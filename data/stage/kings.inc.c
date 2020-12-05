static const u8 kings_map[21*16] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x96, 0x97, 0x98, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x93, 0x94, 0x95, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x90, 0x91, 0x92, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 
  0x00, 0x10, 0x11, 0x01, 0x10, 0x11, 0x01, 0x10, 0x11, 0x01, 0x01, 0x01, 0x10, 0x11, 0x01, 0x10, 0x11, 0x01, 0x10, 0x11, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const EVENT kings_event[4] = {
  {6, 7, 0, 0, 299, 0x1000},
  {14, 7, 0, 0, 299, 0x0000},
  {10, 10, 0, 0, 300, 0x0000},
  {7, 11, 0, 300, 298, 0x0000},
};

static const StageData kings_data = {
    21, 16,
    kings_map,
    4,
    kings_event,
    "\n\
#0090\n\
<MNA<FAI0000<END\n\
#0091\n\
<MNA<FAI0001<END\n\
#0092\n\
<MNA<FAI0002<END\n\
#0093\n\
<MNA<FAI0003<END\n\
#0094\n\
<MNA<FAI0004<END\n\
\n\
#0100\n\
<KEY<MNA<WAI0050<FAI0001\n\
<ANP0300:0010:0000<WAI0097\n\
<ANP0300:0001:0000<WAI0050\n\
<ANP0300:0020:0000<WAI0064\n\
<ANP0300:0001:0000<WAI0016\n\
<ANP0300:0030:0000<WAI0050\n\
<ANP0300:0040:0000<WAI0097\n\
<FAO0001<WAI9999\n\
\n\
#0300\n\
\n\
",
};
