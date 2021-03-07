#include "draw.h"
#include "config.h"

#include <assert.h>

//#define ALIGN_DEBUG

//Current render state
static RenderState render_state;
static u8 *prev_tex;
static u16 *prev_tlut;

//Render constants
const RECT grcFull = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Gfx list
Gfx glist[GLIST_LENGTH];
Gfx *glistp;

//RCP initialization DLs
static Vp viewport = {{
	{SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, G_MAXZ, 0},
	{SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, G_MAXZ, 0},
}};

static Gfx dl_init_rsp[] = {
	gsSPViewport(&viewport),
	gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
	                      G_FOG | G_LIGHTING | G_TEXTURE_GEN |
	                      G_TEXTURE_GEN_LINEAR | G_LOD),
	gsSPTexture(0, 0, 0, 0, G_OFF),
	gsSPEndDisplayList(),
};

static Gfx dl_init_rdp[] = {
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
	gsDPSetCombineKey(G_CK_NONE),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
	gsDPSetColorDither(G_CD_DISABLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

//Internal draw functions
static void PreNMICallback()
{
	//Reset VI to prevent a console crash on PAL systems
	nuGfxDisplayOff();
	osViSetYScale(1);
}

//Draw interface
void InitDirectDraw(NUGfxFunc vblank_callback)
{
	//Setup for target television
	switch (osTvType)
	{
		case OS_TV_PAL:
			osViSetMode(&osViModeTable[OS_VI_FPAL_LAN1]);
			osViSetYScale(0.833);
			nuPreNMIFuncSet((NUScPreNMIFunc)PreNMICallback);
			break;
		case OS_TV_MPAL:
			osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
			break;
		default:
			break;
	}
	
	//Initialize NuSys
	nuGfxInit();
	osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
	nuGfxFuncSet(vblank_callback);
	nuGfxDisplayOn();
}

void StartFrame()
{
	//Reset pointer to head
	glistp = glist;
	
	//Initialize RCP
	gSPSegment(glistp++, 0, 0);
	gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(dl_init_rsp));
	gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(dl_init_rdp));
	gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
	gDPPipeSync(glistp++);
	
	//Reset draw state
	render_state = RS_Null;
	prev_tex = NULL;
	prev_tlut = NULL;
}

void EndFrame()
{
	//End display list and execute
	gDPFullSync(glistp++);
	gSPEndDisplayList(glistp++);
	assert((glistp - glist) <= GLIST_LENGTH);
	nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX2, NU_SC_SWAPBUFFER);
}

static void SetRenderState(RenderState next_render_state)
{
	//Change render state
	if (next_render_state == render_state)
		return;
	render_state = next_render_state;
	
	//Prepare for given render state
	switch (render_state)
	{
		case RS_Rect:
			gDPSetCycleType(glistp++, G_CYC_FILL);
			gDPSetRenderMode(glistp++, G_RM_NOOP, G_RM_NOOP2);
			gDPPipeSync(glistp++);
			break;
		case RS_Tex:
			gDPSetCycleType(glistp++, G_CYC_1CYCLE);
			gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
			gDPSetRenderMode(glistp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE);
			
			gDPSetDepthSource(glistp++, G_ZS_PIXEL);
			gDPSetPrimDepth(glistp++, 0, 0);
			gDPSetTexturePersp(glistp++, G_TP_NONE);
			gDPSetTextureLUT(glistp++, G_TT_RGBA16);
			gDPPipeSync(glistp++);
			break;
		case RS_Copy:
			gDPSetCycleType(glistp++, G_CYC_COPY);
			gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
			gDPSetRenderMode(glistp++, G_RM_NOOP, G_RM_NOOP2);
			
			gDPSetDepthSource(glistp++, G_ZS_PIXEL);
			gDPSetPrimDepth(glistp++, 0, 0);
			gDPSetTexturePersp(glistp++, G_TP_NONE);
			gDPSetTextureLUT(glistp++, G_TT_NONE);
			gDPPipeSync(glistp++);
			break;
		default:
			break;
	}
}

void LoadTLUT_CI4(u16 *tlut)
{
	#ifdef ALIGN_DEBUG
	if ((size_t)tlut & 0x7)
	{ while (1) {;} }
	#endif
	if (tlut != prev_tlut)
	{
		gDPLoadTLUT_pal16(glistp++, 0, tlut);
		prev_tlut = tlut;
	}
}

void LoadTLUT_CI8(u16 *tlut)
{
	#ifdef ALIGN_DEBUG
	if ((size_t)tlut & 0x7)
	{ while (1) {;} }
	#endif
	if (tlut != prev_tlut)
	{
		gDPLoadTLUT_pal256(glistp++, tlut);
		prev_tlut = tlut;
	}
}

void LoadTex_CI4(u32 width, u32 height, u8 *tex)
{
	#ifdef ALIGN_DEBUG
	if ((size_t)tex & 0x7)
	{ while (1) {;} }
	#endif
	if (tex != prev_tex)
	{
		gDPLoadTextureBlock_4b(glistp++, 
			tex,
			G_IM_FMT_CI,
			width, height,
			0,
			G_TX_WRAP, G_TX_WRAP,
			G_TX_NOMASK, G_TX_NOMASK,
			G_TX_NOLOD, G_TX_NOLOD
		);
		gDPPipeSync(glistp++);
		prev_tex = tex;
	}
}

void LoadTex_CI8(u32 width, u32 height, u8 *tex)
{
	#ifdef ALIGN_DEBUG
	if ((size_t)tex & 0x7)
	{ while (1) {;} }
	#endif
	if (tex != prev_tex)
	{
		gDPLoadTextureBlock(glistp++, 
			tex,
			G_IM_FMT_CI,
			G_IM_SIZ_8b,
			width, height,
			0,
			G_TX_WRAP, G_TX_WRAP,
			G_TX_NOMASK, G_TX_NOMASK,
			G_TX_NOLOD, G_TX_NOLOD
		);
		gDPPipeSync(glistp++);
		prev_tex = tex;
	}
}

void LoadTex_C16(u32 width, u32 height, u8 *tex)
{
	#ifdef ALIGN_DEBUG
	if ((size_t)tex & 0xF)
	{ while (1) {;} }
	#endif
	if (tex != prev_tex)
	{
		gDPLoadTextureBlock(glistp++, 
			tex,
			G_IM_FMT_RGBA,
			G_IM_SIZ_16b,
			width, height,
			0,
			G_TX_WRAP, G_TX_WRAP,
			G_TX_NOMASK, G_TX_NOMASK,
			G_TX_NOLOD, G_TX_NOLOD
		);
		gDPPipeSync(glistp++);
		prev_tex = tex;
	}
}

void CopyBitmap(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
	if (src_w <= 0 || src_h <= 0)
		return;
	if (x <= -src_w || y <= -src_h || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	s32 cleft = -x;
	if (cleft < 0)
		cleft = 0;
	s32 ctop = -y;
	if (ctop < 0)
		ctop = 0;
	
	//Render texrect
	SetRenderState(RS_Copy);
	gSPTextureRectangle(glistp++, 
		(x + cleft) << 2, (y + ctop) << 2, 
		(x + src_w - 1) << 2, (y + src_h - 1) << 2,
		G_TX_RENDERTILE, 
		(src->left + cleft) << 5, (src->top + ctop) << 5, 
		4 << 10, 1 << 10
	);
	gDPPipeSync(glistp++);
}

void PutBitmap(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
	if (src_w <= 0 || src_h <= 0)
		return;
	if (x <= -src_w || y <= -src_h || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	//Render texrect
	SetRenderState(RS_Tex);
	gSPScisTextureRectangle(glistp++, 
		x << 2, y << 2, 
		(x + src_w) << 2, (y + src_h) << 2,
		G_TX_RENDERTILE, 
		src->left << 5, src->top << 5, 
		1 << 10, 1 << 10
	);
	gDPPipeSync(glistp++);
}

void PutBitmap_X(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
	if (src_w <= 0 || src_h <= 0)
		return;
	if (x <= -src_w || y <= -src_h || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	//Render texrect
	SetRenderState(RS_Tex);
	gSPScisTextureRectangle(glistp++, 
		x << 2, y << 2, 
		(x + src_w) << 2, (y + src_h) << 2,
		G_TX_RENDERTILE, 
		src->right << 5, src->top << 5, 
		-1 << 10, 1 << 10
	);
	gDPPipeSync(glistp++);
}

void PutBitmap_Y(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
	if (src_w <= 0 || src_h <= 0)
		return;
	if (x <= -src_w || y <= -src_h || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	//Render texrect
	SetRenderState(RS_Tex);
	gSPScisTextureRectangle(glistp++, 
		x << 2, y << 2, 
		(x + src_w) << 2, (y + src_h) << 2,
		G_TX_RENDERTILE, 
		src->left << 5, src->bottom << 5, 
		1 << 10, -1 << 10
	);
}

void PutBitmap_XY(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
	if (src_w <= 0 || src_h <= 0)
		return;
	if (x <= -src_w || y <= -src_h || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	
	//Render texrect
	SetRenderState(RS_Tex);
	gSPScisTextureRectangle(glistp++, 
		x << 2, y << 2, 
		(x + src_w) << 2, (y + src_h) << 2,
		G_TX_RENDERTILE, 
		src->right << 5, src->bottom << 5, 
		-1 << 10, -1 << 10
	);
}

void CortBox(const RECT *rect, u16 col)
{
	//Clip rect against top left
	s32 left = rect->left, top = rect->top;
	if (left < 0)
		left = 0;
	if (top < 0)
		top = 0;
	if (rect->right <= left || rect->bottom <= top || left >= SCREEN_WIDTH || top >= SCREEN_HEIGHT)
		return;
	
	//Draw rect
	SetRenderState(RS_Rect);
	gDPSetFillColor(glistp++, (col << 16) | col);
	gDPFillRectangle(glistp++, left, top, rect->right - 1, rect->bottom - 1);
	gDPPipeSync(glistp++);
}

#include "data/bitmap/font.inc.c"
static const u8 font_space[32*3] = {
	4,2,4,8,6,8,7,2,4,4,8,6,3,6,2,4,6,3,6,6,7,6,6,6,6,6,2,3,4,6,4,5,
	8,6,6,6,6,5,5,6,6,2,5,6,5,6,6,6,6,6,6,5,6,6,6,6,6,6,5,4,4,4,4,6,
	3,6,6,6,6,6,5,6,6,2,4,5,3,8,6,6,6,6,5,5,5,6,6,6,6,6,6,5,2,5,6,4,
};

s32 GetTextWidth(const char *text)
{
	s32 x = 0;
	u8 v;
	while ((v = (u8)*text++ - 0x20) != 0xE0)
		if (v <= 0x60)
			x += font_space[v];
	return x - ((x != 0) ? 1 : 0);
}

static Gfx text_tlut_dumaln[] = { gsSPEndDisplayList() };
ALIGNED8 static u16 text_tlut[0x80][4] = {};
static u8 text_tlut_i = 0;

void PutText(s32 x, s32 y, const char *text, u16 col)
{
	RECT rect = {0, 0, 0, 12};
	u8 v;
	u8 ppy = 0xFF;
	
	//Get colour
	LoadTLUT_CI4(text_tlut[text_tlut_i]);
	text_tlut[text_tlut_i][0] = 0x0000;
	text_tlut[text_tlut_i][1] = col;
	text_tlut_i = (text_tlut_i + 1) & 0x7F;
	
	//Render characters
	while ((v = (u8)*text++ - 0x20) != 0xE0)
	{
		if (v == 0)
		{
			//Don't render spaces, waste of time
			x += font_space[v];
		}
		else if (v <= 0x60)
		{
			//Switch page
			u8 py = v >> 5;
			if (py != ppy)
			{
				LoadTex_CI4(256, 12, font_tex + (128 * 12) * py);
				ppy = py;
			}
			
			//Render character
			rect.left = (v & 0x1F) << 3;
			rect.right = rect.left + 8;
			PutBitmap(&rect, x, y);
			x += font_space[v];
		}
	}
}
