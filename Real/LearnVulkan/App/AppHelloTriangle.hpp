#pragma once

#include <App/App.hpp>

#include <optional>
#include <vector>

namespace real
{

class AppHelloTriangle : public App
{
public: 
  struct QueueFamilyIndices
  {
    std::optional<uint32_t> graphicsFamily;
  };

public: 
  AppHelloTriangle(); 

  ~AppHelloTriangle();

  void Initialize() override;

  void Run() override; 

  void Finish() override;

private: 
  static constexpr int WINDOW_WIDTH = 1280; 
  static constexpr int WINDOW_HEIGHT = 800; 
  
  static inline const std::vector<const char*> validationLayers_ = {
    "VK_LAYER_KHRONOS_validation"
  };

private:
  void InitializeWindow();

  void InitializeVulkan();

  void InitializeDebugMessenger();

  void InitializePhysicalDevice();

  void InitializeDevice();

  void DestroyWindow();

  void DestroyVulkan();

  void DestroyDebugMessenger();

  void DestroyPhysicalDevice();

  void DestroyDevice();

  QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

  bool IsDeviceSuitable(VkPhysicalDevice device);

  bool CheckValidationLayers();

  std::vector<const char*> GetRequiredExtensions();

  VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger
  );

  static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
  ); 

private: 
  GLFWwindow* window_;
  VkInstance instance_;
  VkPhysicalDevice physicalDevice_;
  VkDevice device_;
  VkDebugUtilsMessengerEXT debugMessenger_;
};

} // namespace real