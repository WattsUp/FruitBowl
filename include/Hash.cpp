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
  value = calculateHash(value, c);
}

/**
 * @brief Add a character array until the termination character
 *
 * @param c array to add
 * @param end character will stop and not hash this character
 */
void Hash::add(const char * c, const char end) {
  while (*c != end) {
    add(*c);
    ++c;
  }
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
