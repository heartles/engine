#include "vertex_array.h"

//TODO: move this into some game object instead of the constructor
VertexArray::VertexArray(size_t size)
    : _size(size)
{
    glGenVertexArrays(1, &_handle);
}

VertexBuffer *
VertexArray::genBuffer(size_t unitCount)
{
    glBindVertexArray(_handle);

    GLuint bufIndex;
    glGenBuffers(1, &bufIndex);

    int index = _buffers.size();
    glBindBuffer(GL_ARRAY_BUFFER, bufIndex);
    glVertexAttribPointer(index, unitCount, GL_FLOAT, GL_FALSE, 0, nullptr);

    _buffers.push_back(VertexBuffer(*this, unitCount, bufIndex, index));
    VertexBuffer &buf = _buffers[_buffers.size() - 1];
    glEnableVertexAttribArray(index);
    buf._underlying.resize(_size * unitCount);

    return &buf;
}

VertexBuffer::VertexBuffer(VertexArray &arr, size_t units, GLuint handle, int index)
    : _vertArr(arr), _unitCount(units), _handle(handle), _arrayIndex(index)
{
    _underlying.resize(units * _vertArr._size);
}

void
VertexBuffer::flush()
{
    glBindVertexArray(_vertArr._handle);
    glBindBuffer(GL_ARRAY_BUFFER, _handle);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof_vector(_underlying),
        _underlying.data(),
        GL_STATIC_DRAW
    );
}

void
VertexArray::flush()
{
    for (auto &buf : _buffers)
    {
        buf.flush();
    }
}

void
VertexArray::draw(GLint type, GLint index, GLsizei count)
{
    glBindVertexArray(_handle);

    glDrawArrays(type, index, count);
}

void
VertexArray::resize(size_t newSize)
{
    glBindVertexArray(_handle);
    for (auto &buf : _buffers)
    {
        buf._underlying.resize(buf._unitCount * newSize);

        glBindBuffer(GL_ARRAY_BUFFER, buf._handle);

        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof_vector(buf._underlying),
            buf._underlying.data(),
            GL_STATIC_DRAW
        );

    }
}
