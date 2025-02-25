#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "scop.h"
#include <stdlib.h>
#include <stdio.h>

_scopData scop;

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

uint8_t initVulkan(void){
    return 0;
}

uint8_t init(void){
    if (initGLFW() || initVulkan())
        return 1;
    return 0;
}

uint8_t renderLoop(void){
    while (1);
    return 0;
}

void    cleanUp(void){
    fprintf(stdout, "EXIT\n");
}

int main(void) {
    atexit(cleanUp);
    if (init())
        return 1;
    if (renderLoop())
        return 2;
    return 0;
}