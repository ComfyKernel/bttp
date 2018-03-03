#include <algorithm>

#include <engine.hpp>

bt::_bt_log bt::log = _bt_log();

bool bt::init() {
  if(!logfile("bttp.log")) {
    debug::callwarn(_BT_M_INFO_, "Failed to open logfile! Using STD::COUT only");
  }

  return true;
}

//           //
// PARAMETER //
//           //

const std::vector<std::string> __bt_prop_parameters = {
  "versionMajor", "0",
  "versionMinor", "1",
  "versionFlair", "Early",

  "author", "ComfyKernel",
  "email" , "comfykernel@gmail.com"
};

const std::string __bt_prop_parameter_unknown = "[Unknown Parameter]";

const std::string& bt::parameter::get(const std::string& name) {
  for(unsigned int i=0; i<__bt_prop_parameters.size(); ++i) {
    if(__bt_prop_parameters[i] == name && i % 2 == 0) {      
      return __bt_prop_parameters[i + 1];
    }
  }

  bt::debug::callwarn(_BT_M_INFO_,
		      std::string("Could not find parameter '" +
				  name + "'"));

  return __bt_prop_parameter_unknown;
}

const std::vector<std::string>& bt::parameter::all() {
  // bttp::debug::callinfo(_BT_M_INFO_, "Test message");
  
  return __bt_prop_parameters;
}

//       //
// DEBUG //
//       //

const std::vector<std::string> __bt_severities = {
  "information",
  "warning",
  "error",
  "critical"
};

const std::string& bt::getseverity(bt::severity sev) {
  return __bt_severities[sev];
}

void (*__bt_debug_callback)(const bt::severity, const std::string&, const std::string&) = nullptr;

void bt::debug::callback(void(*cb)(const bt::severity, const std::string&, const std::string&)) {
  __bt_debug_callback = cb;
}

#define __BT_M_DBG_CALL(nam,sev)				  \
  void nam(const std::string& info, const std::string& message) { \
  if(__bt_debug_callback==nullptr) return;                        \
    __bt_debug_callback(sev, info, message);			  \
  }								  \

__BT_M_DBG_CALL(bt::debug::callinfo , bt::severity::dbg_sv_information);
__BT_M_DBG_CALL(bt::debug::callwarn , bt::severity::dbg_sv_warning    );
__BT_M_DBG_CALL(bt::debug::callerror, bt::severity::dbg_sv_error      );
__BT_M_DBG_CALL(bt::debug::callcrit , bt::severity::dbg_sv_critical   );

#undef __BT_M_DBG_CALL

//         //
// LOGGING //
//         //

bool bt::logfile(const std::string& name) {
  if(log.file.is_open()) {
    log.file.close();
  }

  log.file.open(name);

  if(!log.file.is_open()) {
    debug::callerror(_BT_M_INFO_, std::string("Failed opening logfile '") + name + "'");
    return false;
  }

  return true;
}
