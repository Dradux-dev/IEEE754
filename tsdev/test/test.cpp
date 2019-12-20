#include "test.h"

#include "scenario.h"

namespace tsdev {
  namespace test {
    void Test::execute(Scenario* scenario) {
      if(executed) {
        // Was already executed
        ///@todo Send warning to reporter
        //std::cerr << "Warning: " << "Test \"" << name < "\" was already executed." << std::endl;
        return;
      }

      executed = true;
      if(scenario) {
        scenario->execution();
      }

      ///@todo run dependencies

      if (scenario) {
        scenario->setup();
      }

      try {
        if (function) {
          function();
        }
      }
      catch(...) {
        ///@todo Dump error
        passed = false;
        if(scenario) {
          scenario->cleanup();
        }
        return;
      }

      if (scenario) {
        scenario->cleanup();
      }
      passed = true;
    }
  }
}
