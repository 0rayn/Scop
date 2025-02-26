#include "scop.h"

extern _vulkanData vData;

uint32_t rateDeviceSuitability(VkPhysicalDevice *dev){
	uint32_t					score;
	VkPhysicalDeviceFeatures	deviceFeatures;
	VkPhysicalDeviceProperties	deviceProperties;
	
	// optional features like texture compression, 64 bit floats and multi viewport rendering
	vkGetPhysicalDeviceFeatures(*dev, &deviceFeatures);
	// Basic device properties like the name, type and supported Vulkan version
	vkGetPhysicalDeviceProperties(*dev, &deviceProperties);
	score = 0;
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score = 1000; // a dedicated graphics card, not an integrated one

	// Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;
	if (!deviceFeatures.geometryShader) // Checks if the GPU supports geometry shaders.
		return 0;
	
	return score;
}

void	freeVulkanDevices(void){
	if (vData.devices) {
		free(vData.devices);
		vData.devices = NULL;
	}
}

VkPhysicalDevice	*pickDeviceByRating(void){
	VkPhysicalDevice	*dev;
	uint32_t			rating, bestRating;
	
	dev = VK_NULL_HANDLE;
	rating = bestRating = 0;
	for (size_t i = 0; i < vData.devicesCount; i++){
		rating = rateDeviceSuitability(&vData.devices[i]);
		if (rating > bestRating){
			bestRating = rating;
			dev = &vData.devices[i];
		}
	}
	return dev;
}

uint8_t	pickPhysicalDevice(void){

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

	vData.selectedDevice = pickDeviceByRating();
	if (vData.selectedDevice == VK_NULL_HANDLE){
		perror("Couldn't find a suitable Device for the current Requirements !\n");
		return 3;
	}
	return 0;
}