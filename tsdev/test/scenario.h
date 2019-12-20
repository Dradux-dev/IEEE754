#pragma once

#include <map>
#include <string>
#include <vector>

#include "function.h"
#include "test.h"

#ifndef TSTEST_ASSERT_TRUE
#define TSTEST_ASSERT_TRUE(x) this->assertTrue((x), #x, __FILE__, __LINE__);
#endif

#ifndef TSTEST_ASSERT_FALSE
#define TSTEST_ASSERT_FALSE(x) this->assertFalse((x), #x, __FILE__, __LINE__);
#endif

namespace tsdev {
  namespace test {
    class Scenario
    {
      friend class Test;

      public:
        inline Scenario(Scenario* parent = nullptr)
          : parent(parent)
        {
          if (parent) {
            parent->addChild(this);
          }
        }

        virtual bool run(const std::vector<std::string>&) { return false; }
        virtual void setup() {}
        virtual void cleanup() {}

      protected:
        inline void assertion() { ++asserts; }
        inline void execution() { ++executed; }
        void assertTrue(bool b, const std::string& sb, const std::string& file, int line);
        void assertFalse(bool b, const std::string& sb, const std::string& file, int line);

        inline void addTest(const std::string& testName, Function function, std::vector<Test*> dependencies = {}) {
          addTest (testName, "", function, dependencies);
        }

        void addTest(const std::string& testName, const std::string& category, Function function, std::vector<Test*> dependencies = {});


        std::pair<std::string, std::string> make_pair(const std::string& first, const std::string& second);
        std::string asString(bool b);

        inline void addChild(Scenario* child) {
          children.push_back(child);
        }

      protected:
        Scenario* parent;
        std::vector<Scenario*> children;

        std::size_t executed;
        std::size_t asserts;

        std::vector<Test> tests;
        Test* current;

        std::vector<Scenario*> subScenarios;
    };
  }
}
