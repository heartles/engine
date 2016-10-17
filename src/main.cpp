#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.h"

template <typename T>
void assign(gsl::span<T> span, std::initializer_list<T> arr)
{
    int i = 0;
    auto y = arr.begin();

    while (y != arr.end())
    {
        span[i++] = *(y++);
    }
}

struct Game
{
    Engine<Game> &E;
    Game(Engine<Game> &engine)
        : E(engine){};

    VertexArray *_vertArr;
    VertexBuffer *_vBuf;
    void Init()
    {
        _vertArr = new VertexArray(3);
        _vBuf = _vertArr->genBuffer(3);
        auto &vertArr = *_vertArr;
        auto &vBuf = *_vBuf;
        assign(vBuf[0], {0.0f, 1.0f, 0.0f});
        assign(vBuf[1], {-1.0f, -1.0f, 0.0f});
        assign(vBuf[2], {1.0f, -1.0f, 0.0f});
        _vertArr->flush();
    }

    void Frame()
    {
        if (E.InputManager().Button(GLFW_KEY_ESCAPE))
            std::exit(0);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        _vertArr->draw(GL_TRIANGLES, 0, 3);
    }
};

int main(int argc, char **argv)
{
    Engine<Game> e{};

    e.Init();
    e.Run();
}
