#include <iostream>
#include <utility>
#include <string>

#include <engine.hpp>

#include <GL/glew.h>

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

  bt::log<<"\nTesting formatreader\n";

  bt::log<<"Creating the reader\n";

  bt::formatreader fri("test.info");
  
  auto fr_i_type = [&](bt::formatreader& fr,
		       const std::string& data) -> void {
    bt::log<<"Adding type : "<<data<<"\n";
    
    if(data == "list") {
      bt::log<<"Setting the 'isList' flag\n";
      fr.setFlag("isList", true);
    } else {
      fr.setFlag("isList", false);
    }
    
    fr.pushInfo("type", data);
  };

  auto fr_i_name = [&](bt::formatreader& fr,
		       const std::string& data) -> void {
    void* _value;

    bt::log<<"Pushing data : "<<data<<" : of type : "<<fr.getInfo("type")<<"\n";

    const std::string& type = fr.getInfo("type");
    
    if(type == "uint") {
      _value = new uint(std::stoul(fr.nextString()));
    } else if(type =="int") {
      _value = new int(std::stol(fr.nextString()));
    } else {
      _value = NULL;
    }

    fr.pushData(data, _value);
  };

  bt::log<<"Adding new rules\n";
  
  fri.newRule("*(*)", fr_i_type);
  fri.newRule("*[*]", fr_i_name);

  fri.splitInfo="])\n";
  
  bt::log<<"Reading\n";

  fri.read();

  bt::log<<"\nTesting window creation / Deletion\n";

  bt::log<<"Creating a window\n";

  bt::window win(size(1280, 720), "Test Window", bt::version(3, 2));

  bt::log<<"Closing a window\n";

  win.close();

  bt::log<<"\nTesting graphics, running triangle testing for 30 frames\n";

  bt::window wind(size(1280, 720), "Testing Window", bt::version(3, 2));
  
  uint32 frames = 0;

  glClearColor(0, 0, 0, 1);

  bt::log<<"Finished creating the Vertex Array Object\n";

  bt::log<<"\nTesting buffer creation & binding\n";

  bt::gl::buffer<float> vertices({-1.f , -1.f,
	                           0.f , -1.f,
     	                          -0.5f,  0.f},
    GL_ARRAY_BUFFER, GL_STATIC_DRAW);

  bt::gl::buffer<uint> indices({0, 1, 2},
			       GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

  bt::gl::buffer<float> vertices2({
        0.f, 0.f,
	1.f, 0.f,
	0.5f, 1.f},
    GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  
  bt::log<<"Finished creating buffers\n";

  bt::log<<"\nCreating a Vertex Array Object\n";

  bt::gl::vao dvao;
  dvao.create();
  dvao.bind();

  glEnableVertexAttribArray(0);

  vertices2.bind();
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);

  indices.bind();
  
  bt::gl::vao tvao;
  tvao.create();
  tvao.bind();

  glEnableVertexAttribArray(0);

  vertices.bind();
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);

  indices.bind();

  dvao.bind();
  
  bt::log<<"\nCreating shaders\n";

  bt::gl::shader vshad("test_vert.glsl", GL_VERTEX_SHADER);
  bt::gl::shader fshad("test_frag.glsl", GL_FRAGMENT_SHADER);

  bt::log<<"Finished creating shaders\n";
  bt::log<<"\nCreating shader program\n";

  bt::gl::program testprog({vshad, fshad});

  bt::log<<"Finished creating the program\n";  
  bt::log<<"\nStarting loop\n";

  testprog.use();

  glEnableVertexAttribArray(0);
  
  while(frames < 30) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tvao.bind();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);

    dvao.bind();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
    
    wind.poll();
    
    wind.swap();
    
    frames += 1;
  }
  
  bt::log<<"Closing the window\n";

  wind.close();
  
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
