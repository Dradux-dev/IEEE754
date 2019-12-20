#pragma once

#include <iostream>
#include <cstring>
#include <array>
#include <cmath>

#include "adder.h"
#include "bitvector.h"

template <int TPreDecimal, int TDecimal>
struct ShortFixedPoint;

template <int TPreDecimal, int TDecimal>
class FixedPoint {
public:
  struct Shifted {
    FixedPoint fp;
    std::int32_t exponent;

    inline Shifted(FixedPoint&& fp, std::int32_t exponent)
      : fp(fp),
        exponent(exponent)
    {}
  };

  inline FixedPoint()
    : predecimal(BitVector<TPreDecimal>::Zero()),
      decimal(BitVector<TDecimal>::Zero())
  {}

  inline FixedPoint(float f)
    : predecimal(BitVector<TPreDecimal>::FromDecimal(f, TPreDecimal-2, 1)),
      decimal(BitVector<TDecimal>::FromDecimal(f - static_cast<int>(f), -1))
  {}

  std::int32_t distanceToNormalized() const {
    for(std::int32_t pos = TPreDecimal-1; pos >= -TDecimal; --pos) {
      std::uint8_t value = (pos >= 0) ? predecimal[pos] : decimal[-(pos+1)];
      if (Binary::IS_HIGH(value)) {
        return pos;
      }
    }

    return TPreDecimal;
  }

  FixedPoint<TPreDecimal, TDecimal>::Shifted normalize() const {
    std::int32_t distance = distanceToNormalized();

    // Every other case has to be wrong and will be ignored
    if (distance > 0 && distance < TPreDecimal) {
      // Move decimal point left
      return shift(distance);
    }
    else if (distance < 0 && distance >= -TDecimal) {
      // Move decimal point right
      return shift(distance);
    }

    return Shifted(
          std::move(FixedPoint<TPreDecimal, TDecimal>(*this)),
          0
    );
  }

  FixedPoint<TPreDecimal, TDecimal>::Shifted shift(std::int32_t distance) const {
    if (distance == 0) {
      // Do not move, if distance is 0. This is already normalized
      return Shifted(
            std::move(FixedPoint<TPreDecimal, TDecimal>(*this)),
            0
      );
    }

    FixedPoint<TPreDecimal, TDecimal> result(*this);
    if(distance > 0) {
      // Move right
      std::vector<std::uint8_t> carry = result.predecimal.shiftRight(distance);
      result.decimal.shiftRight(distance, carry);
    }
    else if (distance < 0) {
      std::vector<std::uint8_t> carry = result.decimal.shiftLeft(-distance);
      result.predecimal.shiftLeft(-distance, carry);
    }

    return Shifted(
          std::move(result),
          distance
    );
  }

  operator float() const {
    return predecimal.asDecimal(TPreDecimal-2, 1) + decimal.asDecimal(-1);
  }

  FixedPoint<TPreDecimal, TDecimal> operator+(const FixedPoint<TPreDecimal, TDecimal>& f) {
    FixedPoint<TPreDecimal, TDecimal> res;

    res.decimal = decimal + f.decimal;
    res.predecimal = (res.decimal.getOverflow() ? BitVector<TPreDecimal>::One() : BitVector<TPreDecimal>::Zero()) + predecimal + f.predecimal;

    return res;
  }

  template <int x, int y>
  friend std::ostream& operator<<(std::ostream&, const FixedPoint<x,y>&);

protected:
  BitVector<TPreDecimal> predecimal;
  BitVector<TDecimal> decimal;
  std::uint8_t overflow;
};

template <int TPreDecimal, int TDecimal>
std::ostream& operator<<(std::ostream& os, const FixedPoint<TPreDecimal, TDecimal>& fp) {
  return os << fp.predecimal << "." << fp.decimal;
}
