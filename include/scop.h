# pragma once
# include <stdint.h>
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGH 600

typedef struct scopData{
    bool					isRunning;
    GLFWwindow				*window;
} _scopData;

typedef struct vulkanData
{
	VkApplicationInfo		appInfo;
	VkInstance				instance;
	VkInstanceCreateInfo	createInfo;
	VkPhysicalDevice		*selectedDevice;
	uint32_t				devicesCount;
	VkPhysicalDevice		*devices;
} _vulkanData;


uint8_t initVulkan(void);
void	freeVulkanDevices(void);
uint8_t	pickPhysicalDevice(void);