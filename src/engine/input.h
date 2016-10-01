#include <stdint.h>
#include <bitset>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class Button
{
public:
    using index_t = uint16_t;

private:
    index_t _index;

public:
    static constexpr index_t Shift = 9; //TODO: fix value and add other constants

    Button(const char c);
    Button(std::string name);
    Button(index_t i);
};

class Axis
{
public:
    using index_t = uint16_t;

private:
    index_t _index;

public:
    static constexpr index_t MouseX = 0;
    static constexpr index_t MouseY = 1;
    //TODO: add other constants

    Axis(std::string name);
};

struct Input
{
    std::bitset<349> _keyboard;
    std::bitset<8> _mbuttons;
    glm::vec2 _mouse;

    inline const bool Key(int keyCode) {return _keyboard[keyCode];}
    inline const bool MouseButton(int mButton) {return _mbuttons[mButton];}
    inline const glm::vec2 & Mouse() {return _mouse;}
    inline const bool operator[](Button::index_t i)
    {
        return _keyboard[i]; //TODO: support mouse
    }
};

class InputManager
{
    std::vector<Input> _raw = std::vector<Input>(2);
    Input *_thisFrame = &_raw[0], *_lastFrame = &_raw[1];

public:
    inline const bool Button(Button::index_t i) {return (*_thisFrame)[i];}
    inline const bool ButtonPressed(Button::index_t i) {return (*_thisFrame)[i] && !(*_lastFrame)[i];}
    inline const bool ButtonReleased(Button::index_t i) {return !(*_thisFrame)[i] && (*_lastFrame)[i];}
    inline const glm::vec2 & Mouse() {return _thisFrame->Mouse();}

    void Update(GLFWwindow *);
};
