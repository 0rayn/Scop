#include "scop.h"

extern _vulkanData vData;

void	setVulkanAppInfo(void){
	vData.appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vData.appInfo.pApplicationName = "SCOP";
    vData.appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    vData.appInfo.pEngineName = NULL;
    vData.appInfo.engineVersion = 0;
    vData.appInfo.apiVersion = VK_API_VERSION_1_0;
}

// creates the appInfo for Vulkan driver to know which global extensions and validation layers we'll need
void	createVulkanAppInfo(void){
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	vData.createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vData.createInfo.pApplicationInfo = &vData.appInfo;
	// returns the required instance extensions for Vulkan
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	vData.createInfo.enabledExtensionCount = glfwExtensionCount;
	vData.createInfo.ppEnabledExtensionNames = glfwExtensions;
	// todo: still don't understand this:
	vData.createInfo.enabledLayerCount = 0;
}

bool isDeviceSuitable(VkPhysicalDevice *dev){
	(void)dev;
	return true;
}

void	freeVulkanDevices(void){
	for (uint32_t i = 0; i < vData.devicesCount; i++)
		free(vData.devices[i]);
}

uint8_t	pickPhysicalDevice(void){

	vData.selectedDevice = VK_NULL_HANDLE;
	vkEnumeratePhysicalDevices(vData.instance, &vData.devicesCount, NULL);
	if (!vData.devicesCount){
		perror("Failed to find GPUs with Vulkan Support\n");
		return 1;
	}
	
	vData.devices = malloc(sizeof(VkPhysicalDevice) * vData.devicesCount);
	if (!vData.devices){
		perror("Allocation Failed !\n");
		return 2;
	}
	vkEnumeratePhysicalDevices(vData.instance, &vData.devicesCount, vData.devices);

	for (size_t i = 0; i < vData.devicesCount; i++){
		if (isDeviceSuitable(&vData.devices[i])){
			vData.selectedDevice = &vData.devices[i];
			break;
		}
	}
	if (vData.selectedDevice == VK_NULL_HANDLE){
		perror("Couldn't find a suitable Device for the current Requirements !\n");
		return 3;
	}
	return 0;
}

uint8_t initVulkan(void){
	setVulkanAppInfo();
	createVulkanAppInfo();

	if (vkCreateInstance(&(vData.createInfo), NULL, &(vData.instance)) != VK_SUCCESS){
		perror("Error Creating the Vulkan Instance");
		return 1;
	}

	pickPhysicalDevice();
    return 0;
}