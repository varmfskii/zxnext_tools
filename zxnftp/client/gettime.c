#include <time.h>
#include <sys/time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void gettime(struct timespec *ts) {
#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  ts->tv_sec=mts.tv_sec;
  ts->tv_nsec=mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}
