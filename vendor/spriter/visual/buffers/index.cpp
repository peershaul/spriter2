#include "index.h"
#include "../../utils/error.h"
#include "../../utils/logger.h"

#include <GL/glew.h>


unsigned int IndexBuffer::bound = 0;

IndexBuffer::IndexBuffer(){
    GLE(glGenBuffers(1, &id));
}

void IndexBuffer::putData(unsigned int* data, unsigned int length){
    this->data = data;
    this->length = length;

    unsigned int was_bound = get_bound();
    bind();

    GLE(glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), data, GL_STATIC_DRAW));
    s_bind(was_bound);
}

void IndexBuffer::s_bind(unsigned int id){
    bound = id;
    GLE(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}
