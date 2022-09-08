#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include <App/AppHelloTriangle.hpp>

int main()
{
  try
  {
    real::AppHelloTriangle app; 

    app.Initialize(); 
    app.Run();
    app.Finish();
  }
  catch (std::exception& ex)
  {
    std::cerr << "exception: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}