#include <gl/shader.hpp>

#include <fstream>
#include <log.hpp>

bt::gl::shader::shader() {
  _name = 0;
}

bt::gl::shader::shader(const std::string& path, GLenum type) {
  _name = 0;
  load(path, type);
}

GLenum bt::gl::shader::getType() {
  return _type;
}

void bt::gl::shader::setType(GLenum type) {
  _type = type;
}

void bt::gl::shader::create() {
  if(_type == GL_NONE) {
    bt::debug::callwarn(_BT_M_INFO_, "Cannot initialize a shader without a type!");

    return;
  }

  destroy();
  _name = glCreateShader(_type);
}

void bt::gl::shader::destroy() {
  if(!_name) return;

  _type = GL_NONE;
  glDeleteShader(_name);
  _name = 0;
}

bool bt::gl::shader::load(const std::string& path, GLenum type) {
  std::ifstream fi(path, std::ios::in);

  _type = type;

  create();
  
  if(!fi.is_open()) {
    bt::debug::callerror(_BT_M_INFO_, std::string("Failed to open file : " + path + "! Cannot initialize shader."));

    return false;
  }

  std::string data("");

  char c;
  while(fi.get(c)) {
    data += c;
  }

  source(data);

  compile();

  return true;
}

void bt::gl::shader::source(const std::string& data) {
  if(!_name) {
    bt::debug::callwarn(_BT_M_INFO_, "Cannot source a non-initialized shader!");
    return;
  }

  const char* dat = data.c_str();
  GLint len = data.size();

  glShaderSource(_name, 1, &dat, &len);
}

bool bt::gl::shader::compile() {
  if(!_name) {
    bt::debug::callerror(_BT_M_INFO_, "Cannot compile a non-initialized shader!");
    return false;
  }

  glCompileShader(_name);

  GLint stat=0;
  glGetShaderiv(_name, GL_COMPILE_STATUS, &stat);

  if(stat) {
    bt::debug::callinfo(_BT_M_INFO_, "Successfully compiled a shader");
    return true;
  }

  glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &stat);

  char* msg = (char*)operator new(stat);

  glGetShaderInfoLog(_name, stat, nullptr, msg);

  bt::debug::callerror(_BT_M_INFO_, std::string("Failed compiling shader! : ") + msg);
  
  delete msg;

  return false;
}
