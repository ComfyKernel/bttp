#ifndef BTTP_ENGINE_MAIN_HPP
#define BTTP_ENGINE_MAIN_HPP

#define _BT_M_INFO_ std::string("[") + __FILE__ + "] " + __func__ + " : line " + std::to_string(__LINE__)

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "types.hpp"
#include "argparse.hpp"

namespace bttp {
  bool init();
  
  class parameter {
  public:
    static const std::string&              get(const std::string&);
    static const std::vector<std::string>& all();
  };

  enum severity {
    dbg_sv_information,
    dbg_sv_warning,
    dbg_sv_error,
    dbg_sv_critical,
  };

  class debug {
  public:
    // Severity, Info, Message
    static void callback(void(*)(const severity, const std::string&, const std::string&));
    
    static void callinfo (const std::string& info, const std::string& message);
    static void callwarn (const std::string& info, const std::string& message);
    static void callerror(const std::string& info, const std::string& message);
    static void callcrit (const std::string& info, const std::string& message);
  };

  bool logfile(const std::string&);

  class _bt_log {
  public:
    std::ofstream file;
  };

  extern _bt_log log;
}

template<typename T>
bttp::_bt_log& operator<<(bttp::_bt_log& out, T in) {
  if(out.file.is_open())
    out.file << in;
  
  std::cout<< in;
  return out;
}

#endif
