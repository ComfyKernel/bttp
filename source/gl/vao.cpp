#include <gl/vao.hpp>
#include <log.hpp>

bt::gl::vao::vao() {
  _name = 0;
}

void bt::gl::vao::create() {
  destroy();

  glGenVertexArrays(1, &_name);
}

void bt::gl::vao::destroy() {
  if(!_name) return;

  glDeleteVertexArrays(1, &_name);
}

void bt::gl::vao::bind() {
  if(!_name) {
    bt::debug::callwarn(_BT_M_INFO_, "Cannot bind an un-initialized Vertex Array Object!");
    return;
  }

  glBindVertexArray(_name);
}
