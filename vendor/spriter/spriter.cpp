#include "spriter.h"
#include "utils/logger.h"
#include "utils/error.h"
#include "visual/display.h"
#include "visual/shader.h"
#include "visual/buffers/vertex.h"
#include "visual/buffers/index.h"
#include "visual/buffers/bunch.h"

#include <GL/glew.h>
#include <vector>

namespace spriter{

    static Display* dis;
    static const unsigned int positions_length = 15,
        indices_length = 3;

    static float positions[positions_length] = {
    // Position      Color
    -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
     0.0f,  0.5f,   0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,   0.0f, 0.0f, 1.0f
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

        IndexBuffer* ib = new IndexBuffer();
        ib->putData(indices, indices_length);
        ib->bind();

        std::vector<unsigned int> layout = { 2 };

        GLE(glEnableVertexAttribArray(0));
        GLE(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0));
        GLE(glEnableVertexAttribArray(1));
        GLE(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) (2 * sizeof(float)) ));

        Shader* shader = new Shader("resources/shaders/basic.glsl");
        shader->bind();

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
