static const u8 pens1_map[21*16] = {
  0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 
  0x24, 0x24, 0x34, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x34, 0x33, 0x33, 0x33, 0x33, 0x33, 0x34, 0x24, 0x24, 0x24, 
  0x24, 0x24, 0x32, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x34, 0x12, 0x11, 0x12, 0x11, 0x12, 0x30, 0x24, 0x24, 0x24, 
  0x24, 0x24, 0x32, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x0D, 0x0E, 0x34, 0x02, 0x01, 0x02, 0x01, 0x02, 0x34, 0x33, 0x33, 0x34, 
  0x24, 0x24, 0x32, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x1D, 0x1E, 0x34, 0x22, 0x21, 0x22, 0x11, 0x12, 0x03, 0x01, 0x02, 0x30, 
  0x33, 0x33, 0x34, 0x16, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x34, 0x31, 0x31, 0x31, 0x01, 0x02, 0x13, 0x11, 0x12, 0x30, 
  0x34, 0x02, 0x03, 0x01, 0x02, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x11, 0x33, 0x33, 0x12, 0x16, 0x01, 0x02, 0x30, 
  0x34, 0x22, 0x23, 0x21, 0x22, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x03, 0x01, 0x02, 0x10, 0x21, 0x22, 0x30, 
  0x34, 0x31, 0x17, 0x31, 0x16, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x23, 0x21, 0x22, 0x20, 0x16, 0x31, 0x34, 
  0x34, 0x04, 0x05, 0x34, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x34, 
  0x34, 0x14, 0x15, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x04, 0x05, 0x04, 0x05, 0x04, 0x05, 0x04, 0x34, 
  0x34, 0x34, 0x31, 0x14, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x14, 0x15, 0x14, 0x15, 0x14, 0x15, 0x14, 0x34, 
  0x34, 0x34, 0x34, 0x34, 0x34, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x31, 0x05, 0x04, 0x05, 0x04, 0x05, 0x31, 0x31, 0x34, 
  0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x15, 0x14, 0x15, 0x14, 0x15, 0x34, 0x34, 0x34, 
  0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x31, 0x34, 0x34, 0x34, 0x34, 0x34, 
  0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 
};

static const EVENT pens1_event[34] = {
  {0, 0, 0, 0, 0, 0x0000},
  {1, 0, 0, 0, 0, 0x0000},
  {2, 0, 0, 0, 0, 0x0000},
  {17, 8, 0, 102, 18, 0x2000},
  {7, 8, 0, 200, 20, 0x3000},
  {12, 4, 0, 16, 16, 0x2000},
  {13, 4, 0, 17, 17, 0x2000},
  {15, 13, 0, 0, 0, 0x0000},
  {5, 8, 0, 500, 22, 0x2000},
  {15, 12, 0, 0, 0, 0x0000},
  {5, 7, 0, 0, 23, 0x0000},
  {6, 4, 0, 19, 34, 0x2000},
  {8, 4, 0, 19, 34, 0x2000},
  {10, 9, 0, 0, 43, 0x0000},
  {3, 0, 151, 1100, 15, 0x2800},
  {10, 4, 0, 0, 0, 0x0000},
  {13, 9, 0, 0, 43, 0x1000},
  {7, 7, 0, 0, 62, 0x4000},
  {15, 8, 154, 600, 74, 0x2800},
  {19, 7, 0, 100, 0, 0x0000},
  {5, 9, 0, 300, 0, 0x0000},
  {4, 7, 0, 301, 0, 0x0000},
  {6, 6, 157, 622, 0, 0x3800},
  {6, 7, 157, 621, 0, 0x2800},
  {17, 7, 157, 624, 0, 0x3800},
  {17, 7, 157, 625, 0, 0x3800},
  {6, 8, 156, 622, 55, 0x3800},
  {10, 8, 156, 621, 113, 0x3800},
  {12, 8, 156, 625, 42, 0x2800},
  {16, 8, 156, 624, 61, 0x3800},
  {1, 4, 161, 650, 0, 0x6000},
  {11, 6, 160, 651, 46, 0x1900},
  {9, 8, 161, 660, 113, 0x2800},
  {16, 12, 0, 210, 234, 0x2000},
};

static const StageData pens1_data = {
    21, 16,
    pens1_map,
    34,
    pens1_event,
    "\n\
#0090\n\
<MNA<CMU0002<FAI0000<END\n\
#0091\n\
<MNA<CMU0002<FAI0001<END\n\
#0092\n\
<MNA<CMU0002<FAI0002<END\n\
#0093\n\
<MNA<CMU0002<FAI0003<END\n\
#0094\n\
<MNA<FLJ0341:0095<CMU0002<FAI0004<END\n\
\n\
#0095\n\
<CMU0014<FAI0004<END\n\
\n\
\n\
#0098\n\
<CMU0014\n\
<ANP0500:0001:0000<FAI0004\n\
<CNP0301:0112:0002<WAI0100\n\
<ANP0500:0000:0000\n\
<MYD0002<SMC<DNP0301<END\n\
\n\
#0099\n\
<KEY<MNA<FLJ0341:0098<CMU0002\n\
<ANP0500:0001:0000<FAI0004\n\
<CNP0301:0112:0002<WAI0100\n\
<ANP0500:0000:0000\n\
<MYD0002<SMC<DNP0301<END\n\
\n\
\n\
#0100\n\
<PRI<FAO0004<TRA0010:0094:0018:0032\n\
#0101\n\
<PRI<FAO0004<TRA0012:0094:0037:0011\n\
#0102\n\
<FLJ0155:0103<PRI<SOU0011<DNP0102<FAO0004<TRA0011:0094:0016:0053\n\
#0103\n\
<PRI<SOU0011<CMU0000<DNP0102<FAO0004<TRA0011:0400:0016:0053\n\
\n\
\n\
#0200\n\
<FLJ0159:0205\n\
<FLJ0158:0204\n\
<FLJ0157:0203\n\
<FLJ0325:0202\n\
<FLJ0154:0201\n\
<KEY<MSGWords light up the screen...<NOD<CLR<TUR\"...If I have to, though,\n\
I really will...\"<NOD<FLJ0153:0000<CLR<MSGDo you want to permit\n\
teleportation to the Egg Corridor?<YNJ0000<CLRPermission granted to access Egg\n\
Corridor.<NOD<FL+0153<PS+0001:6001<END\n\
#0201\n\
<KEY<MSGWords light up the screen...<NOD<CLR\n\
<TURConnecting to Grasstown...<NOD<END\n\
#0202\n\
<KEY<MSG<TUR\n\
Connected to Grasstown.<NOD<END\n\
#0203\n\
<KEY<MSG<TUR\n\
Enter command.<NOD<END\n\
#0204\n\
<KEY<MSG<TUR\n\
Connected to Sand Zone.<NOD<END\n\
#0205\n\
<KEY<MSGWords light up the screen...<NOD<CLR<TUR\n\
Head for the Egg Corridor\n\
                        --Kazuma<NOD<END\n\
#0210\n\
<KEY<MSGFlowers...?<NOD<END\n\
\n\
#0300\n\
#0301\n\
#0303\n\
\n\
#0500\n\
<KEY<MSGA teleporter.<NOD<SLP<NOD<END\n\
\n\
#0600\n\
<FLJ0325:0601\n\
<KEY<MSG<FAC0009Welcome back.<NOD<CLRSue's back.<NOD\n\
She's been locked up in\n\
the cage outside.<NOD\n\
When the Doctor's flunkies\n\
come, we're going to try\n\
to get Toroko back.<NOD\n\
In exchange for Sue,\n\
you see.<NOD<CLRIt's not very nice, I know,\n\
but Toroko is one of us.<NOD\n\
That's what you get when\n\
you act alone.<NOD<END\n\
#0601\n\
<KEY<MSG<FAC0009I hope Toroko's safe...<NOD<END\n\
\n\
\n\
#0620\n\
<KEY<CMU0000<FL+0156<FL+0444\n\
<ANP0500:0001:0000\n\
<WAI0002<CNP0622:0055:0000<WAI0010\n\
<FAI0004\n\
<CNP0621:0113:0000\n\
<ANP0621:0030:0000<WAI0100\n\
<MSG<FAC0018Oooohh...<NOD<CLR<FAC0010...Are you okay?<NOD<CLO<FAC0000\n\
<WAI0030<ANP0621:0000:0002\n\
<MSG<FAC0018...Mmm.<NOD<CLRMy life flashed before\n\
my eyes.<NOD<CLR<FAC0010.....<NOD<CLO<FAC0000\n\
<ANP0500:0000:0000<WAI0030\n\
<ANP0102:0000:0002<SOU0011\n\
<CNP0625:0042:0000\n\
<MSG<FAC0001Kazuma!!<NOD<ANP0622:0000:0002<CLRAnd Professor Booster!<NOD<CLR<FAC0018Oh!<NOD<CLO<FAC0000\n\
<ANP0621:0003:0002<WAI0080\n\
<ANP0621:0000:0002\n\
<MSG<FAC0018You're all right, then?!<NOD<CLR<FAC0001Well, more or less.<NOD<CLO<FAC0000\n\
<CNP0624:0061:0000\n\
<ANP0625:0003:0000<WAI0016\n\
<ANP0624:0008:0000<WAI0016\n\
<ANP0624:0000:0000\n\
<SOU0011<ANP0102:0000:0000<WAI0048\n\
<ANP0625:0000:0000\n\
<MSG<FAC0007.....<NOD<CLR<FAC0018Who's that Mimiga?<NOD<CLO<FAC0000\n\
<WAI0030\n\
<ANP0625:0000:0002<WAI0030\n\
<ANP0624:0000:0002<WAI0050\n\
<ANP0625:0000:0000<WAI0020\n\
<MSG<FAC0001That's King.<NOD<CLRA friend of mine here in\n\
the village.<NOD<CLRThere used to be tons of\n\
Mimigas here.<NOD\n\
Nearly all of them,\n\
though, have been kidnapped\n\
by the Doctor's goons.<NOD<CLREven King has lost\n\
friends...<NOD<CLO\n\
<CMU0002\n\
<ANP0500:0001:0000\n\
<CNP0301:0112:0002<WAI0100\n\
<ANP0500:0000:0000\n\
<MYD0002<SMC<DNP0301<FL-0157<END\n\
\n\
#0621\n\
<KEY<FLJ0158:0631<MSG<FAC0018The Doctor's plans are\n\
proceeding exactly on\n\
schedule...<NOD\n\
If we don't do something\n\
soon...<NOD<END\n\
#0622\n\
<KEY<FLJ0158:0632<MSG<FAC0010Thanks for your help.<NOD<CLROur transportation didn't\n\
really survive, but at\n\
least we did.<NOD<END\n\
#0624\n\
<KEY<FLJ0158:0634<MSG<FAC0007Toroko as a death\n\
weapon...<NOD\n\
No! I'll never allow it!<NOD<END\n\
#0625\n\
<KEY<FLJ0158:0635<MYB0000<WAI0030<MYD0000<ANP0625:0000:0002<MSG\n\
<FAC0001Welcome back!<NOD<CLRLooks like I owe you\n\
another one.<NOD\n\
With my brother's help,<NOD\n\
we should be able to get\n\
around the password for\n\
that egg.<NOD<CLO<FAC0000\n\
<ANP0625:0003:0000<WAI0008\n\
<ANP0625:0000:0000<MSG<FAC0001Booster!<NOD<CLRCan we take this little\n\
guy with us when we go?<NOD<CLO<FAC0000\n\
<ANP0622:0003:0002<WAI0015\n\
<ANP0622:0005:0002\n\
<MSG<FAC0018<CMU0000.....<NOD<CLR\n\
<FAC0010Professor.<NOD<CLR<FAC0001\?\?\?<NOD<CLR<FAC0018Sue, my dear...<NOD\n\
We have to suspend our\n\
escape.<NOD<CLRThe Doctor has located\n\
the red flowers.<NOD<ANP0624:0000:0000<CLR\n\
<FAC0007!!!<NOD<CLR<FAC0001What?<NOD<CLR<FAC0018While he has not yet\n\
acquired them, it is only\n\
a matter of time.<NOD\n\
The location is the Sand\n\
Zone.<NOD<CLRThe flowers are apparently\n\
to be found somewhere in\n\
the Sand Zone.<NOD<CLR\n\
<FAC0007The Sand Zone?<NOD<CLRYou mean, that's where\n\
we'll find the Doctor?<NOD<CLR<FAC0018Well,<NOD more likely one\n\
of his servants.<NOD\n\
If we don't destroy those\n\
flowers before they get\n\
their hands on them...<NOD<CLRHowever, the Sand Zone is\n\
exceedingly dangerous.<NOD\n\
Even supposing we made the\n\
trip,<NOD\n\
there's no guarantee that\n\
we would return alive...<NOD<CLR\n\
<FAC0007You're giving up?<NOD<CLR<FAC0018Actually...<NOD<CLRThere's one of us who's\n\
a perfect match for this\n\
job.<NOD<CLO<FAC0000\n\
<ANP0621:0003:0002<ANP0625:0003:0000<WAI0020\n\
<ANP0621:0000:0002<WAI0002<ANP0625:0000:0002\n\
<MSG<FAC0018It's you.<NOD<CLR\n\
<CMU0002<FAC0010...Who IS he?<NOD<CLR<FAC0018In fact...<NOD<CLRThis is one of the armed\n\
scout robots that were\n\
dispatched to this island<NOD\n\
10 years ago.<NOD<CLR<FAC0010A robot?!<NOD<CLR<FAC0018My impression was that\n\
they had been completely\n\
wiped out,<ANP0621:0000:0000<NOD\n\
but I do not know the\n\
particulars.<NOD\n\
It's entirely possible that\n\
one of them could have...<NOD<CLR<FAC0010Professor.<NOD\n\
I've connected to the Sand\n\
Zone.<NOD<CLR<FAC0018I see.<NOD<CLO<FAC0000\n\
<ANP0622:0003:0000<WAI0015\n\
<ANP0622:0000:0002\n\
<ANP0621:0000:0002<WAI0030<MSG<FAC0018You are the most suited\n\
to exploring this island.<NOD<CLRPlease. Give us your aid.<NOD<FL+0158<PS+0003:6003<END\n\
\n\
\n\
\n\
\n\
#0631\n\
<KEY<MSG<FAC0018You can reach the Sand\n\
Zone via the teleporter.<NOD\n\
Find the red flowers and\n\
burn every single one of\n\
them.<NOD<END\n\
#0632\n\
<KEY<MSG<FAC0010So you're one of the...<NOD<CLRI hadn't even noticed.<NOD<CLRMy, my, you certainly are\n\
well-built.<NOD<END\n\
#0634\n\
<KEY<MSG<FAC0007The Sand Zone...<NOD<END\n\
#0635\n\
<KEY<MSG<FAC0001If you get rid of the\n\
flowers, we'll be able to\n\
prevent the war for now.<NOD<CLRIt's a big responsibility.<NOD<END\n\
\n\
\n\
#0650\n\
<KEY<MSG<FAC0018Take Sue with you and\n\
flee this island...<NOD\n\
I beg you...<NOD<END\n\
\n\
#0651\n\
<DNP0651<KEY<MYD0000\n\
<ANP0500:0001:0000<WAI0050\n\
<MNP0650:0006:0007:0002\n\
<CNP0650:0113:0002\n\
<ANP0650:0030:0002<WAI0100\n\
<ANP0650:0000:0002\n\
<ANP0500:0000:0000<WAI0050\n\
<ANP0650:0003:0002<WAI0064\n\
<ANP0650:0000:0000\n\
<MSG\n\
<FAC0018.....<NOD<CLO<FAC0000\n\
<ANP0650:0000:0002<WAI0050\n\
<MSG<FAC0018Only you, I see...<NOD<CLR...The Doctor has acquired\n\
the red flowers.<NOD<CLR...The island's Mimigas\n\
have all fallen into his\n\
hands.<NOD<CLRSo the tragedy has become\n\
inevitable...<NOD<CLRI should have allowed\n\
at least Sue to escape\n\
when I had the chance...<NOD<CLO<FAC0000\n\
<ANP0650:0003:0002<WAI0022\n\
<ANP0650:0005:0002\n\
<IT+0023<FL+0744<FL+0162<GIT1023\n\
<MSG\n\
Got the =Booster v2.0=.<WAI0030<NOD<CLO<GIT0000\n\
<ANP0650:0000:0002\n\
<MSG<FAC0018Please heed my last\n\
request.<NOD<CLRIf you see Sue again,<NOD\n\
I want you to take her\n\
and flee this island.<NOD<CLRThat girl is Sakamoto's\n\
daughter,<NOD\n\
and she never wanted to\n\
come here in the first\n\
place.<NOD\n\
But we couldn't leave the\n\
child all alone,<NOD\n\
so she had no choice but\n\
to come along with us.<NOD<CLR\n\
I beg you.<NOD<CLRTake that girl with you\n\
and flee.<NOD<CLO\n\
<FL-0160<FL+0161<FL+0741<PS+0004:6004<END\n\
\n\
\n\
#0660\n\
<KEY<FLJ1020:0661<MSG<FAC0018Take Sue with you and\n\
flee this island...<NOD\n\
I beg you...<NOD<END\n\
#0661\n\
<KEY<MSG<FAC0018I'm truly sorry for the\n\
chaos that has befallen\n\
your island.<NOD<CLRWe humans must take the\n\
blame.<NOD<END\n\
\n\
\n\
#0700\n\
<KEY<CMU0000<FAO0004<TRA0024:0700:0002:0000\n\
\n\
\n\
#6001\n\
<PRI<MSGDo you want to go to the\n\
Egg Corridor?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0500:0001:0000\n\
<WAI0100<FAO0004<FLJ0159:6011<TRA0002:0099:0005:0006\n\
#6002\n\
<PRI<MSGDo you want to go to Grasstown?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0500:0001:0000\n\
<WAI0100<FAO0004<TRA0006:0098:0004:0018\n\
#6003\n\
<PRI<MSGDo you want to go to the\n\
Sand Zone?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0500:0001:0000\n\
<WAI0100<FAO0004<TRA0010:0099:0036:0033\n\
\n\
#6004\n\
<PRI<MSGDo you want to go to the\n\
Labyrinth?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0500:0001:0000\n\
<WAI0100<FAO0004<TRA0043:0099:0010:0034\n\
\n\
#6005\n\
<PRI<MSGDo you want to go to the\n\
Plantation?<YNJ0000<CLO\n\
<KEY<CNP0300:0111:0002<HMC<WAI0060<ANP0500:0001:0000\n\
<WAI0100<FAO0004<TRA0060:0099:0009:0009\n\
\n\
#6011\n\
<KEY<TRA0049:0099:0007:0006\n\
\n\
",
};
