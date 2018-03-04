#include <iostream>

#include <engine.hpp>

bool test_type2d();
bool test_type3d();

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

  test_type2d();
  test_type3d();

  bt::log<<"\nTesting window creation / Deletion\n";

  bt::log<<"Creating a window\n";

  bt::window win(size(1280, 720), "Test Window", bt::version(3, 2));

  bt::log<<"Closing a window\n";

  win.close();
  
  return 0;
}

bool test_type2d() {
  bt::log<<"\nTesting type2d<int>\n";

  type2d<int> test(10, 20);

  bt::log<<"Result after creation       : "<<test<<"\n";
  bt::log<<"Using operand (10, 5)\n";

  bt::log<<"Result after addition       : "<<(test + type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after multiplication : "<<(test * type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after division       : "<<(test / type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after modulo         : "<<(test % type2d<int>(10, 5))<<"\n";
  
  bt::log<<"\nTesting type2d<float>\n";

  type2d<float> test2(10, 20);

  bt::log<<"Result after creation       : "<<test<<"\n";
  bt::log<<"Using operand (10, 5)\n";

  bt::log<<"Result after addition       : "<<(test2 + type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test2 - type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after multiplication : "<<(test2 * type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after division       : "<<(test2 / type2d<float>(10, 5))<<"\n";

  bt::log<<"\nTesting type2d<int> mixed with type2d<float>\n";
  bt::log<<"Using operand (10, 5) as float\n";

  bt::log<<"Result after addition       : "<<(test + type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after multiplication : "<<(test * type2d<float>(10, 5))<<"\n";
  bt::log<<"Result after division       : "<<(test / type2d<float>(10, 5))<<"\n";

  bt::log<<"\nTesting operator assignment to type2d<int>\n";
  bt::log<<"Using operand (10, 5)\n";
  
  bt::log<<"Result after addition assignment       : "<<(test += type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after subtraction assignment    : "<<(test -= type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after multiplication assignment : "<<(test *= type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after division assignment       : "<<(test /= type2d<int>(10, 5))<<"\n";
  bt::log<<"Result after modulo assignment         : "<<(test %= type2d<int>(10, 5))<<"\n";

  bt::log<<"\nNot testing type2d<float>, Assumed to work\n";

  bt::log<<"\nTesting real assignment to type2d<int>\n";
  bt::log<<"Using operand (10, 5)\n";

  bt::log<<"Result after assignment : "<<(test = type2d<int>(10, 5))<<"\n";

  bt::log<<"Using operand (10, 20) as float\n";

  bt::log<<"Result after assignment : "<<(test = type2d<float>(10, 20))<<"\n";

  bt::log<<"\nTesting type2d<int> with single\n";
  bt::log<<"Using operand (10)\n";

  bt::log<<"Result after addition       : "<<(test + 10)<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - 10)<<"\n";
  bt::log<<"Result after multiplication : "<<(test * 10)<<"\n";
  bt::log<<"Result after division       : "<<(test / 10)<<"\n";
  bt::log<<"Result after modulo         : "<<(test % 10)<<"\n";

  bt::log<<"\nNot cross testing types, assumed to work\n";

  bt::log<<"\nTesting type2d<int> assigning with single\n";
  bt::log<<"Using operand (10)\n";

  bt::log<<"Result after addition assignment       : "<<(test += 10)<<"\n";
  bt::log<<"Result after subtraction assignment    : "<<(test -= 10)<<"\n";
  bt::log<<"Result after multiplication assignment : "<<(test *= 10)<<"\n";
  bt::log<<"Result after division assignment       : "<<(test /= 10)<<"\n";
  bt::log<<"Result after modulo assignment         : "<<(test %= 10)<<"\n";

  bt::log<<"\nNot cross testing types, assumed to work\n";

  return true;
}

bool test_type3d() {
  bt::log<<"\nTesting type3d<int>\n";

  type3d<int> test(10, 20, 30);

  bt::log<<"Result after creation       : "<<test<<"\n";
  bt::log<<"Using operand (10, 5, 20)\n";

  bt::log<<"Result after addition       : "<<(test + type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after multiplication : "<<(test * type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after division       : "<<(test / type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after modulo         : "<<(test % type3d<int>(10, 5, 20))<<"\n";

  bt::log<<"\nTesting type3d<float>\n";

  type3d<float> test2(10, 20, 30);

  bt::log<<"Result after creation       : "<<test<<"\n";
  bt::log<<"Using operand (10, 5, 20)\n";

  bt::log<<"Result after addition       : "<<(test2 + type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test2 - type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after multiplication : "<<(test2 * type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after division       : "<<(test2 / type3d<float>(10, 5, 20))<<"\n";

  bt::log<<"\nTesting type3d<int> mixed with type3d<float>\n";
  bt::log<<"Using operand (10, 5, 20) as float\n";

  bt::log<<"Result after addition       : "<<(test + type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after multiplication : "<<(test * type3d<float>(10, 5, 20))<<"\n";
  bt::log<<"Result after division       : "<<(test / type3d<float>(10, 5, 20))<<"\n";

  bt::log<<"\nTesting operator assignment to type3d<int>\n";
  bt::log<<"Using operand (10, 5, 20)\n";
  
  bt::log<<"Result after addition assignment       : "<<(test += type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after subtraction assignment    : "<<(test -= type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after multiplication assignment : "<<(test *= type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after division assignment       : "<<(test /= type3d<int>(10, 5, 20))<<"\n";
  bt::log<<"Result after modulo assignment         : "<<(test %= type3d<int>(10, 5, 20))<<"\n";

  bt::log<<"\nNot testing type3d<float>, Assumed to work\n";

  bt::log<<"\nTesting real assignment to type3d<int>\n";
  bt::log<<"Using operand (10, 5, 20)\n";

  bt::log<<"Result after assignment : "<<(test = type3d<int>(10, 5, 20))<<"\n";

  bt::log<<"Using operand (10, 20, 30) as float\n";

  bt::log<<"Result after assignment : "<<(test = type3d<float>(10, 20, 30))<<"\n";

  bt::log<<"\nTesting type3d<int> with single\n";
  bt::log<<"Using operand (10)\n";

  bt::log<<"Result after addition       : "<<(test + 10)<<"\n";
  bt::log<<"Result after subtraction    : "<<(test - 10)<<"\n";
  bt::log<<"Result after multiplication : "<<(test * 10)<<"\n";
  bt::log<<"Result after division       : "<<(test / 10)<<"\n";
  bt::log<<"Result after modulo         : "<<(test % 10)<<"\n";

  bt::log<<"\nNot cross testing types, assumed to work\n";

  bt::log<<"\nTesting type3d<int> assigning with single\n";
  bt::log<<"Using operand (10)\n";

  bt::log<<"Result after addition assignment       : "<<(test += 10)<<"\n";
  bt::log<<"Result after subtraction assignment    : "<<(test -= 10)<<"\n";
  bt::log<<"Result after multiplication assignment : "<<(test *= 10)<<"\n";
  bt::log<<"Result after division assignment       : "<<(test /= 10)<<"\n";
  bt::log<<"Result after modulo assignment         : "<<(test %= 10)<<"\n";

  bt::log<<"\nNot cross testing types, assumed to work\n";
  
  return true;
}
