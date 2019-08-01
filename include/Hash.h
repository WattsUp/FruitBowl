#ifndef _FB_HASH_H_
#define _FB_HASH_H_

#include <stdint.h>
#include <string>

typedef uint32_t HashValue_t;

class Hash {
public:
  Hash();

  void add(const char c);
  void add(const char * c, const char end = '\0');
  void add(const char * c, size_t length);

  /**
   * @brief Add a string to the hash
   *
   * @param string to hash
   */
  inline void add(const std::string & string) {
    add(string.c_str());
  }

  const HashValue_t get() const;

  /**
   * @brief Calculate the hash from a string
   *
   * @param string to hash
   * @return HashValue_t hash
   */
  static HashValue_t calculateHash(const std::string & string) {
    HashValue_t hash = 0xFFFFFFFF;
    for (char c : string) {
      hash = calculateHash(hash, c);
    }
    return finishHash(hash);
  }

  /**
   * @brief Calculate the hash from a string
   *
   * @param string to hash
   * @return constexpr HashValue_t hash
   */
  static constexpr HashValue_t calculateHash(char * string) {
    HashValue_t hash = 0xFFFFFFFF;
    while (*string != '\0') {
      hash = calculateHash(hash, *string);
      ++string;
    }
    return finishHash(hash);
  }

private:
  /**
   * @brief Calculate the hash through its algorithm on the seed hash and char
   * Jenkin's hash function
   *
   * @param hash to seed
   * @param c char to append
   * @return constexpr HashValue_t hash
   */
  static constexpr HashValue_t calculateHash(HashValue_t hash, const char c) {
    hash = static_cast<HashValue_t>(hash + static_cast<uint64_t>(c));
    hash = static_cast<HashValue_t>(hash + (static_cast<uint64_t>(hash) << 10));
    hash = static_cast<HashValue_t>(hash ^ (static_cast<uint64_t>(hash) >> 6));
    return hash;
  }

  /**
   * @brief Applies final operations to finish creating a hash
   *
   * @param hash to process
   * @return constexpr HashValue_t final hash
   */
  static constexpr HashValue_t finishHash(HashValue_t hash) {
    hash = static_cast<HashValue_t>(hash + (static_cast<uint64_t>(hash) << 3));
    hash = static_cast<HashValue_t>(hash ^ (static_cast<uint64_t>(hash) >> 11));
    hash = static_cast<HashValue_t>(hash + (static_cast<uint64_t>(hash) << 15));
    return hash;
  }

  HashValue_t value;
};

#endif /* _FB_HASH_H_ */