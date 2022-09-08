#include <App/AppHelloTriangle.hpp>
#include <fmt/format.h>

namespace real
{

AppHelloTriangle::AppHelloTriangle()
  : window_{nullptr}
  , instance_{nullptr}
  , debugMessenger_{nullptr}
{
}

AppHelloTriangle::~AppHelloTriangle()
{
  assert(window_ == nullptr);
  assert(instance_ == nullptr);
  assert(debugMessenger_ == nullptr);
}

void AppHelloTriangle::Initialize()
{
  InitializeWindow();
  InitializeVulkan();
  InitializeDebugMessenger();
}

void AppHelloTriangle::Run()
{
  while (!glfwWindowShouldClose(window_))
  {
    glfwPollEvents();
  }
}

void AppHelloTriangle::Finish()
{
  // DestroyDebugMessenger();
  DestroyVulkan();
  DestroyWindow();
}

void AppHelloTriangle::InitializeWindow()
{
  glfwInit();

  // OpenGL 셋업을 GLFW_NO_API로 비활성화 
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // resize 기능을 막음 (임시)
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle", nullptr, nullptr);
}

void AppHelloTriangle::InitializeVulkan()
{
  if (!CheckValidationLayers())
  {
    throw std::runtime_error("validation layer is not supported");
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  // get extensions from glfw
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  // enable extensions required including debug util
  auto extensions = GetRequiredExtensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  // enable validation layers
  createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers_.size());
  createInfo.ppEnabledLayerNames = validationLayers_.data();

  auto result = vkCreateInstance(&createInfo, nullptr, &instance_);

  if (result != VK_SUCCESS)
  {
    throw std::runtime_error(fmt::format("cannot create vulkan instance"));
  }
}

void AppHelloTriangle::InitializeDebugMessenger()
{
  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = DebugCallback;
  createInfo.pUserData = nullptr; // Optional

  if (CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &debugMessenger_) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to set up debug messenger!");
  }
}

void AppHelloTriangle::DestroyWindow()
{
  glfwDestroyWindow(window_);
  glfwTerminate();

  window_ = nullptr;
}

void AppHelloTriangle::DestroyVulkan()
{
  vkDestroyInstance(instance_, nullptr);

  instance_ = nullptr;
}

void AppHelloTriangle::DestroyDebugMessenger()
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance_, "vkDestroyDebugUtilsMessengerEXT"
  );

  if (func != nullptr) 
  {
    func(instance_, debugMessenger_, nullptr);
  }

  debugMessenger_ = nullptr;
}

std::vector<const char*> AppHelloTriangle::GetRequiredExtensions()
{
  uint32_t glfwExtensionCount = 0;

  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
  extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return extensions;
}

bool AppHelloTriangle::CheckValidationLayers()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : validationLayers_) 
  {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) 
    {
      if (strcmp(layerName, layerProperties.layerName) == 0) 
      {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) 
    {
      return false;
    }
  }

  return true;
}

VkResult AppHelloTriangle::CreateDebugUtilsMessengerEXT(
  VkInstance instance, 
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
  const VkAllocationCallbacks* pAllocator, 
  VkDebugUtilsMessengerEXT* pDebugMessenger) 
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance, "vkCreateDebugUtilsMessengerEXT"
  );

  if (func != nullptr) 
  {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }
  // else 
  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VKAPI_ATTR VkBool32 VKAPI_CALL AppHelloTriangle::DebugCallback(
 VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
 VkDebugUtilsMessageTypeFlagsEXT messageType,
 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
 void* pUserData
) 
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}


} // namespace real
