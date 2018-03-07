#ifndef BTTP_ENGINE_MAIN_HPP
#define BTTP_ENGINE_MAIN_HPP

#include <vector>

#include "log.hpp"
#include "types.hpp"
#include "type2d.hpp"
#include "type3d.hpp"
#include "argparse.hpp"
#include "window.hpp"

#include "gl/head.hpp"
#include "gl/buffer.hpp"
#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "gl/vao.hpp"

namespace bt {
  bool init();
  
  class parameter {
  public:
    static const std::string&              get(const std::string&);
    static const std::vector<std::string>& all();
  };
}

#endif
