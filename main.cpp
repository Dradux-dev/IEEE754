#include <iostream>

#include "fixedpoint.h"


int main()
{
  std::vector<std::uint8_t> out;
  BitVector<7> bv;
  bv[0] = 1;
  bv[1] = 1;
  bv[3] = 1;
  bv[5] = 1;
  bv[6] = 1;

  std::cout << "bv = {" << bv << "}" << std::endl;

  // Shift Left 3
  std::cout << "bv << 3" << std::endl;
  out = bv.shiftLeft(3);
  std::cout << "bv = {" << bv << "}" << std::endl;
  std::cout << "out = {";
  for (std::uint8_t x : out) {
    std::cout << static_cast<int>(x);
  }
  std::cout << "}" << std::endl;
  std::cout << "value = " << bv.asDecimal(-1) << std::endl;

  // Shift Right 3
  std::cout << "bv >> 3" << std::endl;
  out = bv.shiftRight(3);
  std::cout << "bv = {" << bv << "}" << std::endl;
  std::cout << "out = {";
  for (std::uint8_t x : out) {
    std::cout << static_cast<int>(x);
  }
  std::cout << "}" << std::endl;

  std::cout << "Value = " << bv.asDecimal(6) << std::endl;

  BitVector<4> bv2 = bv.extendLeft<4>();
  std::cout << "bv2 = " << bv2 << std::endl;

  BitVector<16> bv3 = bv.extendLeft<16>();
  std::cout << "bv3 = " << bv3 << std::endl;

  BitVector<3> bv4 = bv.extendRight<3>();
  std::cout << "bv4 = " << bv4 << std::endl;

  BitVector<8> bv5 = bv.extendRight<8>();
  std::cout << "bv5 = " << bv5 << std::endl;

  BitVector<7> bv6 = bv.invert();
  std::cout << "bv6 = " << bv6 << std::endl;

  BitVector<4> bv7 = BitVector<4>::FromDecimal(5, 3);
  std::cout << "bv7 = " << bv7 << std::endl;

  FixedPoint<4,4> fp(3.5f);
  std::cout << "fp = " << fp << std::endl;
  std::cout << "fp::value = " << static_cast<float>(fp) << std::endl;

  FixedPoint<4,4> fp2(2.5f);
  std::cout << "fp2 = " << fp2 << std::endl;
  std::cout << "fp2::value = " << static_cast<float>(fp2) << std::endl;

  FixedPoint<4,4> fp3 = fp + fp2;
  std::cout << "fp3 = " << fp3 << std::endl;
  std::cout << "fp3::value = " << static_cast<float>(fp3) << std::endl;

  FixedPoint<4,4>::Shifted sfp = fp.shift(1);
  std::cout << "sfp = {" << sfp.fp << ", " << sfp.exponent << "}" << std::endl;
  std::cout << "sfp::value = " << static_cast<float>(sfp.fp) << std::endl;

  FixedPoint<4,4>::Shifted sfp2 = fp.shift(-1);
  std::cout << "sfp2 = {" << sfp2.fp << ", " << sfp2.exponent << "}" << std::endl;
  std::cout << "sfp2::value = " << static_cast<float>(sfp2.fp) << std::endl;

  /*using FixedPoint = FixedPoint<24,23>;
  bool quit = false;

  while(!quit) {
    std::uint8_t choice;
    std::cout << "Floating Pointer Calculator" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Decimal         ->  Floating Point" << std::endl;
    std::cout << "2. Floating Point  ->  Decimal" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Please choose: ";
    std::cin >> choice;

    if (choice == 1) {
      float f;
      std::cout << "Enter the decimal number: ";
      std::cin >> f;
      std::cout << std::endl;

      FixedPoint fixp(f, true);
      std::cout << "f = " << f << std::endl
                << "  = " << fixp << std::endl << std::endl;

      fixp.normalize();
    }
    else if (choice == 2) {
      std::cout << "Not implemented yet - sorry" << std::endl;
    }
    else if (choice == 3) {
      quit = true;
    }

    std::cout << std::endl;
  }*/

  return 0;
}
