#pragma once

#include "index.h"
#include "vertex.h"

#include <vector>

class BufferBunch{
    private:
        static std::vector<BufferBunch*> bunches;
        static unsigned int bound;

        BufferBunch(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int>& layout);
        VertexBuffer* vb;
        IndexBuffer* ib;
        std::vector<unsigned int> layout;

        static unsigned int find(BufferBunch* buff);

    public:
        static BufferBunch* gen(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int>& layout);
        bool operator==(const BufferBunch& buff);

        void bind() { s_bind(this); }
        void unbind() { ubind(); }

        static void s_bind(BufferBunch* buff);
        static void s_bind(unsigned int index);
        static void ubind(){ s_bind(nullptr); }

};
