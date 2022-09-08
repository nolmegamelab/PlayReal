#pragma once

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace real {

class App
{
public: 
  App();

  virtual ~App();

  virtual void Initialize() = 0; 

  virtual void Run() = 0; 

  virtual void Finish() = 0;

};

} // namespace real