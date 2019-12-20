#pragma once

#include "exception.h"

namespace tsdev {
  namespace test {
    class Reporter
    {
      public:
        Reporter() = default;

        virtual error(const Exception& exception) = 0;
        virtual warning(const Exception& exception) = 0;
        virtual result(std::size_t testsPassed, std::size_t assertsPassed) = 0;
    };
  }
}
