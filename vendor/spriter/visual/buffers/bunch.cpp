#include "bunch.h"

#include "../../utils/logger.h"
#include "../../utils/error.h"

#include <GL/glew.h>

unsigned int BufferBunch::bound = 0;
std::vector<BufferBunch*> BufferBunch::bunches = {nullptr};

BufferBunch::BufferBunch(VertexBuffer* vb, IndexBuffer* ib, const std::vector<unsigned int>& layout){
    this->vb = vb;
    this->ib = ib;
    this->layout = layout;
}


BufferBunch* BufferBunch::gen(VertexBuffer* vb, IndexBuffer* ib, const std::vector<unsigned int>& layout){
    BufferBunch* buff = new BufferBunch(vb, ib, layout);
    unsigned int found = find(buff);

    if(found == 0){
        bunches.push_back(buff);
        return buff;
    }

    INFO("bunch is already in use");
    delete buff;
    return bunches[found];
}

unsigned int BufferBunch::find(const BufferBunch* bunch){
    for(unsigned int i = 1; i < bunches.size(); i++){
        if((bunches[i]->vb->get_id() == bunch->vb->get_id()) &&
           bunches[i]->ib->get_id() == bunch->ib->get_id())
            return i;
    }
    return 0;
}

void BufferBunch::ubind(){
    IndexBuffer::ubind();
    VertexBuffer::ubind();
    if(bound == 0) return;

    for(unsigned int i = 0; i < bunches[bound]->layout.size(); i++){
        GLE(glDisableVertexAttribArray(i));
    }
    bound = 0;
}

void BufferBunch::s_bind(unsigned int index){
    if(bound == index) return;
    ubind();

    bound = index;
    BufferBunch* bff = bunches[index];

    bff->vb->bind();
    bff->ib->bind();

    unsigned int stride = 0;
    for(unsigned int s : bff->layout) stride += s;

    unsigned int ptr = 0;
    for(unsigned int i = 0; i < bff->layout.size(); i++){
        GLE(glEnableVertexAttribArray(i));
        GLE(glVertexAttribPointer(i, bff->layout[i], GL_FLOAT, GL_FALSE,
                                  stride * sizeof(float), ((const void*) (ptr * sizeof(float)))));
        ptr += bff->layout[i];
    }
}
