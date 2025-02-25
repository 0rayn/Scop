#include "scop.h"

/*
	https://vulkan-tutorial.com/en
	https://registry.khronos.org/vulkan/specs/latest/man/html/VkApplicationInfo.html
*/

_scopData	scop;
_vulkanData vData;

uint8_t initGLFW(void){
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // Ensure no OpenGL context is created
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);     // disable resize of the window
    scop.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, "SCOP TEST", NULL, NULL);
    if (!scop.window)
        return 1;
    return 0;
}

uint8_t init(void){
	scop.isRunning = 0;
    if (initGLFW() || initVulkan())
        return 1;
    return 0;
}

uint8_t renderLoop(void){
    while (scop.isRunning && !glfwWindowShouldClose(scop.window)) {
    	glfwPollEvents();
	}
    return 0;
}

void    cleanUp(void){
	printf("CleanUp and Exit\n");
	vkDestroyInstance(vData.instance, NULL);
    glfwDestroyWindow(scop.window);
    glfwTerminate();
}

int main(void) {
    atexit(cleanUp);
    if (init())
    	return 1;
	if (renderLoop())
		return 2;
    return 0;
}