#include <FruitBowl.h>
#include <Result.h>

#include <iostream>
#include <sstream>
#include <string>

Result_t testRecursion(int n) {
  if (n == 0)
    return ResultCode_t::BUFFER_OVERFLOW + "Base case reached";
  else
    return testRecursion(n - 1) + ("n=" + std::to_string(n));
}

/**
 * @brief Test the result class
 *
 * @param printPass will print when cases are passing if true, only fails if
 * false
 * @return Result_t
 */
Result_t testResult(bool printPass = true) {
  Result_t testResult;
  if (testResult.referenceCount && *testResult.referenceCount == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after initialization\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after initialization\n";
    return ResultCode_t::INVALID_STATE;
  }

  testResult = testResult;
  if (testResult.referenceCount && *testResult.referenceCount == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after self assignment\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after self assignment\n";
    return ResultCode_t::INVALID_STATE;
  }

  Result_t copy = testResult + "Append text";
  if (copy.referenceCount && *copy.referenceCount == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after appending string\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after appending string\n";
    return ResultCode_t::INVALID_STATE;
  }

  if (testResult.code == ResultCode_t::SUCCESS) {
    if (printPass)
      std::cout << "[PASS] Empty initializer is SUCCESS\n";
  } else {
    std::cout << "[FAIL] Empty initializer is not SUCCESS\n";
    return ResultCode_t::INVALID_STATE;
  }

  if (testResult == ResultCode_t::SUCCESS) {
    if (printPass)
      std::cout << "[PASS] Equality comparison does work with SUCCESS\n";
  } else {
    std::cout << "[FAIL] Equality comparison does not work with SUCCESS\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  if (testResult) {
    if (printPass)
      std::cout << "[PASS] operator bool() does work with SUCCESS\n";
  } else {
    std::cout << "[FAIL] operator bool() does not work with SUCCESS\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  if (!testResult) {
    std::cout << "[FAIL] boolean not operator does not work with SUCCESS\n";
    return ResultCode_t::INVALID_FUNCTION;
  } else {
    if (printPass)
      std::cout << "[PASS] boolean not operator does work with SUCCESS\n";
  }

  testResult = ResultCode_t::CRC;
  if (testResult) {
    std::cout << "[FAIL] operator bool() does not work with CRC\n";
    return ResultCode_t::INVALID_FUNCTION;
  } else {
    if (printPass)
      std::cout << "[PASS] operator bool() does work with CRC\n";
  }

  if (!testResult) {
    if (printPass)
      std::cout << "[PASS] boolean not operator does work with CRC\n";
  } else {
    std::cout << "[FAIL] boolean not operator does not work with CRC\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  std::stringstream string;
  string << testResult;
  if (string.str().compare("[0x07] Data error (cyclic redundency check)") ==
      0) {
    if (printPass) {
      std::cout << "####\n" << testResult << "\n####\n";
      std::cout << "[PASS] stream insertion operator does work with CRC\n";
    }
  } else {
    std::cout << "####\n" << testResult << "\n####\n";
    std::cout << "[FAIL] stream insertion operator does not work with CRC\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  testResult = testRecursion(8);
  if (testResult) {
    std::cout << "[FAIL] operator bool() does not work with testRecursion\n";
    return ResultCode_t::INVALID_FUNCTION;
  } else {
    if (printPass)
      std::cout << "[PASS] operator bool() does work with testRecursion\n";
  }

  string.str("");
  string.clear();
  string << testResult;
  if (string.str().compare("[0x11] The buffer exceeded its size\n"
                           "  ->Base case reached\n"
                           "  ->n=1\n"
                           "  ->n=2\n"
                           "  ->n=3\n"
                           "  ->n=4\n"
                           "  ->n=5\n"
                           "  ->n=6\n"
                           "  ->n=7\n"
                           "  ->n=8") == 0) {
    if (printPass) {
      std::cout << "####\n" << testResult << "\n####\n";
      std::cout
          << "[PASS] stream insertion operator does work with testRecursion\n";
    }
  } else {
    std::cout << "####\n" << string.str() << "\n####\n";
    std::cout << "[FAIL] stream insertion operator does not work with "
                 "testRecursion\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  return ResultCode_t::SUCCESS;
}

int main() {
  std::cout << "Testing FruitBowl\n";
  Result_t result = testResult(true);
  if (!result)
    std::cout << "[FAIL] *** Result class does not pass ***\n";

  return 0;
}