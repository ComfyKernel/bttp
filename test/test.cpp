#include <iostream>

#include <engine.hpp>

void bttp_debug_callback(const bt::severity severity,
			 const std::string& info, const std::string& message) {
  bt::log<<"[BTTP] ["<<bt::getseverity(severity)
	 <<"] "<<info<<"\n       "
	 <<message<<"\n";
}

int main(int argc, char *argv[]) {
  std::cout<<"Setting bt::debug's callback\n";

  bt::debug::callback(bttp_debug_callback);

  std::cout<<"\nCalling bt::init\n";

  bt::init();

  std::cout<<"\nCalling bt::log <<\n";

  bt::log<<"Test message\n";
  bt::log<<"Test message 2\n";

  bt::log<<"\nUsing bt::log for rest of tests\n";
  
  bt::log<<"\nTesting bt::parameter::all\n";

  auto _pvec = bt::parameter::all();

  for(unsigned int i=0; i<_pvec.size(); i+=2) {
    bt::log<<"[all] Got Pair : "<<_pvec[i]<<" : "<<_pvec[i + 1]<<"\n";
  }
  
  bt::log<<"\nTesting bt::parameter::get\n";
  
  bt::log<<"Using BTTP : \n"
	 <<"Version : "
	 <<bt::parameter::get("versionMajor")
	 <<"."
	 <<bt::parameter::get("versionMinor")
	 <<"-"
	 <<bt::parameter::get("versionFlair")
	 <<"\n";

  bt::log<<"\nTesting bttp::parameter::get but with a fake key\n";

  bt::log<<"Key : "
	 <<bt::parameter::get("obviouslyFake")
	 <<"\n";
  
  return 0;
}
