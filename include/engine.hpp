#ifndef BTTP_ENGINE_MAIN_HPP
#define BTTP_ENGINE_MAIN_HPP

#define _BT_M_INFO_ std::string("[") + __FILE__ + "] " + __func__ + " : line " + std::to_string(__LINE__)
#define _BT_M_UNUSED_(var) do { (void)(var); } while (0)

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "types.hpp"
#include "type2d.hpp"
#include "type3d.hpp"
#include "argparse.hpp"
#include "window.hpp"

namespace bt {
  bool init();
  
  class parameter {
  public:
    static const std::string&              get(const std::string&);
    static const std::vector<std::string>& all();
  };

  enum severity {
    dbg_sv_information=0,
    dbg_sv_warning    =1,
    dbg_sv_error      =2,
    dbg_sv_critical   =3,
  };

  const std::string& getseverity(severity);

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
bt::_bt_log& operator<<(bt::_bt_log& out, T in) {
  if(out.file.is_open())
    out.file << in;
  
  std::cout<< in;
  return out;
}

#endif
