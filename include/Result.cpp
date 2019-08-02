#include "Result.h"

/**
 * @brief Construct a new Result object
 * Create a new referenceCount equal to 1
 *
 * @param code to initialize
 */
Result::Result(ResultCode_t code) : code(code), referenceCount(new int16_t) {
  *referenceCount = 1;
}

/**
 * @brief Copy constructor
 * Copy the values and increment referenceCount
 *
 * @param result to copy
 */
Result::Result(const Result & result) :
  code(result.code), message(result.message),
  referenceCount(result.referenceCount) {
  ++(*referenceCount);
}

/**
 * @brief Assignment operator
 * Decrement the left hand side and delete if zero references
 * Set the left hand side to the right and increment its counter
 *
 * @param result to assign
 * @return Result&
 */
Result & Result::operator=(const Result & result) {
  if (this != &result) {
    if (referenceCount != nullptr && (--(*referenceCount)) <= 0) {
      delete referenceCount;
      delete message;
    }
    code           = result.code;
    message        = result.message;
    referenceCount = result.referenceCount;
    ++(*referenceCount);
  }
  return *this;
}

/**
 * @brief Destroy the Result object
 * Decrement the reference counter and delete the memory if zero references
 *
 * Deletes the message string if present
 */
Result::~Result() {
  if (referenceCount != nullptr) {
    (*referenceCount)--;
    if (*referenceCount <= 0) {
      delete referenceCount;
      delete message;
      referenceCount = nullptr;
      message        = nullptr;
    }
  }
}

/**
 * @brief Get the code of the result
 *
 * @return ResultCode_t
 */
ResultCode_t Result::getCode() const {
  return code;
}

/**
 * @brief Get the message of the result
 *
 * @return const char*
 */
const char * Result::getMessage() const {
  if (message == nullptr)
    return Results::MESSAGES[static_cast<uint8_t>(code)];
  return message;
}

/**
 * @brief Get reference count, number of references to message string
 *
 * @return int16_t
 */
const int16_t * Result::getReferenceCount() const {
  return referenceCount;
}

/**
 * @brief Addition operator for appending a string
 * Create a new result, set its code and severity to the left hand side
 * Set the new result's message to the left's appended by the right string
 * Return the new result
 *
 * @param left hand side - a result
 * @param right hand side - a string to append
 * @return Result combined result
 */
const Result operator+(const Result & left, const char * right) {
  Result result(left.getCode());

  // 5 for "\n  ->", 1 for '\0'
  size_t length = strlen(left.getMessage()) + 5 + strlen(right) + 1;

  result.message = new char[length];
  snprintf(result.message, length, "%s\n  ->%s", left.getMessage(), right);
  return result;
}

/**
 * @brief Output stream insertion operator
 *
 * @param stream to write to
 * @param result to insert
 * @return std::ostream& original stream
 */
std::ostream & operator<<(std::ostream & stream, const Result & result) {
  return stream << result.getMessage();
}