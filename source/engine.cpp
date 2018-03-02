#include <algorithm>

#include <engine.hpp>

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

const std::string& bttp::parameter::get(const std::string& name) {
  for(unsigned int i=0; i<__bt_prop_parameters.size(); ++i) {
    if(__bt_prop_parameters[i] == name) {
      if(i%2 != 0) {
	return __bt_prop_parameters[i - 1];
      }
      
      return __bt_prop_parameters[i + 1];
    }
  }

  return __bt_prop_parameter_unknown;
}

const std::vector<std::string>& bttp::parameter::all() {
  // bttp::debug::callinfo(_BT_M_INFO_, "Test message");
  
  return __bt_prop_parameters;
}

//       //
// DEBUG //
//       //

void (*__bt_debug_callback)(const bttp::severity, const std::string&, const std::string&) = nullptr;

void bttp::debug::callback(void(*cb)(const bttp::severity, const std::string&, const std::string&)) {
  __bt_debug_callback = cb;
}

#define __BT_M_DBG_CALL(nam,sev)				  \
  void nam(const std::string& info, const std::string& message) { \
  if(__bt_debug_callback==nullptr) return;                        \
    __bt_debug_callback(sev, info, message);			  \
  }								  \

__BT_M_DBG_CALL(bttp::debug::callinfo , bttp::severity::dbg_sv_information);
__BT_M_DBG_CALL(bttp::debug::callwarn , bttp::severity::dbg_sv_warning    );
__BT_M_DBG_CALL(bttp::debug::callerror, bttp::severity::dbg_sv_error      );
__BT_M_DBG_CALL(bttp::debug::callcrit , bttp::severity::dbg_sv_critical   );

#undef __BT_M_DBG_CALL
