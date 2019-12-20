#pragma once

#include <array>
#include <cinttypes>
#include <ostream>

struct Binary {
  static std::uint8_t HIGH() {
    return 1;
  }

  static std::uint8_t LOW() {
    return 0;
  }

  static bool IS_HIGH(std::uint8_t value) {
    return (value == 1);
  }

  static bool IS_LOW(std::uint8_t value) {
    return (value == 0);
  }

  static std::uint8_t NOT(std::uint8_t a) {
    return (a == 1) ? 0 : 1;
  }

  static std::uint8_t AND(std::uint8_t a, std::uint8_t b) {
    return (a == 1 && b == 1) ? 1 : 0;
  }

  static std::uint8_t OR(std::uint8_t a, std::uint8_t b) {
    return (a == 1 || b == 1) ? 1 : 0;
  }

  static std::uint8_t XOR(std::uint8_t a, std::uint8_t b) {
    return (OR(AND(a, NOT(b)), AND(NOT(a), b)) == 1) ? 1 : 0;
  }
};
