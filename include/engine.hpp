#ifndef BTTP_ENGINE_MAIN_HPP
#define BTTP_ENGINE_MAIN_HPP

#include <string>
#include <vector>

#include "types.hpp"
#include "argparse.hpp"

namespace bttp {
  class parameter {
  public:
    static const std::string&              get(const std::string&);
    static const std::vector<std::string>& all();
  };
}

#endif
