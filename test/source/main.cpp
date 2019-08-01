#include <FruitBowl.h>
#include <Result.h>

#include <iostream>
#include <sstream>
#include <string>

Result testRecursion(int n) {
  if (n == 0)
    return ResultCode_t::BUFFER_OVERFLOW + "Base case reached";
  else
    return testRecursion(n - 1) + ("n=" + std::to_string(n));
}

static Result lastErrorExternC;

extern "C" ResultCode_t externCFunction() {
  lastErrorExternC = testRecursion(8);
  return lastErrorExternC.getCode();
}

extern "C" const char * getLastErrorExternC() {
  return lastErrorExternC.getMessage();
}

/**
 * @brief Test the result class
 *
 * @param printPass will print when cases are passing if true, only fails if
 * false
 * @return Result
 */
Result testResult(bool printPass = true) {
  Result testResult;
  if (testResult.getReferenceCount() && *testResult.getReferenceCount() == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after initialization\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after initialization\n";
    return ResultCode_t::INVALID_STATE;
  }

  testResult = testResult;
  if (testResult.getReferenceCount() && *testResult.getReferenceCount() == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after self assignment\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after self assignment\n";
    return ResultCode_t::INVALID_STATE;
  }

  Result copy = testResult + "Append text";
  if (copy.getReferenceCount() && *copy.getReferenceCount() == 1) {
    if (printPass)
      std::cout << "[PASS] Reference count is 1 after appending string\n";
  } else {
    std::cout << "[FAIL] Reference count is not 1 after appending string\n";
    return ResultCode_t::INVALID_STATE;
  }

  if (testResult.getCode() == ResultCode_t::SUCCESS) {
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

  if (!externCFunction()) {
    if (printPass) {
      std::cout << "[PASS] externCFunction works\n";
    }
  } else {
    std::cout << "[FAIL] externCFunction does not work\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  string.str("");
  string.clear();
  string << getLastErrorExternC();
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
      std::cout << "[PASS] getLastError does work\n";
    }
  } else {
    std::cout << "####\n" << string.str() << "\n####\n";
    std::cout << "[FAIL] getLastError does not work\n";
    return ResultCode_t::INVALID_FUNCTION;
  }

  return ResultCode_t::SUCCESS;
}

/**
 * @brief Test the hash class
 *
 * @param printPass will print when cases are passing if true, only fails if
 * false
 * @return Result
 */
Result testHash(bool printPass = true) {
  Hash hash;
  if (hash.get() == 0xFFE40008) {
    if (printPass)
      std::cout << "[PASS] Get and finish hash works\n";
  } else {
    std::cout << "[FAIL] Get and finish hash does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  if (hash.get() == Hash::calculateHash("")) {
    if (printPass)
      std::cout << "[PASS] Calculate hash on empty string works\n";
  } else {
    std::cout << "[FAIL] Calculate hash on empty string does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  hash.add('!');
  if (hash.get() == 0x49DD93B2) {
    if (printPass)
      std::cout << "[PASS] Add '!' works works\n";
  } else {
    std::cout << "[FAIL] Add '!' works does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  if (hash.get() == Hash::calculateHash("!")) {
    if (printPass)
      std::cout << "[PASS] Calculate hash on \"!\" string works\n";
  } else {
    std::cout << "[FAIL] Calculate hash on \"!\" string does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  hash.add("Hello world!");
  if (hash.get() == Hash::calculateHash("!Hello world!")) {
    if (printPass)
      std::cout << "[PASS] Calculate hash on \"!Hello world!\" string works\n";
  } else {
    std::cout << "[FAIL] Calculate hash on \"!Hello world!\" string does not "
                 "work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  if (hash.get() != Hash::calculateHash(" Hello world!")) {
    if (printPass)
      std::cout << "[PASS] \"!Hello world!\" vs \" Hello world!\" (1 bit flip) "
                   "works\n";
  } else {
    std::cout << "[FAIL] \"!Hello world!\" vs \" Hello world!\" (1 bit flip) "
                 "does not "
                 "work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  std::string test = "!Hello world!EXTRASPACES";
  Hash        hash2;
  hash2.add(test.c_str(), (size_t)13);
  if (hash2.get() == hash.get()) {
    if (printPass)
      std::cout << "[PASS] Calculate hash with length works\n";
  } else {
    std::cout << "[FAIL] Calculate hash with length does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  Hash hash3;
  hash3.add(test.c_str(), 'E');
  if (hash3.get() == hash.get()) {
    if (printPass)
      std::cout << "[PASS] Calculate hash with termination character works\n";
  } else {
    std::cout
        << "[FAIL] Calculate hash with termination character does not work\n";
    return ResultCode_t::UNKNOWN_HASH;
  }

  return ResultCode_t::SUCCESS;
}

int main() {
  std::cout << "Testing FruitBowl\n";
  Result result = testResult(true);
  if (!result)
    std::cout << "[FAIL] *** Result class does not pass ***\n";

  // while (true)
  //   result = testResult(false);

  result = testHash(true);
  if (!result)
    std::cout << "[FAIL] *** Hash class does not pass ***\n";

  return 0;
}