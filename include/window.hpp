#ifndef BTTP_WINDOW_HPP
#define BTTP_WINDOW_HPP

#include <string>

#include "type2d.hpp"

namespace bt {
  using version = uint32_2d;
  
  class window {
  private:
    class _window_impl_;
    _window_impl_* _impl;
    
  public:
    window();
    window(const size&, const std::string&, const version&);

    bool open(const size&, const std::string&, const version&);
    void close();

    void swap();
    
    ~window();
  };
}

#endif
