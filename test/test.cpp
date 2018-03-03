#include <iostream>

#include <engine.hpp>

void bttp_debug_callback(const bttp::severity severity,
			 const std::string& info, const std::string& message) {
  bttp::log<<"[BTTP] [Severity "<<severity<<"] "<<info<<"\n       "<<message<<"\n";
}

int main(int argc, char *argv[]) {
  std::cout<<"Setting bttp::debug's callback\n";

  bttp::debug::callback(bttp_debug_callback);

  std::cout<<"\nCalling bttp::init\n";

  bttp::init();

  std::cout<<"\nCalling bttp::log <<\n";

  bttp::log<<"Test message\n";
  bttp::log<<"Test message 2\n";

  bttp::log<<"\nUsing bttp::log for rest of tests\n";
  
  bttp::log<<"\nTesting bttp::parameter::all\n";

  auto _pvec = bttp::parameter::all();

  for(unsigned int i=0; i<_pvec.size(); i+=2) {
    bttp::log<<"[all] Got Pair : "<<_pvec[i]<<" : "<<_pvec[i + 1]<<"\n";
  }
  
  bttp::log<<"\nTesting bttp::parameter::get\n";
  
  bttp::log<<"Using BTTP : \n"
	   <<"Version : "
	   <<bttp::parameter::get("versionMajor")
	   <<"."
	   <<bttp::parameter::get("versionMinor")
	   <<"-"
	   <<bttp::parameter::get("versionFlair")
	   <<"\n";

  bttp::log<<"\nTesting bttp::parameter::get but with a fake key\n";

  bttp::log<<"Key : "
	   <<bttp::parameter::get("obviouslyFake")
	   <<"\n";
  
  return 0;
}
