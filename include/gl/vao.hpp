#ifndef BTTP_GL_VAO_HPP
#define BTTP_GL_VAO_HPP

#include "head.hpp"

namespace bt {
  namespace gl {
    class vao : public head {
    public:
      vao();
      
      void create ();
      void destroy();

      void bind();
    };
  }
}

#endif
