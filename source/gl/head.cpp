#include <gl/head.hpp>

GLuint bt::gl::head::name() {
  return _name;
}

bt::gl::head::operator GLuint() {
  return _name;
}
