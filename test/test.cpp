#include <iostream>

#include <engine.hpp>

void bttp_debug_callback(const bttp::severity severity,
			 const std::string& info, const std::string& message) {
  std::cout<<"[BTTP] [Severity "<<severity<<"] "<<info<<"\n       "<<message<<"\n";
}

int main(int argc, char *argv[]) {
  std::cout<<"Setting bttp::debug's callback\n";

  bttp::debug::callback(bttp_debug_callback);
  
  std::cout<<"Testing bttp::parameter::all\n";

  auto _pvec = bttp::parameter::all();

  for(unsigned int i=0; i<_pvec.size(); i+=2) {
    std::cout<<"[all] Got Pair : "<<_pvec[i]<<" : "<<_pvec[i + 1]<<"\n";
  }
  
  std::cout<<"\nTesting bttp::parameter::get\n";
  
  std::cout<<"Using BTTP : \n"
	   <<"Version : "
	   <<bttp::parameter::get("versionMajor")
	   <<"."
	   <<bttp::parameter::get("versionMinor")
	   <<"-"
	   <<bttp::parameter::get("versionFlair")
	   <<"\n";
  
  return 0;
}
