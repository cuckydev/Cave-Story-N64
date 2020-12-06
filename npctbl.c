#include "npctbl.h"
#include "npcxxx.h"

const NPC_FUNC gpNpcFuncTbl[] = {
	{Npc000_Act, NULL}, //000,
	{NULL, NULL}, //001,
	{NULL, NULL}, //002,
	{NULL, NULL}, //003,
	{Npc004_Act, Npc004_Put}, //004,
	{NULL, NULL}, //005,
	{NULL, NULL}, //006,
	{NULL, NULL}, //007,
	{NULL, NULL}, //008,
	{NULL, NULL}, //009,
	{NULL, NULL}, //010,
	{NULL, NULL}, //011,
	{NULL, NULL}, //012,
	{NULL, NULL}, //013,
	{NULL, NULL}, //014,
	{Npc015_Act, Npc015_Put}, //015,
	{Npc016_Act, Npc016_Put}, //016,
	{Npc017_Act, Npc017_Put}, //017,
	{Npc018_Act, Npc018_Put}, //018,
	{NULL, NULL}, //019,
	{NULL, NULL}, //020,
	{Npc021_Act, Npc021_Put}, //021,
	{NULL, NULL}, //022,
	{NULL, NULL}, //023,
	{NULL, NULL}, //024,
	{NULL, NULL}, //025,
	{NULL, NULL}, //026,
	{NULL, NULL}, //027,
	{NULL, NULL}, //028,
	{NULL, NULL}, //029,
	{Npc030_Act, Npc030_Put}, //030,
	{NULL, NULL}, //031,
	{Npc032_Act, Npc032_Put}, //032,
	{NULL, NULL}, //033,
	{NULL, NULL}, //034,
	{NULL, NULL}, //035,
	{NULL, NULL}, //036,
	{NULL, NULL}, //037,
	{NULL, NULL}, //038,
	{NULL, NULL}, //039,
	{NULL, NULL}, //040,
	{NULL, NULL}, //041,
	{NULL, NULL}, //042,
	{NULL, NULL}, //043,
	{NULL, NULL}, //044,
	{NULL, NULL}, //045,
	{NULL, NULL}, //046,
	{NULL, NULL}, //047,
	{NULL, NULL}, //048,
	{NULL, NULL}, //049,
	{NULL, NULL}, //050,
	{NULL, NULL}, //051,
	{NULL, NULL}, //052,
	{NULL, NULL}, //053,
	{NULL, NULL}, //054,
	{NULL, NULL}, //055,
	{NULL, NULL}, //056,
	{NULL, NULL}, //057,
	{NULL, NULL}, //058,
	{Npc059_Act, Npc059_Put}, //059,
	{NULL, NULL}, //060,
	{NULL, NULL}, //061,
	{NULL, NULL}, //062,
	{NULL, NULL}, //063,
	{Npc064_Act, Npc064_Put}, //064,
	{Npc065_Act, Npc065_Put}, //065,
	{NULL, NULL}, //066,
	{NULL, NULL}, //067,
	{NULL, NULL}, //068,
	{NULL, NULL}, //069,
	{NULL, NULL}, //070,
	{NULL, NULL}, //071,
	{NULL, NULL}, //072,
	{Npc073_Act, Npc073_Put}, //073,
	{NULL, NULL}, //074,
	{NULL, NULL}, //075,
	{NULL, NULL}, //076,
	{NULL, NULL}, //077,
	{NULL, NULL}, //078,
	{NULL, NULL}, //079,
	{NULL, NULL}, //080,
	{NULL, NULL}, //081,
	{NULL, NULL}, //082,
	{NULL, NULL}, //083,
	{NULL, NULL}, //084,
	{NULL, NULL}, //085,
	{NULL, NULL}, //086,
	{NULL, NULL}, //087,
	{NULL, NULL}, //088,
	{NULL, NULL}, //089,
	{NULL, NULL}, //090,
	{NULL, NULL}, //091,
	{NULL, NULL}, //092,
	{NULL, NULL}, //093,
	{NULL, NULL}, //094,
	{NULL, NULL}, //095,
	{NULL, NULL}, //096,
	{NULL, NULL}, //097,
	{NULL, NULL}, //098,
	{NULL, NULL}, //099,
	{NULL, NULL}, //100,
	{NULL, NULL}, //101,
	{NULL, NULL}, //102,
	{NULL, NULL}, //103,
	{NULL, NULL}, //104,
	{NULL, NULL}, //105,
	{NULL, NULL}, //106,
	{NULL, NULL}, //107,
	{NULL, NULL}, //108,
	{NULL, NULL}, //109,
	{NULL, NULL}, //110,
	{NULL, NULL}, //111,
	{NULL, NULL}, //112,
	{NULL, NULL}, //113,
	{NULL, NULL}, //114,
	{NULL, NULL}, //115,
	{NULL, NULL}, //116,
	{NULL, NULL}, //117,
	{NULL, NULL}, //118,
	{NULL, Npc119_Put}, //119,
	{NULL, NULL}, //120,
	{NULL, NULL}, //121,
	{NULL, NULL}, //122,
	{NULL, NULL}, //123,
	{NULL, NULL}, //124,
	{NULL, NULL}, //125,
	{NULL, NULL}, //126,
	{NULL, NULL}, //127,
	{NULL, NULL}, //128,
	{NULL, NULL}, //129,
	{NULL, NULL}, //130,
	{NULL, NULL}, //131,
	{NULL, NULL}, //132,
	{NULL, NULL}, //133,
	{NULL, NULL}, //134,
	{NULL, NULL}, //135,
	{NULL, NULL}, //136,
	{NULL, NULL}, //137,
	{NULL, NULL}, //138,
	{NULL, NULL}, //139,
	{NULL, NULL}, //140,
	{NULL, NULL}, //141,
	{NULL, NULL}, //142,
	{NULL, NULL}, //143,
	{NULL, NULL}, //144,
	{NULL, NULL}, //145,
	{NULL, NULL}, //146,
	{NULL, NULL}, //147,
	{NULL, NULL}, //148,
	{NULL, NULL}, //149,
	{NULL, NULL}, //150,
	{NULL, NULL}, //151,
	{NULL, NULL}, //152,
	{NULL, NULL}, //153,
	{NULL, NULL}, //154,
	{NULL, NULL}, //155,
	{NULL, NULL}, //156,
	{NULL, NULL}, //157,
	{NULL, NULL}, //158,
	{NULL, NULL}, //159,
	{NULL, NULL}, //160,
	{NULL, NULL}, //161,
	{NULL, NULL}, //162,
	{NULL, NULL}, //163,
	{NULL, NULL}, //164,
	{NULL, NULL}, //165,
	{NULL, NULL}, //166,
	{NULL, NULL}, //167,
	{NULL, NULL}, //168,
	{NULL, NULL}, //169,
	{NULL, NULL}, //170,
	{NULL, NULL}, //171,
	{NULL, NULL}, //172,
	{NULL, NULL}, //173,
	{NULL, NULL}, //174,
	{NULL, NULL}, //175,
	{NULL, NULL}, //176,
	{NULL, NULL}, //177,
	{NULL, NULL}, //178,
	{NULL, NULL}, //179,
	{NULL, NULL}, //180,
	{NULL, NULL}, //181,
	{NULL, NULL}, //182,
	{NULL, NULL}, //183,
	{NULL, NULL}, //184,
	{NULL, NULL}, //185,
	{NULL, NULL}, //186,
	{NULL, NULL}, //187,
	{NULL, NULL}, //188,
	{NULL, NULL}, //189,
	{NULL, NULL}, //190,
	{NULL, NULL}, //191,
	{NULL, NULL}, //192,
	{NULL, NULL}, //193,
	{NULL, NULL}, //194,
	{NULL, NULL}, //195,
	{NULL, NULL}, //196,
	{NULL, NULL}, //197,
	{NULL, NULL}, //198,
	{NULL, NULL}, //199,
	{NULL, NULL}, //200,
	{NULL, NULL}, //201,
	{NULL, NULL}, //202,
	{NULL, NULL}, //203,
	{NULL, NULL}, //204,
	{NULL, NULL}, //205,
	{NULL, NULL}, //206,
	{NULL, NULL}, //207,
	{NULL, NULL}, //208,
	{NULL, NULL}, //209,
	{NULL, NULL}, //210,
	{NULL, Npc211_Put}, //211,
	{NULL, NULL}, //212,
	{NULL, NULL}, //213,
	{NULL, NULL}, //214,
	{NULL, NULL}, //215,
	{NULL, NULL}, //216,
	{NULL, NULL}, //217,
	{NULL, NULL}, //218,
	{NULL, NULL}, //219,
	{NULL, NULL}, //220,
	{NULL, NULL}, //221,
	{NULL, NULL}, //222,
	{NULL, NULL}, //223,
	{NULL, NULL}, //224,
	{NULL, NULL}, //225,
	{NULL, NULL}, //226,
	{NULL, NULL}, //227,
	{NULL, NULL}, //228,
	{NULL, NULL}, //229,
	{NULL, NULL}, //230,
	{NULL, NULL}, //231,
	{NULL, NULL}, //232,
	{NULL, NULL}, //233,
	{NULL, NULL}, //234,
	{NULL, NULL}, //235,
	{NULL, NULL}, //236,
	{NULL, NULL}, //237,
	{NULL, NULL}, //238,
	{NULL, NULL}, //239,
	{NULL, NULL}, //240,
	{NULL, NULL}, //241,
	{NULL, NULL}, //242,
	{NULL, NULL}, //243,
	{NULL, NULL}, //244,
	{NULL, NULL}, //245,
	{NULL, NULL}, //246,
	{NULL, NULL}, //247,
	{NULL, NULL}, //248,
	{NULL, NULL}, //249,
	{NULL, NULL}, //250,
	{NULL, NULL}, //251,
	{NULL, NULL}, //252,
	{NULL, NULL}, //253,
	{NULL, NULL}, //254,
	{NULL, NULL}, //255,
	{NULL, NULL}, //256,
	{NULL, NULL}, //257,
	{NULL, NULL}, //258,
	{NULL, NULL}, //259,
	{NULL, NULL}, //260,
	{NULL, NULL}, //261,
	{NULL, NULL}, //262,
	{NULL, NULL}, //263,
	{NULL, NULL}, //264,
	{NULL, NULL}, //265,
	{NULL, NULL}, //266,
	{NULL, NULL}, //267,
	{NULL, NULL}, //268,
	{NULL, NULL}, //269,
	{NULL, NULL}, //270,
	{NULL, NULL}, //271,
	{NULL, NULL}, //272,
	{NULL, NULL}, //273,
	{NULL, NULL}, //274,
	{NULL, NULL}, //275,
	{NULL, NULL}, //276,
	{NULL, NULL}, //277,
	{NULL, NULL}, //278,
	{NULL, NULL}, //279,
	{NULL, NULL}, //280,
	{NULL, NULL}, //281,
	{NULL, NULL}, //282,
	{NULL, NULL}, //283,
	{NULL, NULL}, //284,
	{NULL, NULL}, //285,
	{NULL, NULL}, //286,
	{NULL, NULL}, //287,
	{NULL, NULL}, //288,
	{NULL, NULL}, //289,
	{NULL, NULL}, //290,
	{NULL, NULL}, //291,
	{NULL, NULL}, //292,
	{NULL, NULL}, //293,
	{NULL, NULL}, //294,
	{NULL, NULL}, //295,
	{NULL, NULL}, //296,
	{NULL, NULL}, //297,
	{NULL, NULL}, //298,
	{NULL, NULL}, //299,
	{NULL, NULL}, //300,
	{NULL, NULL}, //301,
	{NULL, NULL}, //302,
	{NULL, NULL}, //303,
	{NULL, NULL}, //304,
	{NULL, NULL}, //305,
	{NULL, NULL}, //306,
	{NULL, NULL}, //307,
	{NULL, NULL}, //308,
	{NULL, NULL}, //309,
	{NULL, NULL}, //310,
	{NULL, NULL}, //311,
	{NULL, NULL}, //312,
	{NULL, NULL}, //313,
	{NULL, NULL}, //314,
	{NULL, NULL}, //315,
	{NULL, NULL}, //316,
	{NULL, NULL}, //317,
	{NULL, NULL}, //318,
	{NULL, NULL}, //319,
	{NULL, NULL}, //320,
	{NULL, NULL}, //321,
	{NULL, NULL}, //322,
	{NULL, NULL}, //323,
	{NULL, NULL}, //324,
	{NULL, NULL}, //325,
	{NULL, NULL}, //326,
	{NULL, NULL}, //327,
	{NULL, NULL}, //328,
	{NULL, NULL}, //329,
	{NULL, NULL}, //330,
	{NULL, NULL}, //331,
	{NULL, NULL}, //332,
	{NULL, NULL}, //333,
	{NULL, NULL}, //334,
	{NULL, NULL}, //335,
	{NULL, NULL}, //336,
	{NULL, NULL}, //337,
	{NULL, NULL}, //338,
	{NULL, NULL}, //339,
	{NULL, NULL}, //340,
	{NULL, NULL}, //341,
	{NULL, NULL}, //342,
	{NULL, NULL}, //343,
	{NULL, NULL}, //344,
	{NULL, NULL}, //345,
	{NULL, NULL}, //346,
	{NULL, NULL}, //347,
	{NULL, NULL}, //348,
	{NULL, NULL}, //349,
	{NULL, NULL}, //350,
	{NULL, NULL}, //351,
	{NULL, NULL}, //352,
	{NULL, NULL}, //353,
	{NULL, NULL}, //354,
	{NULL, NULL}, //355,
	{NULL, NULL}, //356,
	{NULL, NULL}, //357,
	{NULL, NULL}, //358,
	{Npc359_Act, NULL}, //359,
	{NULL, NULL}, //360,
};