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

struct Result_t {
  ResultCode_t code    = ResultCode_t::SUCCESS;
  char *       message = nullptr;

#ifndef FRUIT_BOWL_NO_SEVERITY
  ResultSeverity_t severity = ResultSeverity_t::INFO;
#endif /* FRUIT_BOWL_NO_SEVERITY */

  /**
   * @brief Construct a new Result_t object
   *
   * @param code to initialize
   */
  Result_t(ResultCode_t code = ResultCode_t::SUCCESS) : code(code) {}

  /**
   * @brief Copy constructor
   *
   * @param result to copy
   */
  Result_t(const Result_t & result) {}

  /**
   * @brief Assignment operator
   *
   * @param result to assign
   * @return Result_t&
   */
  Result_t & operator=(const Result_t & result) {
    return *this;
  }

  /**
   * @brief Destroy the Result_t object
   *
   * Deletes the message string if present
   */
  ~Result_t() {
    if (message != nullptr)
      delete message;
  }

  /**
   * @brief Bool cast operator (test for success)
   *
   * @return code == ResultCode_t::SUCCESS
   */
  explicit inline operator bool() const {
    return code == ResultCode_t::SUCCESS;
  }
};

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

Result_t operator+(const Result_t & left, const char * right);

/**
 * @brief Addition operator for appending a string
 *
 * @param left hand side - a result
 * @param right hand side - a string to append
 * @return Result_t combined result
 */
inline Result_t operator+(const Result_t & left, const std::string & right) {
  return left + right.c_str();
}

std::ostream & operator<<(std::ostream & stream, const Result_t & result);

namespace Results {
static const Result_t SUCCESS           = {ResultCode_t::SUCCESS};
static const Result_t INVALID_FUNCTION  = {ResultCode_t::INVALID_FUNCTION};
static const Result_t ACCESS_DENIED     = {ResultCode_t::ACCESS_DENIED};
static const Result_t INVALID_DATA      = {ResultCode_t::INVALID_DATA};
static const Result_t DISK_FULL         = {ResultCode_t::DISK_FULL};
static const Result_t BAD_COMMAND       = {ResultCode_t::BAD_COMMAND};
static const Result_t CRC               = {ResultCode_t::CRC};
static const Result_t WRITE_FAULT       = {ResultCode_t::WRITE_FAULT};
static const Result_t READ_FAULT        = {ResultCode_t::READ_FAULT};
static const Result_t END_OF_FILE       = {ResultCode_t::END_OF_FILE};
static const Result_t NOT_SUPPORTED     = {ResultCode_t::NOT_SUPPORTED};
static const Result_t FILE_EXISTS       = {ResultCode_t::FILE_EXISTS};
static const Result_t CANNOT_MAKE       = {ResultCode_t::CANNOT_MAKE};
static const Result_t INVALID_PASSWORD  = {ResultCode_t::INVALID_PASSWORD};
static const Result_t INVALID_PARAMETER = {ResultCode_t::INVALID_PARAMETER};
static const Result_t OPEN_FAILED       = {ResultCode_t::OPEN_FAILED};
static const Result_t BUFFER_OVERFLOW   = {ResultCode_t::BUFFER_OVERFLOW};
static const Result_t DIR_NOT_EMPTY     = {ResultCode_t::DIR_NOT_EMPTY};
static const Result_t BIND_FAILED       = {ResultCode_t::BIND_FAILED};
static const Result_t INVALID_UTF8      = {ResultCode_t::INVALID_UTF8};
static const Result_t UNKNOWN_HASH      = {ResultCode_t::UNKNOWN_HASH};
static const Result_t UNKNOWN_REFERENCE = {ResultCode_t::UNKNOWN_REFERENCE};
static const Result_t EXCEPTION_OCCURED = {ResultCode_t::EXCEPTION_OCCURED};
static const Result_t UNDEFINED_PARENT  = {ResultCode_t::UNDEFINED_PARENT};
static const Result_t INCOMPLETE        = {ResultCode_t::INCOMPLETE};
static const Result_t NO_OPERATION      = {ResultCode_t::NO_OPERATION};
static const Result_t TIMEOUT           = {ResultCode_t::TIMEOUT};
static const Result_t NO_SYSTEM_CALL    = {ResultCode_t::NO_SYSTEM_CALL};
static const Result_t INVALID_STATE     = {ResultCode_t::INVALID_STATE};

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