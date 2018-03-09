#include <tuple>
#include <sstream>

#include <log.hpp>
#include <types.hpp>
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
  _rules.push_back(std::pair<std::string, __bt_format_function>(name, func));
}

const std::string __bt_fr_nosegment = "";

const std::string& bt::formatreader::nextString() {
  if(_segments.size() <= _sptr) {
    bt::debug::callwarn(_BT_M_INFO_, "Out of segments!");
    return __bt_fr_nosegment;
  }

  ++_sptr;
  return _segments[_sptr];
}

bool bt::formatreader::read() {
  if(!is_open()) {
    bt::debug::callerror(_BT_M_INFO_, "Cannot read the data from an unopened file!");
    return false;
  }

  bt::log<<"Creating _crtable\n";
  
  std::vector<std::tuple<char, uint, uint>> _crtable;

  bt::log<<"Processing rules\n";

  for(uint i=0; i<_rules.size(); ++i) {
    for(uint s=0; s<_rules[i].first.size(); ++s) {
      uint rstate;
      
      switch(_rules[i].first[s]) {
      case '+':
	rstate=1;
	break;
      case '*':
	rstate=2;
	break;
      default:
	_crtable.push_back(std::tuple<char, uint, uint>(_rules[i].first[s], rstate, i));
	break;
      }
    }
  }

  bt::log<<"Reading string buffer\n";

  std::stringstream _str;
  _str << _fi.rdbuf();

  bt::log<<"Splitting into segments\n";

  std::string __c_segment = "";
  
  for(uint i=0; i<_str.str().size(); ++i) {
    for(uint si=0; si<splitInfo.size(); ++si) {
      if(_str.str()[i] == splitInfo[si]) {
	if(__c_segment.empty())
	  continue;

	if(_str.str()[i] != '\n') {
	  __c_segment += _str.str()[i];
	}
	bt::log<<"Got segment : "<<__c_segment<<"\n";
	_segments.push_back(__c_segment);
	i++;
	__c_segment="";
	continue;
      }
    }

    switch(_str.str()[i]) {
    case ' ':
    case '\t':
    case '\n':
      break;
    default:
      __c_segment += _str.str()[i];
      continue;
      break;
    }
  }

  bt::log<<"Interpreting\n";

  for(uint i=0; i<_segments.size(); ++i) {
    uint rstate=2;
    char mchar ='\0';
    for(uint r=0; r<_crtable.size(); ++r) {
      switch (std::get<2>(_crtable[r])) {
      case 0:
	break;
      case 1:
	break;
      case 2:
	if(rstate == 2 && !((r + 1) >= _crtable.size())) {
	  if(_segments[i][0] == mchar &&
	     _segments[i][_segments[i].size() - 1] == std::get<0>(_crtable[r])) {
	    bt::log<<"Calling rule\n";
	    
	    _rules[std::get<2>(_crtable[r])].second
	      (*this, _segments[i].substr(1, _segments[i].size() - 2));

	    rstate=0;
	    mchar='\0';
	    break;
	  }
	}

	mchar  = std::get<0>(_crtable[r]);
	rstate = 2;
	break;
      }
    }
  }
  
  return true;
}

void bt::formatreader::setFlag(const std::string& name, bool stat) {
  for(auto& i : _flags) {
    if(i.first == name) {
      i.second = stat;
      return;
    }
  }

  _flags.push_back(std::pair<std::string, bool>(name, stat));
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

  _info.push_back(std::pair<std::string,std::string>(std::string(name), std::string(data)));
}

const std::string __bt_fr_none = "[Unknown Info]";

const std::string& bt::formatreader::getInfo(const std::string& name) {
  for(const auto& i : _info) {
    if(i.first == name) {
      return i.second;
    }
  }

  bt::debug::callwarn(_BT_M_INFO_, std::string("Could not find info : ") + name);

  return __bt_fr_none;
}

void bt::formatreader::pushData(const std::string& name, void* data) {
  _data.push_back(std::pair<std::string, void*>(std::string(name), data));
}
