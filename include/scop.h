# pragma once
# include <stdint.h>


# define WINDOW_WIDTH 800
# define WINDOW_HEIGH 600

typedef struct scopData{
    uint8_t     isRunning;
    GLFWwindow  *window;
} _scopData;