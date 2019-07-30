#include "Result.h"

/**
 * @brief Boolean not operator (test for failure)
 *
 * @param result to test
 * @return result.code != ResultCode_t::SUCCESS
 */
inline bool operator!(const Result_t & result) {
  return result.code != ResultCode_t::SUCCESS;
}

/**
 * @brief Boolean equality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code == right.code
 */
inline bool operator==(const Result_t & left, const Result_t & right) {
  return left.code == right.code;
}

/**
 * @brief Boolean inequality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code != right.code
 */
inline bool operator!=(const Result_t & left, const Result_t & right) {
  return left.code != right.code;
}