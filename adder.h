#pragma once

#include "binary.h"

struct Adder {
  struct Result {
    std::uint8_t sum;
    std::uint8_t carry;

    explicit inline Result()
      : sum(Binary::LOW()),
        carry(Binary::LOW())
    {}

    explicit inline Result(std::uint8_t sum, std::uint8_t carry)
      : sum(sum),
        carry(carry)
    {}
  };

  static Result Half(std::uint8_t a, std::uint8_t b) {
    return Result(
          Binary::XOR(a, b),
          Binary::AND(a, b)
    );
  }

  static Result Full(std::uint8_t a, std::uint8_t b, std::uint8_t carry) {
    Result ha1 = Half(a, b);
    Result ha2 = Half(ha1.sum, carry);

    return Result(
          ha2.sum,
          Binary::OR(ha1.carry, ha2.carry)
    );
  }
};
