#include "vertex_buffer.h"

GLuint VertexBuffer::bound = 0;

VertexBuffer::VertexBuffer(){
    glGenBuffers(1, &id);
}

void VertexBuffer::putData(float* data, unsigned int length, bool dynamic){
    this->data = data;
    this->length = length;

    GLuint was_bound = VertexBuffer::get_bound();
    this->bind();

    glBufferData(GL_ARRAY_BUFFER, length, data, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    VertexBuffer::s_bind(was_bound);
}

void VertexBuffer::s_bind(GLuint id){
    bound = id;
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::ubind(){
    bound = 0;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
