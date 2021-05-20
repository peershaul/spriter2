#pragma once

#include "../../utils/logger.h"

class IndexBuffer{
    private:
        unsigned int id, length;
        unsigned int* data;
        static unsigned int bound;
    public:
        IndexBuffer();

        void putData(unsigned int* data, unsigned int length);

        void bind() { s_bind(this); }
        void unbind() { ubind(); }

        unsigned int get_id() { return id; }

        static void s_bind(unsigned int id);
        static void s_bind(IndexBuffer* ib) { s_bind(ib->id); }
        static void ubind() { s_bind( (unsigned int) 0  ); }

        static unsigned int get_bound(){ return bound; }

};
