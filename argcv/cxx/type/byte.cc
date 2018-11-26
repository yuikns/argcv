/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Yu Jing
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
#include "argcv/cxx/type/byte.h"

#include <cstdint>
#include <string>
#include <vector>

namespace argcv {

inline bool byte2hex(Byte *c, char in) noexcept {
  // how about use a map instead?
  if ('0' <= in && in <= '9') {
    *c = in - '0';
    return true;
  }

  if ('a' <= in && in <= 'z') {
    *c = in - 'a' + 10;
    return true;
  }

  if ('A' <= in && in <= 'Z') {
    *c = in - 'A' + 10;
    return true;
  }

  return false;
}

// bool DecodeHexString(std::string *out, const std::string &in) noexcept {
bool Bytes::FromHexString(const std::string &in) noexcept {
  size_t n = in.size();
  if (n % 2 == 1) {
    // invalid length
    return false;
  }
  n >>= 1;
  Byte *cdata = new Byte[n];
  for (size_t i = 0; i < n; i++) {
    // little-endian
    Byte hi, lo;
    if (byte2hex(&hi, in[2 * i]) && byte2hex(&lo, in[2 * i + 1])) {
      cdata[i] = static_cast<Byte>(((hi << 4) & 0xf0) | (lo & 0x0f));
    }
  }

  // update members
  clear();
  data_ = cdata;
  size_ = n;
  return true;
}

}  // namespace argcv
