#ifndef _FB_RESULT_H_
#define _FB_RESULT_H_

#include <stdint.h>

enum class ResultCode_t : uint8_t { SUCCESS = 0x0000 };

#ifndef FRUIT_BOWL_NO_SEVERITY
enum ResultSeverity_t { WARNING = 1, ERROR = 2, CRITICAL = 3 };
#endif /* FRUIT_BOWL_NO_SEVERITY */

struct Result_t {
  ResultCode_t code;
  char *       message;

#ifndef FRUIT_BOWL_NO_SEVERITY
  ResultSeverity_t severity;
#endif /* FRUIT_BOWL_NO_SEVERITY */

  /**
   * @brief Bool cast operator (test for success)
   *
   * @return code == ResultCode_t::SUCCESS
   */
  inline operator bool() const {
    return code == ResultCode_t::SUCCESS;
  }
};

inline bool operator!(const Result_t & result);
inline bool operator==(const Result_t & left, const Result_t & right);
inline bool operator!=(const Result_t & left, const Result_t & right);

#endif /* _FB_RESULT_H_ */