#include <cstdio>
#include <stdint.h>

#if defined(__unix__) || defined(__APPLE__) || defined (__CYGWIN__)
#include <time.h>
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#ifdef WIN32
#include <Windows.h>
#endif

#include <vector>
#include "MaxRectsBinPack.h"

using namespace rbp;

uint64_t tick()
{
#if defined(WIN32)
	LARGE_INTEGER ddwTimer;
	BOOL success = QueryPerformanceCounter(&ddwTimer);
	return ddwTimer.QuadPart;
#elif defined(__APPLE__)
	return mach_absolute_time();
#elif defined(_POSIX_MONOTONIC_CLOCK)
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return t.tv_sec * 1000 * 1000 * 1000 + t.tv_nsec;
#elif defined(_POSIX_C_SOURCE)
	timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 * 1000 + t.tv_usec;
#else
	return clock();
#endif
}

uint64_t ticksPerSec()
{
#if defined(WIN32)
	uint64_t ddwTimerFrequency;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&ddwTimerFrequency));
	return ddwTimerFrequency;
#elif defined(__APPLE__)
	mach_timebase_info_data_t timeBaseInfo;
	mach_timebase_info(&timeBaseInfo);
	return 1000000000ULL * (uint64_t)timeBaseInfo.denom / (uint64_t)timeBaseInfo.numer;
#elif defined(_POSIX_MONOTONIC_CLOCK)
	return 1000 * 1000 * 1000;
#elif defined(_POSIX_C_SOURCE) || defined(__APPLE__)
	return 1000 * 1000;
#else
	return CLOCKS_PER_SEC;
#endif
}

bool AreDisjoint(const Rect &a, const Rect &b)
{
	return a.x >= b.x + b.width || a.x + a.width <= b.x ||
		a.y >= b.y + b.height || a.y + a.height <= b.y;
}

bool AllRectsDisjoint(std::vector<Rect> &packed)
{
	for(size_t i = 0; i < packed.size(); ++i)
		for(size_t j = i+1; j < packed.size(); ++j)
		{
			if (!AreDisjoint(packed[i], packed[j]))
				return false;
		}
	return true;
}

int main()
{
	MaxRectsBinPack pack(1024*8, 1024*8, true);

	std::vector<Rect> packed;
	srand(12412);
	uint64_t t0 = tick();
	for(int i = 1; i < 1024*1024; ++i)
	{
		int a = (rand() % 128) + 1;
		int b = (rand() % 128) + 1;
		Rect r = pack.Insert(a, b, MaxRectsBinPack::RectBestShortSideFit);
		if (!r.width)
			break;		
		packed.push_back(r);
	}
	uint64_t t1 = tick();
	printf("Packing %d rectangles took %f msecs. All rects disjoint: %s. Occupancy: %f\n",
		(int)packed.size(), (t1 - t0) * 1000.0 / ticksPerSec(), AllRectsDisjoint(packed) ? "yes" : "NO!", pack.Occupancy());
}
