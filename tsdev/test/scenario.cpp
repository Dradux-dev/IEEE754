#include "scenario.h"

#include "exception.h"

namespace tsdev {
  namespace test {
    void Scenario::addTest(const std::string &testName, const std::string &category, Function function, std::vector<Test*> dependencies) {
      tests.push_back(std::move(Test(testName, function, category, dependencies)));
    }

    void Scenario::assertTrue(bool b, const std::string& sb, const std::string& file, int line) {
      assertion();

      if (!b) {
        throw Exception(
              current ? current->name : "",
              file,
              line,
              "==",
              make_pair(sb, "true"),
              make_pair(asString(b), "true")
        );
      }    }

    void Scenario::assertFalse(bool b, const std::string& sb, const std::string& file, int line) {
      assertion();

      if (b) {
        throw Exception(
              current ? current->name : "",
              file,
              line,
              "==",
              make_pair(sb, "false"),
              make_pair(asString(b), "false")
        );
      }
    }

    std::pair<std::string, std::string> Scenario::make_pair(const std::string& first, const std::string& second) {
      return std::pair<std::string, std::string>(first, second);
    }

    std::string Scenario::asString(bool b) {
      return b ? "true" : "false";
    }
  }
}
