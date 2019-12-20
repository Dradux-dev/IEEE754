#pragma once

#include "../fixedpoint.h"
#include "../tsdev/test/scenario.h"

namespace IEEE754 {
  namespace test {
    class TFixedPoint : public tsdev::test::Scenario
    {
      public:
        using FixedPoint = FixedPoint<4,4>;

        TFixedPoint(Scenario* parent);

        void convertToFloat();
    };
  }
}
