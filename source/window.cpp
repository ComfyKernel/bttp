#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <window.hpp>
#include <engine.hpp>

bool _bt_window_sdl_active = false;

void bt_glCallback(GLenum source, GLenum type, GLuint id,
		   GLenum severity, GLsizei length,
		   const GLchar* message, const void* parameters) {
  _BT_M_UNUSED_(parameters);
  _BT_M_UNUSED_(length);
  
#define _BT_GL_MESSAGE_ std::string("[OPENGL] ") + " ID : [" + std::to_string(id) + "] " + (const char*)message + "\n"

  switch(severity) {
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    bt::debug::callinfo (_BT_M_INFO_, _BT_GL_MESSAGE_);
    break;
  case GL_DEBUG_SEVERITY_LOW:
    bt::debug::callwarn (_BT_M_INFO_, _BT_GL_MESSAGE_);
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    bt::debug::callwarn (_BT_M_INFO_, _BT_GL_MESSAGE_);
    break;
  case GL_DEBUG_SEVERITY_HIGH:
    bt::debug::callerror(_BT_M_INFO_, _BT_GL_MESSAGE_);
    break;
  }

#undef _BT_GL_MESSAGE_
}

class bt::window::_window_impl_ {
public:
  SDL_Window*   window;
  SDL_GLContext ctx;
  SDL_Event     event;
  bool          open;
  bool   shouldClose;

  std::string name;
  version     gl_version;

  void poll() {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
	shouldClose = true;
      }
    }
  }

  void swap() {
    SDL_GL_SwapWindow(window);
  }

  bool w_open(const size& siz, const std::string& nm, const version& glv) {
    if(!_bt_window_sdl_active) {
      if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
	bt::debug::callerror(_BT_M_INFO_, "Failed to initialize SDL2!");
	bt::log<<"Reason : "<<SDL_GetError()<<"\n";

	_bt_window_sdl_active = false;
	return false;
      }
      
      _bt_window_sdl_active = true;
    }

    name       = nm;
    gl_version = glv;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glv.a);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glv.b);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(glv.a >= 3 && glv.b >= 2) {
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			  SDL_GL_CONTEXT_PROFILE_CORE);
    }

    window = SDL_CreateWindow(nm.c_str(),
			      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			      siz.a, siz.b,
			      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!window) {
      bt::debug::callerror(_BT_M_INFO_, "Failed to create an SDL2 Window");
      bt::log<<"Reason : "<<SDL_GetError()<<"\n";
      
      return false;
    }
    
    ctx = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, ctx);

    glewExperimental = GL_TRUE;
    
    GLenum g_stat = glewInit();
    if(g_stat != GLEW_OK) {
      bt::debug::callerror(_BT_M_INFO_, "Failed to initialize GLEW!");
      bt::log<<"Reason : "<<glewGetString(g_stat)<<"\n";

      SDL_GL_DeleteContext(ctx);
      SDL_DestroyWindow(window);
      
      return false;
    }

    bt::debug::callinfo(_BT_M_INFO_, std::string("Using GLEW V.")
			           + std::string((const char*)glewGetString(GLEW_VERSION)));

    if(glewIsSupported("GL_ARB_debug_output")) {
      bt::debug::callinfo(_BT_M_INFO_, "OpenGL Debug Output is supported");

      glEnable(GL_DEBUG_OUTPUT);
      
      glDebugMessageCallback(bt_glCallback, nullptr);
    } else {
      bt::debug::callwarn(_BT_M_INFO_, "OpenGL Debug Output is not supported! Consider updating your drivers.");
    }
    
    open = true;
    
    return true;
  }

  void close() {
    bt::debug::callinfo(_BT_M_INFO_, std::string("Closing window : '")+name+"'");
    
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);

    open = false;
  }
};

bt::window::window()
  : _impl{new _window_impl_()} { }

bt::window::window(const size& siz, const std::string& nam, const version& glv)
  : _impl{new _window_impl_()} {
  open(siz, nam, glv);
}

bool bt::window::open(const size& siz, const std::string& nam, const version& glv) {
  return _impl->w_open(siz, nam, glv);
}

void bt::window::close() {
  if(_impl->open)
    _impl->close();
}

bt::window::~window() {
  if(_impl->open)
    _impl->close();
  
  delete _impl;
}

void bt::window::swap() {
  _impl->swap();
}

bool bt::window::is_open() {
  return _impl->open;
}

bool bt::window::should_close() {
  return _impl->shouldClose;
}

void bt::window::poll() {
  _impl->poll();
}
