#pragma once

#include <cinttypes>

struct Position {
  std::uint8_t byte;
  std::uint8_t bit;

  inline Position() = default;
  inline Position(const Position& pos) = default;
  inline Position(std::uint8_t byte, std::uint8_t bit)
    : byte(byte),
      bit(bit)
  {}
};
