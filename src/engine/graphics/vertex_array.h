#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>
#include "../common.h"
//TODO: we only really need the typedefs from glad.h,
//so we should replace the ones we need with a typedef & a
//static_assert that the two are equal somewhere.
#include <glad/glad.h>
#include <span>

class VertexArray;
class VertexBuffer
{
    friend class VertexArray;

    VertexArray &_vertArr;
    std::vector<float> _underlying;
    size_t _unitCount;
    int _arrayIndex;

    GLuint _handle;

    VertexBuffer(VertexArray &arr, size_t units, GLuint handle, int index);

public:
    VertexBuffer() = delete;
    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer &&) = default;
    VertexBuffer& operator=(VertexBuffer &&) = default;

    void flush();
    inline size_t size();
    inline gsl::span<float> operator[](int index)
    {
        return gsl::span<float>(&_underlying[index * _unitCount], _unitCount);
    }
};

class VertexArray
{
    friend class VertexBuffer;

    std::vector<VertexBuffer> _buffers;
    GLuint _handle;
    size_t _size;

public:
    VertexArray(size_t size);

    void flush();
    VertexBuffer * genBuffer(size_t unitCount = 1);
    inline size_t size() {return _size;};
    void resize(size_t newSize);
    void draw(GLint type, GLint index, GLsizei count);
};

inline size_t
VertexBuffer::size() {return _vertArr.size();}

#endif
