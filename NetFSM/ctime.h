#ifndef CTIME_H
#define CTIME_H

#include <time.h>   // POSIX-таймеры
#include "Deffsa.h"

// Чтобы время засекать. Всё общение с внешним миром идёт в секундах.
class CTime {
    private:
        timespec mark;

    public:
        double mSecond();
        CTime():mark((timespec){0, 0}) { restart(); };
        double elapsed() const { return to_seconds( diff(now(),mark) ); };
        double restart() { timespec oldmark = mark; mark = now(); return to_seconds( diff(mark,oldmark) ); };
        double operator()() const { return elapsed(); };
        double operator()( bool andRestart ) { return (andRestart) ? restart() : elapsed(); };

        static double to_seconds( timespec delta ) { return 1e-9*delta.tv_nsec + (double)delta.tv_sec; };
        static timespec now() { timespec its_now; clock_gettime( CLOCK_REALTIME, &its_now ); return its_now; };
        static timespec diff( const timespec t2,  const timespec t1 );
//        static timespec to_nseconds( ) { return mark.tv_nsec; };
};

#endif /* CTIME_H */

// --- EOF ---
