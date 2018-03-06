#ifndef BTTP_GL_SHADER_HPP
#define BTTP_GL_SHADER_HPP

#include "head.hpp"

#include <string>

namespace bt {
  namespace gl {
    class shader : public head {
    protected:
      GLenum _type = GL_NONE;
      
    public:
      shader();
      shader(const std::string& path, GLenum type);

      GLenum getType();
      
      void setType(GLenum);
      
      void create();
      void destroy();

      bool load(const std::string& path, GLenum type);

      void source(const std::string& data);

      bool compile();
    };
  }
}

#endif
