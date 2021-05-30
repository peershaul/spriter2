#pragma once

#include "index.h"
#include "vertex.h"

#include <vector>

class VertexArray{
    private:
        unsigned int id;
        const VertexBuffer* vb;
        const IndexBuffer* ib;
        std::vector<unsigned int> layout;

        static unsigned int bound;
    public:
        VertexArray(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int> layout);

        void bind() { s_bind(this); }
        void unbind() { ubind(); }

        static void s_bind(unsigned int id);
        static void s_bind(VertexArray* va){ s_bind(va->id); }
        static void ubind(){ s_bind((unsigned int) 0); }

        static unsigned int get_bound() { return bound; }
};
