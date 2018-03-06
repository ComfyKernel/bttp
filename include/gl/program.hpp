#ifndef BTTP_GL_PROGRAM_HPP
#define BTTP_GL_PROGRAM_HPP

#include "head.hpp"

#include <initializer_list>

namespace bt {
  namespace gl {
    class program : public head {
    protected:

    public:
      program();
      program(std::initializer_list<GLuint>);

      void create();
      void destroy();

      void attach(GLuint);
      void attach_list(std::initializer_list<GLuint>);
      bool link();

      void use();
    };
  }
}

#endif
