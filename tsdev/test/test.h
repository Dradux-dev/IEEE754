#pragma once

#include <string>
#include <vector>

#include "function.h"

namespace tsdev {
  namespace test {
    class Test {
      friend class Scenario;

      public:
      inline Test(const std::string& name, Function function, const std::string& category = "", const std::vector<Test*>& dependencies = {})
          : name(name),
            function(function),
            category(category),
            executed(false),
            passed(false),
            dependencies(dependencies)
        {}

        virtual void execute(class Scenario* scenario);

      protected:
        std::string name;
        Function function;
        std::string category;
        bool executed;
        bool passed;
        std::vector<Test*> dependencies;
    };
  }
}
