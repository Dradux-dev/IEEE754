#pragma once

#include <array>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <vector>

#include "adder.h"
#include "direction.h"
#include "binary.h"
#include "position.h"
#include "range.h"


template <int TLen>
struct BitVector {
  inline BitVector() {
    clear();
  }

  inline BitVector(const BitVector& bv) = default;

  void clear() {
    std::memset(data.data(), 0, data.size());
  }

  inline std::uint8_t& operator[](int index) {
    return data[index];
  }

  inline const std::uint8_t& operator[](int index) const {
    return data[index];
  }

  inline std::vector<std::uint8_t> shiftLeft(std::size_t n) {
    std::vector<std::uint8_t> in(n);
    std::memset(in.data(), 0, in.size());
    return shiftLeft(n, in);
  }

  inline std::vector<std::uint8_t> shiftLeft(std::size_t n, const std::vector<std::uint8_t>& in) {
    std::vector<std::uint8_t> out(n);

    // Indices: 0 1 2 3 4 5 6 7 8 ... 123
    for (std::size_t i = 0; i < TLen; ++i) {
      if (i < n) {
        out[i] = data[i];
      }

      if (i < (TLen - n)){
        data[i] = data[i+n];
      }
      else {
        data[i] = in[i - (TLen - n)];
      }
    }

    return out;
  }

  inline std::vector<std::uint8_t> shiftRight(std::size_t n) {
    std::vector<std::uint8_t> in(n);
    std::memset(in.data(), 0, in.size());
    return shiftRight(n, in);
  }

  inline std::vector<std::uint8_t> shiftRight(std::size_t n, const std::vector<std::uint8_t>& in) {
    std::vector<std::uint8_t> out(n);

    // Indices: 0 1 2 3 4 5 6 7 8 ... 123
    for (std::size_t i = TLen; i > 0; --i) {
      if (TLen - i < n) {
        out[n - (TLen - i) - 1] = data[i-1];
      }

      if (i > n) {
        data[i-1] = data[i-1-n];
      }
      else {
        data[i-1] = in[i-1];
      }
    }

    return out;
  }

  template<int U>
  BitVector<U> extendLeft(std::uint8_t fill = 0) {
    BitVector<U> bv;

    if (U <= TLen) {
      std::size_t x = TLen - U;
      for (std::size_t n = 0; n < U; ++n) {
        bv[n] = data[n+x];
      }
    }
    else {
      std::size_t x = U - TLen;
      for (std::size_t n = 0; n < U; ++n) {
        if (n < x) {
          bv[n] = fill;
        }
        else {
          bv[n] = data[n - x];
        }
      }
    }

    return bv;
  }

  template<int U>
  BitVector<U> extendRight(std::uint8_t fill = 0) {
    BitVector<U> bv;

    if (U <= TLen) {
      for (std::size_t n = 0; n < U; ++n) {
        bv[n] = data[n];
      }
    }
    else {
      for (std::size_t n = 0; n < U; ++n) {
        if (n < TLen) {
          bv[n] = data[n];
        }
        else {
          bv[n] = fill;
        }
      }
    }

    return bv;
  }

  BitVector<TLen> invert() {
    return invert(Range<std::size_t>(0, TLen));
  }

  BitVector<TLen> invert(std::size_t start) {
    return invert(Range<std::size_t>(start, TLen));
  }

  BitVector<TLen> invert(const Range<std::size_t>& range) {
    BitVector<TLen> bv = *this;

    for (std::size_t n : range) {
      if (Binary::IS_HIGH(bv[n])) {
        bv[n] = Binary::LOW();
      }
      else {
        bv[n] = Binary::HIGH();
      }
    }

    return bv;
  }

  BitVector<TLen> twoComplement() {
    return invert() + BitVector<TLen>::One();
  }

  /// @todo Plus
  BitVector<TLen> operator+(const BitVector<TLen>& bv) {
    BitVector<TLen> res;
    Adder::Result tmp;

    for (std::size_t n = TLen; n > 0; --n) {
      tmp = Adder::Full(data[n-1], bv[n-1], tmp.carry);
    }

    overflow = tmp.carry;
    return res;
  }

  /// @todo Minus
  BitVector<TLen> operator-(const BitVector<TLen>& bv) {
    BitVector<TLen> c2 = bv.twoComplement();
    BitVector<TLen> res;
    Adder::Result tmp;

    for (std::size_t n = TLen; n > 0; --n) {
      tmp = Adder::Full(data[n-1], c2[n-1], tmp.carry);
    }

    overflow = tmp.carry;
    return res;
  }

  inline std::uint8_t getOverflow() const {
    return overflow;
  }

  inline float asDecimal(std::int32_t firstExponent, std::size_t startBit = 0) const {
    float value = 0.0f;
    std::int32_t exponent = firstExponent;
    for (std::size_t i = startBit; i < TLen; ++i) {
      value += data[i] * std::pow(2.0f, static_cast<float>(exponent));
       exponent -= 1;
    }

    return value;
  }

  static BitVector<TLen> FromDecimal(float value, std::int32_t firstExponent, std::size_t startBit = 0) {
    BitVector<TLen> bv;
    std::int32_t exponent = firstExponent;

    for (std::size_t n = startBit; n < TLen; ++n) {
      float positionValue = std::pow(2.0f, static_cast<float>(exponent));

      if (positionValue <= value) {
        bv[n] = Binary::HIGH();
        value -= positionValue;
      }
      else {
        bv[n] = Binary::LOW();
      }

      exponent -= 1;
    }

    return bv;
  }

  static BitVector<TLen> Zero() {
    return FromDecimal(0.0f, TLen - 1);
  }

  static BitVector<TLen> One() {
    return FromDecimal(1.0f, TLen - 1);
  }

protected:
  std::array<std::uint8_t, TLen> data;
  std::uint8_t overflow;
};

template <int TLen>
std::ostream& operator<<(std::ostream& os, const BitVector<TLen>& bv) {
  for(std::size_t n = 0; n < TLen; ++n) {
    std::uint8_t bit = bv[n];
    if (Binary::IS_HIGH(bit)) {
      os << "1";
    }
    else if (Binary::IS_LOW(bit)) {
      os << "0";
    }
  }

  return os;
}
