#ifndef BTTP_GL_HEAD_HPP
#define BTTP_GL_HEAD_HPP

#include <GL/glew.h>

namespace bt {
  namespace gl {
    class head {
    protected:
      GLuint _name;
      
    public:
      GLuint name();

      virtual void create () = 0;
      virtual void destroy() = 0;
      
      operator GLuint();
    };
  }
}

#endif
