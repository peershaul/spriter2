#include "vertex.h"
#include "../../utils/error.h"
#include "../../utils/logger.h"

#include <GL/glew.h>

unsigned int VertexBuffer::bound = 0;

VertexBuffer::VertexBuffer(){
    GLE(glGenBuffers(1, &id));
}

void VertexBuffer::putData(float* data, unsigned int length, bool dynamic){
    this->data = data;
    this->length = length;

    unsigned int was_bound = get_bound();
    s_bind(id);

    GLE(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, data, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
    s_bind(was_bound);
}

void VertexBuffer::changeData(float* new_data, unsigned int offset, unsigned int size){

    if(offset + size >= length){
        ERR("You are trying to change data outside of the length of the buffer");
        return;
    }

    for(unsigned int i = offset; i < size + offset; i++)
       data[i] = new_data[offset - i];

    GLE(glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), size * sizeof(float), new_data));
}

void VertexBuffer::s_bind(unsigned int id){
    bound = id;
    GLE(glBindBuffer(GL_ARRAY_BUFFER, id));
}
