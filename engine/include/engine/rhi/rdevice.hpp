#ifndef RDEVICE_HPP
#define RDEVICE_HPP

#include <vector>
#include <volk.h>
#include <GLFW/glfw3.h>
#include "vk_mem_alloc.h"

class RDevice{
private:
    VkInstance _instance;
    VkDevice _device;
    VkSurfaceKHR _surface;
    VkPhysicalDevice _physDevice;

    VmaAllocator _allocator;

    uint32_t _presentFamily;
    uint32_t _graphicsFamily;
    VkQueue _graphicsQ;
    VkQueue _computeQ;
    // VKQueue _rtQ;
public:
    RDevice(GLFWwindow* w);
    ~RDevice();

    RDevice(const RDevice&) = delete;
    RDevice& operator=(const RDevice&) = delete;
    RDevice(RDevice&&) = delete;
    RDevice& operator=(RDevice&&) = delete;
};

#endif // RDEVICE_HPP