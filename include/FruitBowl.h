#ifndef _FB_FRUIT_BOWL_H_
#define _FB_FRUIT_BOWL_H_

#include "Hash.h"
#include "Result.h"

#ifndef FRUIT_BOWL_NO_CHRONO
#include <chrono>

typedef std::chrono::milliseconds          millis_t;
typedef std::chrono::microseconds          micros_t;
typedef std::chrono::nanoseconds           nanos_t;
typedef std::chrono::high_resolution_clock clockHP_t;
typedef std::chrono::steady_clock          clockStd_t;

#endif /* FRUIT_BOWL_NO_CHRONO */

#endif /* _FRUIT_BOWL_H_ */