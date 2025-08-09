#include "ctime.h"

// -------------------------------------------------------------------------------------------------
timespec CTime::diff( const timespec t2,  const timespec t1 )
{
    timespec res = { t2.tv_sec - t1.tv_sec, t2.tv_nsec - t1.tv_nsec };
    if (0 > res.tv_nsec) {
        res.tv_nsec += 1000000000;
        res.tv_sec--;
    }
    return res;
}

double CTime::mSecond(){
    return elapsed()*1000;
}

// --- EOF ---
