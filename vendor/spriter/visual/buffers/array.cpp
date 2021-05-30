#include "array.h"

#include "../../utils/error.h"

#include <GL/glew.h>

unsigned int VertexArray::bound = 0;

VertexArray::VertexArray(VertexBuffer* vb, IndexBuffer* ib, std::vector<unsigned int> layout){

    this->ib = ib;
    this->vb = vb;
    this->layout = {};

    unsigned int stride = 0;

    for(unsigned int n : layout){
        this->layout.push_back(n);
        stride += n;
    }

    unsigned int was_bound = get_bound();

    GLE(glGenVertexArrays(1, &id));
    bind();
    vb->bind();
    ib->bind();

    unsigned int ptr = 0;

    for(unsigned int i = 0; i < layout.size(); i++){
        GLE(glEnableVertexAttribArray(i));
        GLE(glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride * sizeof(float),
                                  (const void*) (ptr * sizeof(float))));
        ptr += layout[i];
    }

    s_bind(was_bound);
}


void VertexArray::s_bind(unsigned int id){
    bound = id;
    GLE(glBindVertexArray(id));
}
