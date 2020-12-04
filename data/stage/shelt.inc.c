static const u8 shelt_map[21*16] = {
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
  0x30, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x30, 
  0x30, 0x54, 0x43, 0x41, 0x42, 0x43, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x43, 0x41, 0x42, 0x41, 0x42, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x51, 0x52, 0x53, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x53, 0x51, 0x52, 0x51, 0x52, 0x54, 0x30, 
  0x30, 0x54, 0x63, 0x61, 0x62, 0x63, 0x61, 0x62, 0x61, 0x62, 0x61, 0x62, 0x61, 0x62, 0x63, 0x61, 0x62, 0x61, 0x62, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x41, 0x42, 0x53, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x53, 0x41, 0x42, 0x41, 0x42, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x51, 0x52, 0x53, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x53, 0x51, 0x52, 0x51, 0x52, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x61, 0x62, 0x53, 0x61, 0x62, 0x61, 0x62, 0x61, 0x62, 0x61, 0x62, 0x53, 0x61, 0x62, 0x61, 0x62, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x41, 0x42, 0x53, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x53, 0x41, 0x42, 0x41, 0x42, 0x54, 0x30, 
  0x30, 0x54, 0x53, 0x51, 0x52, 0x53, 0x50, 0x52, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x53, 0x51, 0x52, 0x51, 0x52, 0x54, 0x30, 
  0x30, 0x54, 0x63, 0x61, 0x62, 0x63, 0x60, 0x61, 0x61, 0x62, 0x61, 0x62, 0x61, 0x62, 0x63, 0x61, 0x62, 0x61, 0x62, 0x54, 0x30, 
  0x30, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x30, 
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
};

static const EVENT shelt_event[21] = {
  {0, 0, 0, 0, 0, 0x0000},
  {1, 0, 0, 0, 0, 0x0000},
  {2, 0, 0, 0, 0, 0x0000},
  {6, 10, 520, 101, 18, 0x4000},
  {2, 10, 0, 0, 0, 0x0000},
  {17, 10, 0, 0, 0, 0x0000},
  {18, 10, 0, 0, 0, 0x0000},
  {15, 10, 0, 102, 22, 0x3000},
  {15, 9, 524, 0, 23, 0x0800},
  {13, 10, 0, 220, 20, 0x3000},
  {13, 9, 521, 0, 62, 0x4000},
  {6, 9, 0, 100, 0, 0x3000},
  {11, 10, 522, 210, 55, 0x3800},
  {16, 9, 0, 303, 0, 0x2000},
  {15, 11, 0, 300, 0, 0x0000},
  {14, 9, 0, 301, 0, 0x0000},
  {3, 10, 525, 16, 16, 0x2800},
  {3, 8, 525, 16, 0, 0x6000},
  {15, 8, 0, 103, 0, 0x1000},
  {4, 8, 525, 17, 0, 0x6000},
  {4, 10, 525, 17, 17, 0x2800},
};

static const StageData shelt_data = {
    21, 16,
    shelt_map,
    21,
    shelt_event,
    "#0090\n\
<MNA<CMU0008<FAI0000<END\n\
#0091\n\
<MNA<CMU0008<FAI0001<END\n\
#0092\n\
<MNA<CMU0008<FAI0002<END\n\
#0093\n\
<MNA<CMU0008<FAI0003<END\n\
#0094\n\
<MNA<CMU0008<FAI0004<END\n\
\n\
#0099\n\
<KEY<MNA<CMU0000<CMU0008\n\
<ANP0102:0001:0000<FAI0004\n\
<CNP0301:0112:0000<WAI0100\n\
<ANP0102:0000:0000\n\
<MYD0000<DNP0301<SMC<END\n\
\n\
#0100\n\
<PRI<FLJ0523:0105<FAO0004<TRA0006:0094:0217:0016\n\
#0101\n\
#0102\n\
<KEY<FLJ0524:0103\n\
<MSGA teleporter.<NOD\n\
It doesn't look like it's\n\
working at the moment...<NOD<END\n\
#0103\n\
<PRI<MSGGo to the Plantation?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0102:0001:0000\n\
<WAI0100<FAO0004<TRA0061:0099:0007:0013\n\
\n\
#0105\n\
<PRI<FAO0004<FL+0227<TRA0006:0600:0217:0016\n\
\n\
\n\
#0200\n\
<KEY<MNA<CMU0000<FAI0004<WAI0100\n\
<QUA0030<SOU0044<ANP0101:0001:0000\n\
<WAI0080<ANP0210:0000:0000<WAI0020\n\
<FL+0520<SOU0011<DNP0101\n\
<WAI0050<MYD0002<MOV0006:0010\n\
<CMU0010<MSG<FAC0010Woohoo!<WAI0160<NOD<CMU0008<CLRYou did it, my boy!<NOD\n\
I knew you could do\n\
it the minute I laid\n\
eyes on you.<NOD<CLR.....<NOD\n\
<CLRAnyway...<NOD\n\
My name is Kazuma\n\
Sakamoto.<NOD\n\
You can call me Kazuma,\n\
that's fine.<NOD<CLRI was lucky enough to\n\
escape from the Doctor,<NOD\n\
but unfortunately,\n\
my teleporter sent me\n\
here.<NOD\n\
I thought I was going\n\
to starve...<NOD\n\
I owe my very life to you!<NOD<CLROh, by the way...<NOD<CLR...You wouldn't happen\n\
to know the Mimiga\n\
Village, would you?<NOD<CLR...Sue?<NOD<CLRYou've met Sue?!<NOD<CLRAh, I see.<NOD\n\
You came in Sue's place\n\
to find me.<NOD<CLRAll right, then!<NOD\n\
Lead the way to the \n\
village!<NOD<SOU0043<ANP0102:0001:0000<WAI0030<ANP0210:0000:0002<CLR?!<NOD<CLO<FAC0000\n\
<CNP0303:0113:0000<ANP0303:0030:0000<WAI0100\n\
<FAC0000<MSG<ANP0102:0000:0000<FAC0018Kazuma?!<NOD<CLR<FAC0010Professor Booster!!<NOD\n\
You're safe!<NOD<CLR<FAC0018Yes, more or less.<NOD<CLO\n\
<ANP0303:0003:0000<WAI0040\n\
<ANP0303:0000:0002<WAI0030\n\
<ANP0303:0000:0000<WAI0030\n\
<FAC0000<MSG<FAC0018And how is Sue?<NOD\n\
Is she all right?<NOD<CLR<FAC0010She's at the Mimiga\n\
village.<NOD\n\
This young fellow was\n\
just about to guide me\n\
there.<NOD<CLO\n\
<WAI0020<ANP0210:0000:0000<WAI0010\n\
<FAC0000<MSG<FAC0018!!!<NOD<CLO\n\
<ANP0303:0003:0000<WAI0080<ANP0303:0000:0000\n\
<FAC0000<MSG<FAC0010Oh, do you two know\n\
each other?<NOD<CLR<FAC0018.....<NOD<CLRNo...<NOD\n\
<ANP0303:0000:0002...No, we've never met.<NOD<CLRNever mind, we must\n\
hurry to find Sue.<NOD\n\
The Doctor has begun\n\
gathering the Mimigas.<NOD\n\
It seems he has become\n\
aware of the red flowers.<NOD<CLR<FAC0010But, Sue...<NOD<CLRWill the red flowers\n\
affect Sue as well?<NOD\n\
Just like the other\n\
Mimigas<CLR<FAC0018Kazuma.<NOD<CLRThe Doctor has begun\n\
gathering the Mimigas.<NOD\n\
You know what that means,\n\
don't you?<NOD<CLR<FAC0010<CMU0000You...you mean, the war?\n\
He...<NOD<CLO<FAC0000\n\
<ANP0303:0003:0002<WAI0032\n\
<ANP0303:0000:0002\n\
<MSG<FAC0018Precisely.<NOD<CMU0008\n\
We have no choice now\n\
but to stop him.<NOD<CLR<FAC0010Stop him? But how?<NOD<CLR<FAC0018I have an idea.<NOD\n\
For now, let us hurry\n\
to where Sue is.<NOD\n\
We'll talk then.<NOD<FAC0000<CLO\n\
<ANP0303:0003:0000<WAI0038\n\
<MYB0002<WAI0016<MYD0002<ANP0303:0000:0000\n\
<MSG<FAC0018You too. Come along.<NOD<CLO\n\
<ANP0303:0005:0000<WAI0020<DNP0303\n\
<ANP0210:0003:0000<WAI0078\n\
<ANP0210:0005:0000<WAI0020<DNP0210\n\
<FL-0522<FL+0523\n\
<CNP0016:0016:0002<WAI0020\n\
<CNP0017:0017:0002<FL+0525<FL+0226\n\
<END\n\
\n\
\n\
\n\
#0210\n\
#0220\n\
<KEY<FLJ0524:0221<MSG<TURThis teleporter is currently\n\
unavailable.<NOD<END\n\
#0221\n\
<KEY<MSG<TURTeleportation to \"Plantation\" is\n\
possible.<NOD<END\n\
\n\
#0300\n\
#0301\n\
#0302\n\
#0303\n\
\n\
\n\
#0500\n\
<KEY<CMU0021<FAI0004\n\
<MSG<TURConnecting to network...<WAI0050\n\
<TURLogged on.<WAI0050\n\
<TURExecuting chat algorithm.<WAI0100<CLR<MSGSue?<NOD\n\
You there?<NOD\n\
It's me.<NOD\n\
Kazuma!<NOD\n\
I managed to get away somehow,\n\
but I've gotten lost...<NOD\n\
I've found a shelter, but there's\n\
nothing here.<NOD\n\
If you can hear me,\n\
please answer!<NOD<CLR...Please?<NOD\n\
<FAO0004<SK+0005<TRA0013:0091:0010:0008\n\
\n\
\n\
#0501\n\
<KEY<HMC<CMU0021<FAI0004\n\
<MSG<TURSearching for user \"Sue\"...<WAI0150<CLR<TUR1 user \"Sue\" found.<WAI0150<CLR<MSGSue!<NOD\n\
Please respond!<NOD\n\
They're looking for you...<NOD\n\
Are you asleep?<NOD\n\
Your brother is so lonely...<NOD<FAO0004<SMC<CLO\n\
<TRA0090:0095:0014:0009\n\
\n\
\n\
#0502\n\
<KEY<HMC<CMU0021<FAI0004\n\
<MSGSuuuuue!<NOD\n\
Answer me!<NOD\n\
I'm so hungry...<NOD\n\
There's nothing to eat and I've\n\
been reduced to feeding on\n\
cockroaches.<NOD\n\
...Ha-ha. That was a joke.\n\
Ha-ha.<NOD<CLR...If I have to, though,\n\
I really will...<NOD<FAO0004<SMC<TRA0011:0302:0008:0006\n\
\n\
\n\
#0700\n\
<KEY<FAI0004<MSGSue?<NOD\n\
Is it really you?<NOD<FAO0004<TRA0024:0701:0002:0000\n\
#0701\n\
<KEY<FAI0004<MSGThe door's stuck and I\n\
can't get out.<NOD\n\
I'm still in this shelter-\n\
sort-of place.<NOD\n\
The sector code is \"Grasstown\"...<NOD\n\
See if you can run a\n\
scan on it from there.<NOD<CLRAlso, Mom's not here.<NOD\n\
I think she might still be\n\
with the Doctor.<NOD<CLRDo any Dragons look immediately\n\
hatchable?<NOD<FAO0004<TRA0024:0702:0002:0000\n\
\n\
#0702\n\
<KEY<FAI0004<MSGGotcha.<NOD\n\
Oh, by the way, I really\n\
could use some food, so<CLR\n\
<MSG<TURUser \"Sue\" has disconnected.<NOD<CLR.....<NOD<FAO0004<TRA0024:0703:0002:0000\n\
\n\
",
};
