#include "index_buffer.h"

GLuint IndexBuffer::bound = 0;

void IndexBuffer::s_bind(const GLuint id){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    bound = id;
}

void IndexBuffer::s_bind(IndexBuffer* ib){
    s_bind(ib->id);
}

void IndexBuffer::ubind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    bound = 0;
}

IndexBuffer::IndexBuffer(){
    glGenBuffers(1, &id);
}

void IndexBuffer::putData(unsigned int* data, unsigned int length, bool dynamic){
    this->data = data;
    this->length = length;

    GLuint last_bound = IndexBuffer::get_bound();
    this->bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, data, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    IndexBuffer::s_bind(last_bound);
}

void IndexBuffer::bind(){
    s_bind(this);
}
