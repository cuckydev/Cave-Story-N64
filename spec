#include <nusys.h>

//Game binary
beginseg
	name "code"
	flags   BOOT OBJECT
	entry   nuBoot
	address NU_SPEC_BOOT_ADDR
	stack   NU_SPEC_BOOT_STACK
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
endseg

//Tilesets
beginseg
	name "prt_cave"
	flags RAW
	include "data/tilesets/prt_cave.dat"
endseg

beginseg
	name "prt_eggin"
	flags RAW
	include "data/tilesets/prt_eggin.dat"
endseg

beginseg
	name "prt_eggs"
	flags RAW
	include "data/tilesets/prt_eggs.dat"
endseg

beginseg
	name "prt_eggx"
	flags RAW
	include "data/tilesets/prt_eggx.dat"
endseg

beginseg
	name "prt_mimi"
	flags RAW
	include "data/tilesets/prt_mimi.dat"
endseg

beginseg
	name "prt_pens"
	flags RAW
	include "data/tilesets/prt_pens.dat"
endseg

beginseg
	name "prt_store"
	flags RAW
	include "data/tilesets/prt_store.dat"
endseg

beginseg
	name "prt_white"
	flags RAW
	include "data/tilesets/prt_white.dat"
endseg

//Stages
beginseg
	name "pens1"
	flags RAW
	include "data/stage/pens1.dat"
endseg

beginseg
	name "eggs"
	flags RAW
	include "data/stage/eggs.dat"
endseg

beginseg
	name "eggx"
	flags RAW
	include "data/stage/eggx.dat"
endseg

beginseg
	name "egg6"
	flags RAW
	include "data/stage/egg6.dat"
endseg

beginseg
	name "eggr"
	flags RAW
	include "data/stage/eggr.dat"
endseg

beginseg
	name "mimi"
	flags RAW
	include "data/stage/mimi.dat"
endseg

beginseg
	name "cave"
	flags RAW
	include "data/stage/cave.dat"
endseg

beginseg
	name "start"
	flags RAW
	include "data/stage/start.dat"
endseg

beginseg
	name "barr"
	flags RAW
	include "data/stage/barr.dat"
endseg

beginseg
	name "pool"
	flags RAW
	include "data/stage/pool.dat"
endseg

beginseg
	name "cemet"
	flags RAW
	include "data/stage/cemet.dat"
endseg

beginseg
	name "plant"
	flags RAW
	include "data/stage/plant.dat"
endseg

beginseg
	name "shelt"
	flags RAW
	include "data/stage/shelt.dat"
endseg

beginseg
	name "comu"
	flags RAW
	include "data/stage/comu.dat"
endseg

beginseg
	name "mibox"
	flags RAW
	include "data/stage/mibox.dat"
endseg

beginseg
	name "egend1"
	flags RAW
	include "data/stage/egend1.dat"
endseg

beginseg
	name "cthu"
	flags RAW
	include "data/stage/cthu.dat"
endseg

beginseg
	name "egg1"
	flags RAW
	include "data/stage/egg1.dat"
endseg

beginseg
	name "pens2"
	flags RAW
	include "data/stage/pens2.dat"
endseg

beginseg
	name "kings"
	flags RAW
	include "data/stage/kings.dat"
endseg

beginseg
	name "pole"
	flags RAW
	include "data/stage/pole.dat"
endseg

//ROM
beginwave
	name    "cave"
	include "code"
	
	//Tilesets
	include "prt_cave"
	include "prt_eggin"
	include "prt_eggs"
	include "prt_eggx"
	include "prt_mimi"
	include "prt_pens"
	include "prt_store"
	include "prt_white"
	
	//Stages
	include "pens1"
	include "eggs"
	include "eggx"
	include "egg6"
	include "eggr"
	include "mimi"
	include "cave"
	include "start"
	include "barr"
	include "pool"
	include "cemet"
	include "plant"
	include "shelt"
	include "comu"
	include "mibox"
	include "egend1"
	include "cthu"
	include "egg1"
	include "pens2"
	include "kings"
	include "pole"
endwave
