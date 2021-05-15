#pragma once

#include "buffer.h"

class IndexBuffer : public Buffer<unsigned int>{
public:
    void putData(unsigned int data[], bool dynamic);
    void updateData(unsigned int data[]);
};
