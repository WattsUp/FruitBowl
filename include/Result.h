#ifndef _FB_RESULT_H_
#define _FB_RESULT_H_

#include "ResultCode.h"

#include <iostream>
#include <stdint.h>
#include <string>

/**
 * @brief Holds an error code and message
 * The message is empty (not using memory) until a custom message is set (by
 * appending a string)
 *
 * The message is implemented as a shared pointer such that copying a result
 * with a custom message does not copy the string. This makes the return code
 * lightweight, not requiring returning a pointer to a result.
 *
 */
class Result {
public:
  Result(ResultCode_t code = ResultCode_t::SUCCESS);
  Result(const Result & result);
  Result & operator=(const Result & result);
  ~Result();

  ResultCode_t    getCode() const;
  const char *    getMessage() const;
  const int16_t * getReferenceCount() const;

  /**
   * @brief Bool cast operator (test for success)
   *
   * @return code == ResultCode_t::SUCCESS
   */
  explicit inline operator bool() const {
    return code == ResultCode_t::SUCCESS;
  }

  const friend Result operator+(const Result & left, const char * right);

private:
  ResultCode_t code           = ResultCode_t::SUCCESS;
  char *       message        = nullptr;
  int16_t *    referenceCount = nullptr;
};

/**
 * @brief Boolean not operator (test for failure)
 *
 * @param result to test
 * @return result.code != ResultCode_t::SUCCESS
 */
inline bool operator!(const Result & result) {
  return result.getCode() != ResultCode_t::SUCCESS;
}

/**
 * @brief Boolean equality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code == right.code
 */
inline bool operator==(const Result & left, const Result & right) {
  return left.getCode() == right.getCode();
}

/**
 * @brief Boolean equality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code == right
 */
inline bool operator==(const Result & left, const ResultCode_t & right) {
  return left.getCode() == right;
}

/**
 * @brief Boolean inequality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code != right.code
 */
inline bool operator!=(const Result & left, const Result & right) {
  return left.getCode() != right.getCode();
}

/**
 * @brief Boolean inequality operator
 *
 * @param left hand side
 * @param right hand side
 * @return left.code != right
 */
inline bool operator!=(const Result & left, const ResultCode_t & right) {
  return left.getCode() != right;
}

/**
 * @brief Addition operator for appending a string
 *
 * @param left hand side - a result
 * @param right hand side - a string to append
 * @return Result_t combined result
 */
inline Result operator+(const Result & left, const std::string & right) {
  return left + right.c_str();
}

std::ostream & operator<<(std::ostream & stream, const Result & result);

#endif /* _FB_RESULT_H_ */