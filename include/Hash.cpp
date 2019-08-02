#include "Hash.h"
#include <iomanip>
#include <sstream>

/**
 * @brief Construct a new Hash:: Hash object
 * Create a new referenceCount equal to 1
 *
 * @param value to initialize the hash to
 */
Hash::Hash(HashValue_t value) :
  value(value), referenceCount(new int16_t), string(new std::string) {
  *referenceCount = 1;
}

/**
 * @brief Copy constructor
 * Copy the values and increment referenceCount
 *
 * @param result to copy
 */
Hash::Hash(const Hash & hash) :
  value(hash.value), string(hash.string), referenceCount(hash.referenceCount) {
  ++(*referenceCount);
}

/**
 * @brief Assignment operator
 * Decrement the left hand side and delete if zero references
 * Set the left hand side to the right and increment its counter
 *
 * @param hash to assign
 * @return Hash&
 */
Hash & Hash::operator=(const Hash & hash) {
  if (this != &hash) {
    if (referenceCount != nullptr && (--(*referenceCount)) <= 0) {
      delete referenceCount;
      delete string;
    }
    value          = hash.value;
    string         = hash.string;
    referenceCount = hash.referenceCount;
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
Hash::~Hash() {
  if (referenceCount != nullptr) {
    (*referenceCount)--;
    if (*referenceCount <= 0) {
      delete referenceCount;
      delete string;
      referenceCount = nullptr;
      string         = nullptr;
    }
  }
}

/**
 * @brief Add a character to the hash
 *
 * @param c to add
 */
void Hash::add(const char c) {
  string->push_back(c);
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
  return *string;
}

/**
 * @brief Get reference count, number of references to string
 *
 * @return int16_t
 */
const int16_t * Hash::getReferenceCount() const {
  return referenceCount;
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