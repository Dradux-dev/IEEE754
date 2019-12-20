#pragma once

#include <map>
#include <string>

namespace tsdev {
  namespace test {
    class Exception : public std::runtime_error {
      public:
        std::string testName;
        std::string fileName;
        std::size_t lineNumber;
        std::string comparison;
        std::pair<std::string, std::string> strInfo;
        std::pair<std::string, std::string> valueInfo;

        Exception(const std::string& testName, const std::string& fileName, std::size_t lineNumber, const std::string& comparison, std::pair<std::string, std::string> strInfo, std::pair<std::string, std::string> valueInfo)
          : std::runtime_error(""),
            testName(testName),
            fileName(fileName),
            lineNumber(lineNumber),
            comparison(comparison),
            strInfo(strInfo),
            valueInfo(valueInfo)
        {}
    };
  }
}
