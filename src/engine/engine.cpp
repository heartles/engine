#include "engine.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void
Logging::operator()(String s)
{
    std::cout << s << std::endl;
}
