#include <algorithm>

#include <engine.hpp>

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
      return __bt_prop_parameters[i + 1];
    }
  }

  return __bt_prop_parameter_unknown;
}
