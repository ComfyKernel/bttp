#include <log.hpp>
#include <formatreader.hpp>

bt::formatreader::formatreader() {
  
}

bt::formatreader::formatreader(const std::string& file) {
  open(file);
}

bool bt::formatreader::is_open() {
  return _fi.is_open();
}

bool bt::formatreader::open(const std::string& file) {
  _fi.open(file);

  if(!_fi.is_open()) {
    bt::debug::callerror(_BT_M_INFO_, "Failed to open inforeader file!");
    return false;
  }

  return true;
}

void bt::formatreader::close() {
  _fi.close();
}

void bt::formatreader::newRule(const std::string& name,
			       __bt_format_function func) {
  _rules.push_back(std::make_pair<std::string, __bt_format_function>(std::string(name), func));
}

void bt::formatreader::read() {

}

void bt::formatreader::setFlag(const std::string& name, bool stat) {
  for(auto& i : _flags) {
    if(i.first == name) {
      i.second = stat;
      return;
    }
  }

  _flags.push_back(std::make_pair<std::string, bool>(std::string(name), stat));
}

bool bt::formatreader::getFlag(const std::string& name) {
  for(const auto& i : _flags) {
    if(i.first == name) {
      return i.second;
    }
  }

  bt::debug::callwarn(_BT_M_INFO_, std::string("Could not find flag : ") + name);

  return false;
}

void bt::formatreader::pushInfo(const std::string& name,
				const std::string& data) {
  for(auto& i : _info) {
    if(i.first == name) {
      i.second = data;
      return;
    }
  }

  _info.push_back(std::make_pair<std::string,std::string>(std::string(name), std::string(data)));
}

const std::string __bt_fr_none = "[Unknown Info]";

const std::string& bt::formatreader::getInfo(const std::string& name) {
  for(const auto& i : _info) {
    if(_info.first == name) {
      return _info.second;
    }
  }

  bt::debug::callwarn(_BT_M_INFO_, std::string("Could not find info : ") + name)

  return __bt_fr_none;
}

void bt::formatreader::pushData(const std::string& name, void* data) {
  _data.push_back(std::make_pair<std::string, void*>(std::string(name), data));
}
