#ifndef _FB_RESULT_H_
#define _FB_RESULT_H_

#include <iostream>
#include <stdint.h>
#include <string>

enum class ResultCode_t : uint8_t {
  SUCCESS           = 0x00,
  INVALID_FUNCTION  = 0x01,
  ACCESS_DENIED     = 0x02,
  NOT_ENOUGH_MEMORY = 0x03,
  INVALID_DATA      = 0x04,
  DISK_FULL         = 0x05,
  BAD_COMMAND       = 0x06,
  CRC               = 0x07,
  WRITE_FAULT       = 0x08,
  READ_FAULT        = 0x09,
  END_OF_FILE       = 0x0A,
  NOT_SUPPORTED     = 0x0B,
  FILE_EXISTS       = 0x0C,
  CANNOT_MAKE       = 0x0D,
  INVALID_PASSWORD  = 0x0E,
  INVALID_PARAMETER = 0x0F,
  OPEN_FAILED       = 0x10,
  BUFFER_OVERFLOW   = 0x11,
  DIR_NOT_EMPTY     = 0x12,
  BIND_FAILED       = 0x13,
  INVALID_UTF8      = 0x14,
  UNKNOWN_HASH      = 0x15,
  UNKNOWN_REFERENCE = 0x16,
  EXCEPTION_OCCURED = 0x17,
  UNDEFINED_PARENT  = 0x18,
  INCOMPLETE        = 0x19,
  NO_OPERATION      = 0x1A,
  TIMEOUT           = 0x1B,
  NO_SYSTEM_CALL    = 0x1C,
  INVALID_STATE     = 0x1D
};

#ifndef FRUIT_BOWL_NO_SEVERITY
enum ResultSeverity_t { INFO = 0, WARNING = 1, ERROR = 2, CRITICAL = 3 };
#endif /* FRUIT_BOWL_NO_SEVERITY */

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

#ifndef FRUIT_BOWL_NO_SEVERITY
  ResultSeverity_t severity = ResultSeverity_t::INFO;
#endif /* FRUIT_BOWL_NO_SEVERITY */
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
 * @brief Boolean not operator (test for failure)
 *
 * @param code to test
 * @return code != ResultCode_t::SUCCESS
 */
inline bool operator!(const ResultCode_t & code) {
  return code != ResultCode_t::SUCCESS;
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

namespace Results {

// clang-format off
static const char * MESSAGES[] = {
  "[0x00] The operation completed successfully",
  "[0x01] Incorrect function called",
  "[0x02] Access is denied",
  "[0x03] Not enough memory to complete the command",
  "[0x04] The data is invalid",
  "[0x05] Not enough disk space to complete the command",
  "[0x06] The command is not recognized",
  "[0x07] Data error (cyclic redundency check)",
  "[0x08] Cannot write to the specified device",
  "[0x09] Cannot read from the specified device",
  "[0x0A] Reached EOF before completing the command",
  "[0x0B] The command is not supported",
  "[0x0C] The file already exists",
  "[0x0D] Cannot create the specified directory or file",
  "[0x0E] The specified password is not correct",
  "[0x0F] The specified parameter is not correct",
  "[0x10] Could not open the specified file or device",
  "[0x11] The buffer exceeded its size",
  "[0x12] The directory is not empty",
  "[0x13] Could not bind to the specified address",
  "[0x14] The character does not follow the UTF8 standard",
  "[0x15] The hash is not recognized in the list of known hashes",
  "[0x16] The reference is to an undefined object",
  "[0x17] The command encountered an exception",
  "[0x18] The parent of the object is undefined",
  "[0x19] The operation has not completed",
  "[0x1A] No operation was performed",
  "[0x1B] The operation did not complete before a timeout expired",
  "[0x1C] System call is not available to use",
  "[0x1D] The current state is not valid"
};
// clang-format on

} // namespace Results

#endif /* _FB_RESULT_H_ */