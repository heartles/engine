#include <glad/glad.h>
#include "input.h"

void
InputManager::Update(GLFWwindow *window)
{
    std::swap(_thisFrame, _lastFrame);

    auto &input = *_thisFrame;
    for (int i = 0; i < input._keyboard.size(); i++)
    {
        input._keyboard[i] = glfwGetKey(window, i);
    }

    for (int i = 0; i < input._mbuttons.size(); i++)
    {
        input._mbuttons[i] = glfwGetMouseButton(window, i);
    }

    int w, h;
    glfwGetWindowSize(window, &w, &h);

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    input._mouse.x = (2 * static_cast<float>(x) / w) - 1;
    input._mouse.y = 1 - (2 * static_cast<float>(y) / h);
}
