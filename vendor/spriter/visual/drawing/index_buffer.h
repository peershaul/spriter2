#pragma once

#include <GL/glew.h>

class IndexBuffer{
    private:
        GLuint id;
        unsigned int* data;
        unsigned int length;
        static GLuint bound;

    public:
        IndexBuffer();

        void putData(unsigned int* data, unsigned int length);
        void bind();

        static void s_bind(GLuint id);
        static void s_bind(IndexBuffer* ib);
        static void ubind();

        static GLuint get_bound(){ return bound; }
};
