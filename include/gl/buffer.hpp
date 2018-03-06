#ifndef BTTP_GL_BUFFER_HPP
#define BTTP_GL_BUFFER_HPP

#include "head.hpp"
#include "../types.hpp"

#include <initializer_list>
#include <iostream>

namespace bt {
  namespace gl {
    template<typename T>
    class buffer : public head {
    protected:
      GLenum _type;
      GLenum _usage;
      
    public:
      GLenum type () {
	return _type;
      }
      
      GLenum usage() {
	return _usage;
      }

      buffer() {
	_name = 0;
      }
      
      buffer(T* data, uint length, GLenum tp, GLenum use) {
	_name = 0;

	generate(data, length, tp, use);
      }
      
      buffer(std::initializer_list<T> _idata, GLenum tp, GLenum use) {
	_name = 0;
	
	generate(_idata.begin(), _idata.size(), tp, use);
      }

      void create () {
	destroy();

	glGenBuffers(1, &_name);
      }
      
      void generate(const T* data, uint length, GLenum tp, GLenum use) {
	create();

	_type  = tp;
	_usage = use;

	glBindBuffer(tp, _name);
	
	glBufferData(tp, length * sizeof(T), data, use);
      }
      
      void destroy() {
	if(!_name) return;

	glDeleteBuffers(1, &_name);
      }
    };
  }
}

#endif
