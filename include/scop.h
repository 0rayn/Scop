# pragma once
# include <stdint.h>
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGH 600

typedef struct scopData{
    uint8_t					isRunning;
    GLFWwindow				*window;
} _scopData;

typedef struct vulkanData
{
	VkApplicationInfo		appInfo;
	VkInstance				instance;
	VkInstanceCreateInfo	createInfo;
} _vulkanData;


uint8_t initVulkan(void);