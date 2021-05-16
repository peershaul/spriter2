#include "bunch.h"

#include "../../utils/logger.h"
#include "../../utils/error.h"

#include "GL/glew.h"

unsigned int BufferBunch::bound = 0;
std::vector<BufferBunch*> BufferBunch::bunches = { nullptr };

BufferBunch::BufferBunch(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int>& layout){
    this->vb = vb;
    this->ib = ib;
    this->layout = layout;
}


BufferBunch* BufferBunch::gen(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int>& layout){
    BufferBunch* buff = new BufferBunch(vb, ib, layout);
    unsigned int found = find(buff);

    if(found == 0) {
        BufferBunch::bunches.push_back(buff);
        return buff;
    }

    INFO("BufferBunch already exist");
    return BufferBunch::bunches[found];
}

unsigned int BufferBunch::find(BufferBunch* buff){
    unsigned int found = 0;

    for(unsigned int i = 1; i < BufferBunch::bunches.size(); i++){
        if(&BufferBunch::bunches[i] == &buff){
            found = i;
            break;
        }
    }

    return found;
}

bool BufferBunch::operator==(const BufferBunch& buff){
    return ib == buff.ib && vb == buff.vb;
}

void BufferBunch::s_bind(unsigned int index){
    if(index >= BufferBunch::bunches.size()){
        ERR("you are trying to bind out of bounds buffer bunch");
        return;
    }

    s_bind(BufferBunch::bunches[index]);
}

void BufferBunch::s_bind(BufferBunch* buff){
    unsigned int was_bound = bound;
    bound = find(buff);

    if(bound != 0){
        buff->ib->bind();
        buff->vb->bind();

        unsigned int stride = 0;
        for(unsigned int i = 0; i < buff->layout.size(); i++)
            stride += buff->layout[i];

        unsigned int offset = 0;
        for(unsigned int i = 0; i < buff->layout.size(); i++){
            GLE(glEnableVertexAttribArray(i));
            GLE(glVertexAttribPointer(i, buff->layout[i], GL_FLOAT, GL_FALSE,
                              stride * sizeof(float), (const void*) (offset * sizeof(float))));
            offset += buff->layout[i];
        }
    }


    else if (was_bound != 0) {
        BufferBunch* buff = BufferBunch::bunches[was_bound];
        buff->vb->unbind();
        buff->ib->unbind();

        for(unsigned int i = 0; i < buff->layout.size(); i++){
            GLE(glDisableVertexAttribArray(i));
        }
    }
}
