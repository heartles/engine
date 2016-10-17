#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

template <typename T>
size_t sizeof_vector(std::vector<T> vector)
{
    return vector.size() * sizeof(T);
}

typedef std::string String;
typedef size_t Handle;

#endif
