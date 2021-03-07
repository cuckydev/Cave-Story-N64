static const char *head_script = "#0000\n\
<END\n\
\n\
#0001\n\
<PRI<MSGEmpty.<NOD<END\n\
\n\
#0016\n\
<PRI<MSG\n\
Do you want to save?<YNJ0000<FL+0431<TUR<CLR\n\
Saving...<SVP0020<MSGGame saved.<NOD<END\n\
\n\
#0017\n\
<PRI<FLJ0201:0018\n\
<LI+1000<SOU0020<AE+<MSG\n\
Health refilled.<NOD<END\n\
#0018\n\
<PRI\n\
<LI+1000<SOU0020<AE+<MSG\n\
Health and missiles refilled.<NOD<END\n\
\n\
#0019\n\
<KEY<MSG\n\
Do you want to rest?<YNJ0000<FAO0004<CMU0000<WAI0020<CLR.....<NOD<CLO\n\
<WAI0050\n\
<LI+1000<SOU0020<MYD0002<MSG\n\
Health restored.<NOD<CLO<RMU<FAI0004<END\n\
\n\
#0020\n\
<PRI<MSGFailed to save.<NOD<END\n\
#0030\n\
<PRI<FLJ0202:0032<FLJ0201:0031<FL+0201<GIT0005<AM+0005:0010\n\
<CMU0010Got the =Missile Launcher=!<WAI0160<NOD<RMU<CLRThe Missile Launcher is a powerful\n\
weapon, but its ammo is limited.<NOD\n\
You can replenish your stockpile\n\
with items dropped by enemies.<NOD<END\n\
#0031\n\
<PRI<AM+0005:0005<MSG\n\
<GIT0006Max missiles increased by <NUM0000!<NOD<END\n\
#0032\n\
<PRI<AM+0010:0005<MSG\n\
<GIT0011Max missiles increased by <NUM0000!<NOD<END\n\
\n\
#0040\n\
<KEY<CMU0000<WAI0040<PRI<WAI0040<CMU0003\n\
<MSG\n\
You have died.<NOD<CLRWant to retry?<YNJ0049<CLO\n\
<FAO0001<WAI0050<FLJ0431:0048<INI<END\n\
\n\
#0041\n\
<KEY<CMU0000<HMC<WAI0040<PRI<WAI0040<CMU0003\n\
<MSG\n\
You have drowned.<NOD<CLRWant to retry?<YNJ0049<CLO\n\
<FAO0001<WAI0050<FLJ0431:0048<INI<END\n\
\n\
#0042\n\
<KEY<CMU0000<WAI0040<PRI<WAI0040<CMU0003\n\
<MSG<HMC\n\
You were never seen again...<NOD<CLRWant to retry?<YNJ0049<CLO\n\
<FAO0001<WAI0050<FLJ0431:0048<INI<END\n\
\n\
#0048\n\
<SMC<LDP<END\n\
\n\
#0049\n\
<CLO<FAO0004<ESC\n\
\n\
XX: head.tsc   4000 - 4099\n\
4000:Almond";
