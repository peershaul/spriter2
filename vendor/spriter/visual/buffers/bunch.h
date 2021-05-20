#pragma once

#include "index.h"
#include "vertex.h"

#include <vector>

class BufferBunch{
    private:
        VertexBuffer* vb;
        IndexBuffer* ib;
        std::vector<unsigned int> layout;

        BufferBunch(VertexBuffer* vb, IndexBuffer* ib, const std::vector<unsigned int>& layout);

        static std::vector<BufferBunch*> bunches;
        static unsigned int bound;
    public:
        static BufferBunch* gen(VertexBuffer* vb, IndexBuffer* ib, const std::vector<unsigned int>& layout);

        static void s_bind(unsigned int index);
        static void s_bind(BufferBunch* bunch) { s_bind(find(bunch)); }
        static void ubind();

        void bind(){ s_bind(this); }
        void unbind() { ubind(); }

        static std::vector<BufferBunch*> get_bunches(){
            std::vector<BufferBunch*> buffs = {};
            for(BufferBunch* buff : bunches)
                buffs.push_back(buff);
            return buffs;
        }

        static unsigned int find(const BufferBunch* bunch);
};
