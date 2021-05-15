#pragma once

#include <GL/glew.h>

class VertexBuffer{
    private:
        GLuint id;
        float* data;
        unsigned int length;
        static GLuint bound;
    public:
        VertexBuffer();

        void putData(float* data, unsigned int length, bool dynamic);
        void bind() { VertexBuffer::s_bind(this); }

        static void s_bind(GLuint id);
        static void s_bind(VertexBuffer* vb) { s_bind(vb->id); }
        static void ubind();

        static GLuint get_bound() { return bound; }
};
