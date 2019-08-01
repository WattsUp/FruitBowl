#include "Hash.h"
#include <iomanip>
#include <sstream>

/**
 * @brief Construct a new Hash:: Hash object
 *
 * Initializes the hash to all ones
 */
Hash::Hash() : value(0xFFFFFFFF) {}

/**
 * @brief Add a character to the hash
 *
 * @param c to add
 */
void Hash::add(const char c) {
  string.push_back(c);
  value = calculateHash(value, c);
}

/**
 * @brief Add a character array until the termination character or length number
 * of characters
 *
 * @param c array to add
 * @param end character will stop and not hash this character
 */
size_t Hash::add(const char * c, size_t length, const char end) {
  size_t count = 0;
  while (*c != end && length > 0) {
    add(*c);
    --length;
    ++c;
    ++count;
  }
  return count;
}

/**
 * @brief Add a character array until the termination character or length number
 * of characters
 *
 * @param c array to add
 * @param end character will stop and not hash this character
 */
size_t Hash::add(const unsigned char * c, size_t length, const char end) {
  size_t count = 0;
  while (*c != end && length > 0) {
    add(*c);
    --length;
    ++c;
    ++count;
  }
  return count;
}

/**
 * @brief Add a character array, length characters long
 *
 * @param c array to add
 * @param length number of characters
 */
void Hash::add(const char * c, size_t length) {
  while (length > 0) {
    add(*c);
    --length;
    ++c;
  }
}

/**
 * @brief Get the current hash value
 *
 * @return const HashValue_t hash
 */
const HashValue_t Hash::get() const {
  return finishHash(value);
}

/**
 * @brief Get the string of the hash
 *
 * @return const std::string &
 */
const std::string & Hash::getString() const {
  return string;
}

/**
 * @brief Get the completion status of hashing
 *
 * @return true if hashing is complete
 * @return false if hashing is not complete
 */
const bool Hash::isDone() const {
  return hashingDone;
}

/**
 * @brief Set the completion status of hashing
 *
 * @param done if true will indicate hashing is complete
 */
void Hash::setDone(const bool done) {
  hashingDone = done;
}