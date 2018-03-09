#ifndef BTTP_FORMATREADER_HPP
#define BTTP_FORMATREADER_HPP

#include <functional>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

namespace bt {
  class formatreader;
}

typedef std::function<void(bt::formatreader&, const std::string&)> __bt_format_function;

typedef std::pair<std::string, __bt_format_function> __bt_format_pair;

namespace bt {  
  class formatreader {
  protected:
    std::vector<__bt_format_pair>                    _rules;
    std::vector<std::pair<std::string, bool>>        _flags;
    std::vector<std::pair<std::string, std::string>> _info;
    std::vector<std::pair<std::string, void*>>       _data;
    std::vector<std::string> _segments;
    unsigned int             _sptr = 0;

    std::fstream _fi;
    
  public:
    formatreader();
    formatreader(const std::string&);

    bool is_open();
    bool open(const std::string&);

    void newRule(const std::string&, __bt_format_function);

    std::string splitInfo="";
    const std::string& nextString();
    bool read();

    void setFlag(const std::string&, bool);
    bool getFlag(const std::string&);

    void pushInfo(const std::string&, const std::string&);
    const std::string& getInfo(const std::string&);

    void pushData(const std::string&, void*);
    template<typename T>
    T* getData(const std::string& name) {
      for(const auto& i : _data) {
	if(i.first == name) {
	  return (T*)i.second;
	}
      }

      return nullptr;
    }

    void close();
  };
}

#endif
