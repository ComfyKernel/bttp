#ifndef BTTP_ARGPARSE_HPP
#define BTTP_ARGPARSE_HPP

#include <map>
#include <string>

namespace bt {
  class argumentreader {
  protected:
    std::map<std::string, void*> _data;
    
  public:    
    argumentreader();
    argumentreader(int, char**);

    
  };
};

#endif
