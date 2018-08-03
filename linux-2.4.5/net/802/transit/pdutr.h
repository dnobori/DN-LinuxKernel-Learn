#include "linux/autoconf.h"

/* this file was generated on Thu Jan  8 00:21:19 GMT 1998  */

/* index name #defines: */

#define ADM            0
#define CONN           1
#define RESET_WAIT     2
#define RESET_CHECK    3
#define SETUP          4
#define RESET          5
#define D_CONN         6
#define ERROR          7
#define NORMAL         8
#define BUSY           9
#define REJECT        10
#define AWAIT         11
#define AWAIT_BUSY    12
#define AWAIT_REJECT  13


/* size of transition table is 1684 bytes */

static short int pdutr_offset [ ] ={
      0,   54,   82,  110,  138,  192,  246,  300,  328,  554,
    780, 1006, 1232, 1458 };

static char pdutr_entry [ ] = {
   ADM5          , ADM           , ADM4          , ADM           , ADM5          , ADM           ,
   ADM4          , ADM           , ADM5          , ADM           , ADM4          , ADM           ,
   ADM5          , ADM           , ADM4          , ADM           , ADM3          , ADM           ,
   ADM3          , ADM           , ADM2          , CONN          , ADM2          , CONN          ,
   ADM5          , ADM           , ADM5          , ADM           , ADM5          , ADM           ,
   ADM5          , ADM           , ADM5          , ADM           , ADM5          , ADM           ,
   ADM5          , ADM           , ADM5          , ADM           , ADM5          , ADM           ,
   ADM5          , ADM           , ADM5          , ADM           , ADM5          , ADM           ,
   ADM5          , ADM           , ADM5          , ADM           , ADM5          , ADM           ,
   CONN5         , CONN          , CONN5         , CONN          , CONN5         , CONN          ,
   CONN5         , CONN          , CONN5         , CONN          , CONN3         , CONN          ,
   CONN5         , CONN          , CONN5         , CONN          , CONN5         , CONN          ,
   CONN5         , CONN          , CONN5         , CONN          , CONN4         , ADM           ,
   CONN5         , CONN          , CONN5         , CONN          , RESWAIT8      , RESET_WAIT    ,
   RESWAIT8      , RESET_WAIT    , RESWAIT8      , RESET_WAIT    , RESWAIT8      , RESET_WAIT    ,
   RESWAIT7      , RESET_WAIT    , RESWAIT6      , RESET_WAIT    , RESWAIT8      , RESET_WAIT    ,
   RESWAIT8      , RESET_WAIT    , RESWAIT8      , RESET_WAIT    , RESWAIT8      , RESET_WAIT    ,
   RESWAIT8      , RESET_WAIT    , RESWAIT5      , ADM           , RESWAIT8      , RESET_WAIT    ,
   RESWAIT8      , RESET_WAIT    , RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   ,
   RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   , RESCHK5       , ADM           ,
   RESCHK4       , RESET_CHECK   , RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   ,
   RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   ,
   RESCHK3       , ADM           , RESCHK6       , RESET_CHECK   , RESCHK6       , RESET_CHECK   ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP4        , ADM           ,
   SETUP4        , ADM           , SETUP1        , SETUP         , SETUP1        , SETUP         ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   SETUP2        , NORMAL        , SETUP5        , ADM           , SETUP5        , ADM           ,
   SETUP6        , SETUP         , SETUP6        , SETUP         , SETUP6        , SETUP         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET4        , ADM           ,
   RESET4        , ADM           , RESET1        , RESET         , RESET1        , RESET         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   RESET2        , NORMAL        , RESET5        , ADM           , RESET5        , ADM           ,
   RESET6        , RESET         , RESET6        , RESET         , RESET6        , RESET         ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN3       , D_CONN        ,
   D_CONN3       , D_CONN        , D_CONN1       , ADM           , D_CONN1       , ADM           ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   D_CONN4       , ADM           , D_CONN4       , ADM           , D_CONN5       , ADM           ,
   D_CONN5       , D_CONN        , D_CONN5       , D_CONN        , D_CONN5       , D_CONN        ,
   ERR5          , ERROR         , ERR5          , ERROR         , ERR5          , ERROR         ,
   ERR5          , ERROR         , ERR2          , ADM           , ERR1          , RESET_CHECK   ,
   ERR6          , ERROR         , ERR6          , ERROR         , ERR6          , ERROR         ,
   ERR6          , ERROR         , ERR6          , ERROR         , ERR3          , ADM           ,
   ERR4          , RESET_WAIT    , ERR4          , RESET_WAIT    , NORMAL8B      , NORMAL        ,
   NORMAL9       , NORMAL        , NORMAL10      , NORMAL        , NORMAL10      , NORMAL        ,
   NORMAL5       , REJECT        , NORMAL6       , REJECT        , NORMAL7       , REJECT        ,
   NORMAL7       , REJECT        , NORMAL11      , NORMAL        , NORMAL11      , NORMAL        ,
   NORMAL12      , NORMAL        , NORMAL12      , NORMAL        , NORMAL11      , NORMAL        ,
   NORMAL11      , NORMAL        , NORMAL12      , NORMAL        , NORMAL12      , NORMAL        ,
   NORMAL13      , NORMAL        , NORMAL13      , NORMAL        , NORMAL14      , NORMAL        ,
   NORMAL14      , NORMAL        , NORMAL13      , NORMAL        , NORMAL13      , NORMAL        ,
   NORMAL14      , NORMAL        , NORMAL14      , NORMAL        , NORMAL15      , NORMAL        ,
   NORMAL16      , NORMAL        , NORMAL17      , NORMAL        , NORMAL17      , NORMAL        ,
   NORMAL15      , NORMAL        , NORMAL16      , NORMAL        , NORMAL17      , NORMAL        ,
   NORMAL17      , NORMAL        , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , NORMAL8B      , NORMAL        ,
   NORMAL9       , NORMAL        , SH10          , ERROR         , NORMAL8A      , NORMAL        ,
   NORMAL5       , REJECT        , NORMAL6       , REJECT        , SH10          , ERROR         ,
   NORMAL5       , REJECT        , NORMAL11      , NORMAL        , NORMAL11      , NORMAL        ,
   SH10          , ERROR         , NORMAL11      , NORMAL        , NORMAL11      , NORMAL        ,
   NORMAL11      , NORMAL        , SH10          , ERROR         , NORMAL11      , NORMAL        ,
   NORMAL13      , NORMAL        , NORMAL13      , NORMAL        , SH10          , ERROR         ,
   NORMAL13      , NORMAL        , NORMAL13      , NORMAL        , NORMAL13      , NORMAL        ,
   SH10          , ERROR         , NORMAL13      , NORMAL        , NORMAL15      , NORMAL        ,
   NORMAL16      , NORMAL        , SH10          , ERROR         , NORMAL15      , NORMAL        ,
   NORMAL15      , NORMAL        , NORMAL16      , NORMAL        , SH10          , ERROR         ,
   NORMAL15      , NORMAL        , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , BUSY13        , BUSY          , BUSY14        , BUSY          ,
   BUSY12        , BUSY          , BUSY12        , BUSY          , BUSY9         , BUSY          ,
   BUSY10        , BUSY          , BUSY11        , BUSY          , BUSY11        , BUSY          ,
   BUSY15        , BUSY          , BUSY15        , BUSY          , BUSY16        , BUSY          ,
   BUSY16        , BUSY          , BUSY15        , BUSY          , BUSY15        , BUSY          ,
   BUSY16        , BUSY          , BUSY16        , BUSY          , BUSY17        , BUSY          ,
   BUSY17        , BUSY          , BUSY18        , BUSY          , BUSY18        , BUSY          ,
   BUSY17        , BUSY          , BUSY17        , BUSY          , BUSY18        , BUSY          ,
   BUSY18        , BUSY          , BUSY19        , BUSY          , BUSY20        , BUSY          ,
   BUSY21        , BUSY          , BUSY21        , BUSY          , BUSY19        , BUSY          ,
   BUSY20        , BUSY          , BUSY21        , BUSY          , BUSY21        , BUSY          ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , BUSY13        , BUSY          , BUSY14        , BUSY          ,
   SH10          , ERROR         , BUSY13        , BUSY          , BUSY9         , BUSY          ,
   BUSY10        , BUSY          , SH10          , ERROR         , BUSY9         , BUSY          ,
   BUSY15        , BUSY          , BUSY15        , BUSY          , SH10          , ERROR         ,
   BUSY15        , BUSY          , BUSY15        , BUSY          , BUSY15        , BUSY          ,
   SH10          , ERROR         , BUSY15        , BUSY          , BUSY17        , BUSY          ,
   BUSY17        , BUSY          , SH10          , ERROR         , BUSY17        , BUSY          ,
   BUSY17        , BUSY          , BUSY17        , BUSY          , SH10          , ERROR         ,
   BUSY17        , BUSY          , BUSY19        , BUSY          , BUSY20        , BUSY          ,
   SH10          , ERROR         , BUSY19        , BUSY          , BUSY19        , BUSY          ,
   BUSY20        , BUSY          , SH10          , ERROR         , BUSY19        , BUSY          ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   REJECT7       , REJECT        , REJECT8       , REJECT        , REJECT9       , REJECT        ,
   REJECT9       , REJECT        , REJECT5       , REJECT        , REJECT5       , REJECT        ,
   REJECT6       , REJECT        , REJECT6       , REJECT        , REJECT10      , REJECT        ,
   REJECT10      , REJECT        , REJECT11      , REJECT        , REJECT11      , REJECT        ,
   REJECT10      , REJECT        , REJECT10      , REJECT        , REJECT11      , REJECT        ,
   REJECT11      , REJECT        , REJECT12      , REJECT        , REJECT12      , REJECT        ,
   REJECT13      , REJECT        , REJECT13      , REJECT        , REJECT12      , REJECT        ,
   REJECT12      , REJECT        , REJECT13      , REJECT        , REJECT13      , REJECT        ,
   REJECT14      , REJECT        , REJECT15      , REJECT        , REJECT16      , REJECT        ,
   REJECT16      , REJECT        , REJECT14      , REJECT        , REJECT15      , REJECT        ,
   REJECT16      , REJECT        , REJECT16      , REJECT        , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   REJECT7       , REJECT        , REJECT8       , REJECT        , SH10          , ERROR         ,
   REJECT7       , REJECT        , REJECT5       , REJECT        , REJECT5       , REJECT        ,
   SH10          , ERROR         , REJECT5       , REJECT        , REJECT10      , REJECT        ,
   REJECT10      , REJECT        , SH10          , ERROR         , REJECT10      , REJECT        ,
   REJECT10      , REJECT        , REJECT10      , REJECT        , SH10          , ERROR         ,
   REJECT10      , REJECT        , REJECT12      , REJECT        , REJECT12      , REJECT        ,
   SH10          , ERROR         , REJECT12      , REJECT        , REJECT12      , REJECT        ,
   REJECT12      , REJECT        , SH10          , ERROR         , REJECT12      , REJECT        ,
   REJECT14      , REJECT        , REJECT15      , REJECT        , SH10          , ERROR         ,
   REJECT14      , REJECT        , REJECT14      , REJECT        , REJECT15      , REJECT        ,
   SH10          , ERROR         , REJECT14      , REJECT        , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , AWAIT6        , AWAIT         ,
   AWAIT6        , AWAIT         , AWAIT7        , AWAIT         , AWAIT7        , AWAIT         ,
   AWAIT3        , AWAIT_REJECT  , AWAIT3        , AWAIT_REJECT  , AWAIT4        , AWAIT_REJECT  ,
   AWAIT4        , AWAIT_REJECT  , AWAIT9        , AWAIT         , AWAIT9        , AWAIT         ,
   AWAIT10       , AWAIT         , AWAIT10       , AWAIT         , AWAIT9        , AWAIT         ,
   AWAIT9        , AWAIT         , AWAIT10       , AWAIT         , AWAIT10       , AWAIT         ,
   AWAIT12       , AWAIT         , AWAIT12       , AWAIT         , AWAIT13       , AWAIT         ,
   AWAIT13       , AWAIT         , AWAIT12       , AWAIT         , AWAIT12       , AWAIT         ,
   AWAIT13       , AWAIT         , AWAIT13       , AWAIT         , AWAIT9        , AWAIT         ,
   AWAIT9        , AWAIT         , AWAIT10       , AWAIT         , AWAIT10       , AWAIT         ,
   AWAIT9        , AWAIT         , AWAIT9        , AWAIT         , AWAIT10       , AWAIT         ,
   AWAIT10       , AWAIT         , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , AWAIT6        , AWAIT         ,
   AWAIT6        , AWAIT         , SH10          , ERROR         , AWAIT5        , NORMAL        ,
   AWAIT3        , AWAIT_REJECT  , AWAIT3        , AWAIT_REJECT  , SH10          , ERROR         ,
   AWAIT2        , REJECT        , AWAIT9        , AWAIT         , AWAIT9        , AWAIT         ,
   SH10          , ERROR         , AWAIT8        , AWAIT         , AWAIT9        , AWAIT         ,
   AWAIT9        , AWAIT         , SH10          , ERROR         , AWAIT8        , AWAIT         ,
   AWAIT12       , AWAIT         , AWAIT12       , AWAIT         , SH10          , ERROR         ,
   AWAIT11       , AWAIT         , AWAIT12       , AWAIT         , AWAIT12       , AWAIT         ,
   SH10          , ERROR         , AWAIT11       , AWAIT         , AWAIT9        , AWAIT         ,
   AWAIT9        , AWAIT         , SH10          , ERROR         , AWAIT8        , AWAIT         ,
   AWAIT9        , AWAIT         , AWAIT9        , AWAIT         , SH10          , ERROR         ,
   AWAIT8        , AWAIT         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , AWAIT_BUSY8   , AWAIT_BUSY    , AWAIT_BUSY8   , AWAIT_BUSY    ,
   AWAIT_BUSY9   , AWAIT_BUSY    , AWAIT_BUSY9   , AWAIT_BUSY    , AWAIT_BUSY5   , AWAIT_BUSY    ,
   AWAIT_BUSY5   , AWAIT_BUSY    , AWAIT_BUSY6   , AWAIT_BUSY    , AWAIT_BUSY6   , AWAIT_BUSY    ,
   AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY12  , AWAIT_BUSY    ,
   AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    ,
   AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY14  , AWAIT_BUSY    ,
   AWAIT_BUSY14  , AWAIT_BUSY    , AWAIT_BUSY15  , AWAIT_BUSY    , AWAIT_BUSY15  , AWAIT_BUSY    ,
   AWAIT_BUSY14  , AWAIT_BUSY    , AWAIT_BUSY14  , AWAIT_BUSY    , AWAIT_BUSY15  , AWAIT_BUSY    ,
   AWAIT_BUSY15  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    ,
   AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    ,
   AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY12  , AWAIT_BUSY    , AWAIT_BUSY12  , AWAIT_BUSY    ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , AWAIT_BUSY8   , AWAIT_BUSY    , AWAIT_BUSY8   , AWAIT_BUSY    ,
   SH10          , ERROR         , AWAIT_BUSY7   , BUSY          , AWAIT_BUSY5   , AWAIT_BUSY    ,
   AWAIT_BUSY5   , AWAIT_BUSY    , SH10          , ERROR         , AWAIT_BUSY4   , BUSY          ,
   AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    , SH10          , ERROR         ,
   AWAIT_BUSY10  , BUSY          , AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    ,
   SH10          , ERROR         , AWAIT_BUSY10  , BUSY          , AWAIT_BUSY14  , AWAIT_BUSY    ,
   AWAIT_BUSY14  , AWAIT_BUSY    , SH10          , ERROR         , AWAIT_BUSY13  , BUSY          ,
   AWAIT_BUSY14  , AWAIT_BUSY    , AWAIT_BUSY14  , AWAIT_BUSY    , SH10          , ERROR         ,
   AWAIT_BUSY13  , BUSY          , AWAIT_BUSY11  , AWAIT_BUSY    , AWAIT_BUSY11  , AWAIT_BUSY    ,
   SH10          , ERROR         , AWAIT_BUSY10  , BUSY          , AWAIT_BUSY11  , AWAIT_BUSY    ,
   AWAIT_BUSY11  , AWAIT_BUSY    , SH10          , ERROR         , AWAIT_BUSY10  , BUSY          ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   AWAIT_REJECT5 , AWAIT         , AWAIT_REJECT5 , AWAIT         , AWAIT_REJECT6 , AWAIT         ,
   AWAIT_REJECT6 , AWAIT         , AWAIT_REJECT2 , AWAIT_REJECT  , AWAIT_REJECT2 , AWAIT_REJECT  ,
   AWAIT_REJECT3 , AWAIT_REJECT  , AWAIT_REJECT3 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  ,
   AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT9 , AWAIT_REJECT  , AWAIT_REJECT9 , AWAIT_REJECT  ,
   AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT9 , AWAIT_REJECT  ,
   AWAIT_REJECT9 , AWAIT_REJECT  , AWAIT_REJECT11, AWAIT_REJECT  , AWAIT_REJECT11, AWAIT_REJECT  ,
   AWAIT_REJECT12, AWAIT_REJECT  , AWAIT_REJECT12, AWAIT_REJECT  , AWAIT_REJECT11, AWAIT_REJECT  ,
   AWAIT_REJECT11, AWAIT_REJECT  , AWAIT_REJECT12, AWAIT_REJECT  , AWAIT_REJECT12, AWAIT_REJECT  ,
   AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT9 , AWAIT_REJECT  ,
   AWAIT_REJECT9 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  ,
   AWAIT_REJECT9 , AWAIT_REJECT  , AWAIT_REJECT9 , AWAIT_REJECT  , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH4           , ADM           , SH4           , ADM           ,
   SH4           , ADM           , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   SH3           , RESET_CHECK   , SH3           , RESET_CHECK   , SH3           , RESET_CHECK   ,
   AWAIT_REJECT5 , AWAIT         , AWAIT_REJECT5 , AWAIT         , SH10          , ERROR         ,
   AWAIT_REJECT4 , NORMAL        , AWAIT_REJECT2 , AWAIT_REJECT  , AWAIT_REJECT2 , AWAIT_REJECT  ,
   SH10          , ERROR         , AWAIT_REJECT4 , NORMAL        , AWAIT_REJECT8 , AWAIT_REJECT  ,
   AWAIT_REJECT8 , AWAIT_REJECT  , SH10          , ERROR         , AWAIT_REJECT7 , REJECT        ,
   AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  , SH10          , ERROR         ,
   AWAIT_REJECT7 , REJECT        , AWAIT_REJECT11, AWAIT_REJECT  , AWAIT_REJECT11, AWAIT_REJECT  ,
   SH10          , ERROR         , AWAIT_REJECT10, REJECT        , AWAIT_REJECT11, AWAIT_REJECT  ,
   AWAIT_REJECT11, AWAIT_REJECT  , SH10          , ERROR         , AWAIT_REJECT10, REJECT        ,
   AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  , SH10          , ERROR         ,
   AWAIT_REJECT7 , REJECT        , AWAIT_REJECT8 , AWAIT_REJECT  , AWAIT_REJECT8 , AWAIT_REJECT  ,
   SH10          , ERROR         , AWAIT_REJECT7 , REJECT        , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH9           , ERROR         , SH9           , ERROR         ,
   SH9           , ERROR         , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH6           , ADM           , SH6           , ADM           , SH6           , ADM           ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH5           , RESET_WAIT    ,
   SH5           , RESET_WAIT    , SH5           , RESET_WAIT    , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR         , SH7           , ERROR         ,
   SH7           , ERROR         , SH7           , ERROR          };
