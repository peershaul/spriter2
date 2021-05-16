#include "spriter.h"
#include "utils/logger.h"
#include "utils/error.h"
#include "visual/display.h"
#include "visual/buffers/vertex.h"

#include <GL/glew.h>

namespace spriter{

    static Display* dis;
    static const unsigned int positions_length = 6,
        indices_length = 3;

    static float positions[positions_length] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
};

    static unsigned int indices[indices_length] = {
        0, 2, 1,
    };


    bool init(){
        INFO("Hello world from the spriter engine");

        dis = new Display(800, 600, "Hello world");
        dis->changeClearColor(0.3f, 0.7f, 0.9f, 1.0f);

        VertexBuffer* vb = new VertexBuffer();
        vb->putData(positions, positions_length, false);
        vb->bind();

        unsigned int index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        loop();

        return true;
    }

    void loop(){
        while(!dis->isClosed()){
            dis->clear();

            GLE(glDrawElements(GL_TRIANGLES, indices_length, GL_UNSIGNED_INT, nullptr));

            dis->update();
        }
    }
}
