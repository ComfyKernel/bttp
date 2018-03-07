#ifndef BTTP_FORMATREADER_HPP
#define BTTP_FORMATREADER_HPP

#include <functional>

namespace bt {
  class formatreader;
  
  struct formatrule {
  public:
    std::string trigger;

    std::function<void(formatreader&)>;
  }
  
  class formatreader {
  protected:
    
  public:
    std::vector<formatrule>  rules;
    std::vector<std::string> sorted;
    
    formatreader();

    
  };
}

#endif
