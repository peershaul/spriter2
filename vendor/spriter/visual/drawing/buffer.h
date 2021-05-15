#pragma once

#include <GL/glew.h>

template <typename T>
class Buffer{
    protected:
        GLuint id;
        GLenum type;

        Buffer(GLenum type){
            this->type = type;

            glGenBuffers(1, &this->id);
        }

    public:
        virtual void putData(T data[], bool dynamic);
        virtual void updateData(T data[]);

        void bind() { glBindBuffer(type, id); }
        void unbind() { glBindBuffer(type, NULL); }
};
