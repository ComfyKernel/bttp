#ifndef BTTP_ENGINE_MAIN_HPP
#define BTTP_ENGINE_MAIN_HPP

#define _BT_M_INFO_ std::string("[") + __FILE__ + "] " + __func__ + " : line " + std::to_string(__LINE__)

#include <string>
#include <vector>

#include "types.hpp"
#include "argparse.hpp"

namespace bttp {
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
}

#endif
