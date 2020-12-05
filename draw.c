#include "draw.h"
#include "config.h"

#include <assert.h>

//Current render state
static RenderState render_state;

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
	nuGfxFuncSet(vblank_callback);
}

void StartDirectDraw()
{
	//Turn on display
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
	gDPPipeSync(glistp++);
	
	//Reset draw state
	render_state = RS_Null;
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
			gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
			gDPPipeSync(glistp++);
			break;
		case RS_Tex:
			gDPSetCycleType(glistp++, G_CYC_1CYCLE);
			gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
			
			gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
			gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE);
			
			gDPSetDepthSource(glistp++, G_ZS_PIXEL);
			gDPSetPrimDepth(glistp++, 0, 0);
			gDPSetTexturePersp(glistp++, G_TP_NONE);
			gDPSetTextureLUT(glistp++, G_TT_RGBA16);
			gDPPipeSync(glistp++);
			break;
		default:
			break;
	}
}

void LoadTLUT(u16 *tlut)
{
	gDPLoadTLUT_pal256(glistp++, tlut);
}

void LoadTex_CI4(u32 width, u32 height, u8 *tex)
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
}

void LoadTex_CI8(u32 width, u32 height, u8 *tex)
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
}

void PutBitmap(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
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
	gDPPipeSync(glistp++);
}

void PutBitmap_XY(const RECT *src, s32 x, s32 y)
{
	//Get source rect dimensions
	s32 src_w = src->right - src->left;
	s32 src_h = src->bottom - src->top;
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
	gDPPipeSync(glistp++);
}

void CortBox(const RECT *rect, u32 col)
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
	gDPSetFillColor(glistp++, col);
	gDPFillRectangle(glistp++, left, top, rect->right - 1, rect->bottom - 1);
	gDPPipeSync(glistp++);
}

#include "data/bitmap/font.inc.c"
static const u8 font_space[32*3] = {
	2,2,4,8,6,8,7,2,4,4,8,6,3,6,2,4,6,3,6,6,7,6,6,6,6,6,2,3,4,8,4,5,
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

void PutText(s32 x, s32 y, const char *text, u16 *tlut)
{
	static u8 *font_pages[] = {
		font0_tex,
		font1_tex,
		font2_tex,
	};
	RECT rect = {0, 0, 0, 12};
	
	//Render text character by character
	u8 v;
	u8 ppy = 0xFF;
	
	LoadTLUT(tlut);
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
			u8 py = v / 32;
			if (py != ppy)
			{
				LoadTex_CI4(256, 12, font_pages[py]);
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

