#include <gl/program.hpp>
#include <log.hpp>

bt::gl::program::program() {
  _name = 0;
}

bt::gl::program::program(std::initializer_list<GLuint> shaders) {
  _name = 0;
  create();
  attach_list(shaders);
  link();
}

void bt::gl::program::create() {
  destroy();

  _name = glCreateProgram();
}

void bt::gl::program::destroy() {
  if(!_name) return;

  glDeleteProgram(_name);
}

void bt::gl::program::attach(GLuint shad) {
  if(!_name) {
    bt::debug::callwarn(_BT_M_INFO_, "Cannot attach a shader to an un-initialized program!");
    return;
  }

  glAttachShader(_name, shad);
}

void bt::gl::program::attach_list(std::initializer_list<GLuint> shaders) {
  for(const auto& i : shaders) {
    attach(i);
  }
}

bool bt::gl::program::link() {
  if(!_name) {
    bt::debug::callerror(_BT_M_INFO_, "Cannot link an un-initialized program!");
    return false;
  }

  glLinkProgram(_name);

  GLint stat = 0;
  glGetProgramiv(_name, GL_LINK_STATUS, &stat);

  if(stat) {
    bt::debug::callinfo(_BT_M_INFO_, "Successfully linked a shader program");

    return true;
  }

  glGetProgramiv(_name, GL_INFO_LOG_LENGTH, &stat);

  char* msg = (char*)operator new(stat);

  glGetProgramInfoLog(_name, stat, nullptr, msg);

  bt::debug::callerror(_BT_M_INFO_, std::string("Failed linking program : ") + msg);

  delete msg;

  return false;
}

void bt::gl::program::use() {
  if(!_name) {
    bt::debug::callwarn(_BT_M_INFO_, "Cannot use an un-initialized program!");
    return;
  }

  glUseProgram(_name);
}
