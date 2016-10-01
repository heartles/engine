#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.h"

struct Game
{
    Engine<Game> &E;
    Game(Engine<Game> &engine)
        : E(engine){};
    void Init(){}
    void Frame()
    {
        if (E.InputManager().Button(GLFW_KEY_ESCAPE))
            std::exit(0);
    }
};

int main(int argc, char **argv)
{
    Engine<Game> e{};

    e.Init();
    e.Run();
}
