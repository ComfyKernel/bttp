#include <iostream>

#include <engine.hpp>

int main(int argc, char *argv[]) {
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
