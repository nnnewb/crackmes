#if !defined(_OTP_HPP)
#  define _OTP_HPP

#  include <algorithm>
#  include <iterator>
#  include <memory>
#  include <openssl/evp.h>
#  include <openssl/hmac.h>
#  include <string>
#  include <vector>

class TOTP {
private:
  time_t step;
  std::string secret;

private:
  int32_t truncate(const std::vector<uint8_t> &hash) const {
    if (hash.size() != 20) {
      return -1;
    }

    int32_t p = 0;
    size_t offsetBits = hash[19] & 0xf;
    p = (hash[offsetBits] & 0x7f) << 24 | (hash[offsetBits + 1] & 0xff) << 16 | (hash[offsetBits + 2] & 0xff) << 8 |
        (hash[offsetBits + 3] & 0xff);
    return p;
  }

  std::vector<uint8_t> hmac_sha1(const std::string &counter) const {
    uint8_t output[EVP_MAX_MD_SIZE];
    uint32_t output_len = EVP_MAX_MD_SIZE;
    auto ret = std::vector<uint8_t>();

    HMAC(EVP_sha1(), secret.c_str(), secret.length(), reinterpret_cast<const unsigned char *>(counter.c_str()),
         counter.length(), output, &output_len);

    std::copy_n(std::begin(output), output_len, std::back_inserter(ret));
    return ret;
  }

public:
  TOTP(const std::string &secret, const time_t step) : secret(secret), step(step){};
  TOTP(std::string &&secret, const time_t step) : secret(secret), step(step){};
  TOTP(const TOTP &) = delete;
  TOTP(TOTP &&) = delete;
  ~TOTP() = default;

  int32_t get() const {
    // rfc6238 section 4.2 says:
    //
    // More specifically, T = (Current Unix time - T0) / X, where the
    // default floor function is used in the computation.
    //
    // For example, with T0 = 0 and Time Step X = 30, T = 1 if the current
    // Unix time is 59 seconds, and T = 2 if the current Unix time is
    // 60 seconds.
    //
    auto now = time(nullptr);
    auto T = (now - 0) / step;
    // rfc4226 section 5.2 says:
    //
    // HOTP(K,C) = Truncate(HMAC-SHA-1(K,C))
    //
    // rfc 4226 section 5.3 says:
    //
    // Implementations MUST extract a 6-digit code at a minimum and possibly
    // 7 and 8 - digit code.  Depending on security requirements, Digit = 7 or
    // more SHOULD be considered in order to extract a longer HOTP value.
    //
    return truncate(hmac_sha1(std::to_string(T))) % 1000000;
  }
};

#endif // _OTP_HPP
