#ifndef BTTP_ARGPARSE_HPP
#define BTTP_ARGPARSE_HPP

#include <map>
#include <string>
#include <functional>

namespace bt {
  class argumentreader {
  protected:
    std::map<std::string, void*> _data;
    
  public:    
    argumentreader();
    argumentreader(int, char**);

    bool addCommand(const std::string& name, const std::string& description, std::function<void (int, const char*)> callback);
  };
};

#endif
