#include "Result.h"

/**
 * @brief Addition operator for appending a string
 * Create a new result, set its code and severity to the left hand side
 * Set the new result's message to the left's appended by the right string
 * Return the new result
 *
 * @param left hand side - a result
 * @param right hand side - a string to append
 * @return Result_t combined result
 */
const Result_t operator+(const Result_t & left, const char * right) {
  Result_t result;
  result.code = left.code;

#ifndef FRUIT_BOWL_NO_SEVERITY
  result.severity = left.severity;
#endif /* FRUIT_BOWL_NO_SEVERITY */

  const char * leftStr = left.message;
  if (leftStr == nullptr)
    leftStr = Results::MESSAGES[static_cast<uint8_t>(result.code)];

  size_t length =
      strlen(leftStr) + 5 + strlen(right) + 1; // 5 for "\n  ->", 1 for '\0'
  result.message = new char[length];
  snprintf(result.message, length, "%s\n  ->%s", leftStr, right);
  return result;
}

/**
 * @brief Output stream insertion operator
 *
 * @param stream to write to
 * @param result to insert
 * @return std::ostream& original stream
 */
std::ostream & operator<<(std::ostream & stream, const Result_t & result) {
  if (result.message == nullptr)
    return stream << Results::MESSAGES[static_cast<uint8_t>(result.code)];
  return stream << result.message;
}