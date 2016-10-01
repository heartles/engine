#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input.h"

struct Logging
{
    void operator ()(String text);
};


template <typename Game_t>
class Engine
{
    Logging Log;
    GLFWwindow *_window;
    InputManager _inputManager {};
    Game_t _game;

public:
    Engine() : _game(*this) {}

    InputManager & InputManager() {return _inputManager;}
    void Init();
    int Run();
};


template <typename Game_t>
void
Engine<Game_t>::Init()
{
    glfwInit();
    auto monitor = glfwGetPrimaryMonitor();
    auto mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    glfwWindowHint(GLFW_RESIZABLE, false);

    _window = glfwCreateWindow(mode->width, mode->height, "cpp playground", nullptr, nullptr);

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    _game.Init();
}

template <typename Game_t>
int
Engine<Game_t>::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        _inputManager.Update(_window);

        _game.Frame();
    }
}
