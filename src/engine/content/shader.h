#include "../common.h"

class Shader
{
    Handle _shader;

public:
    Shader(String vert, String frag);

    void Apply();
}
