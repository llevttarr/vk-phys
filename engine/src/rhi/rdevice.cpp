#include "rdevice.hpp"

RDevice::RDevice(GLFWwindow* w){
    if (volk_initialize()!=VK_SUCCESS){
        // TODO throw
        return;
    }

    VkApplicationInfo iApp{};
    iApp.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    iApp.pApplicationName = "Physics system";
    iApp.applicationVersion = VK_MAKE_VERSION(1,0,0);
    iApp.pEngineName = "Physics engine";
    iApp.engineVersion = VK_MAKE_VERSION(1,0,0);
    iApp.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo iCreate{};
    iCreate.sType = sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    iCreate.pApplicationInfo = &iApp;

    uint32_t glfwExN = 0;
    const char** glfwEx = glfwGetRequiredInstanceExtensions(&glfwExN);
    std::vector<const char*> glfwExVec(glfwEx,glfwEx+glfwExN);

    // todo: debug extensions if debug enabled

    iCreate.enabledExtensionCount = glfwExVec.size();
    iCreate.ppEnabledExtensionNames = glfwExVec.data();

    // const char* validationLayers[] = { "VK_LAYER_KHRONOS_validation" };
    // iCreate.enabledLayerCount = 1;
    // iCreate.ppEnabledLayerNames = validationLayers;

    iCreate.enabledLayerCount = 0;
    if (vkCreateInstance(&iCreate, nullptr, &_instance) != VK_SUCCESS) {
        // TODO: throw
        return;
    }
    if(volkLoadInstance() != VK_SUCCESS){
        // TODO: throw
        return;
    }

    // DEBUGGER


    if (glfwCreateWindowSurface(_instance, w, nullptr, &_surface) != VK_SUCCESS) {
        // TODO: throw
        return;
    }
    _physDevice = VK_NULL_HANDLE;
}
