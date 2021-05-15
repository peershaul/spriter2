#include "spriter.h"
#include "utils/logger.h"
#include "visual/display.h"
#include "visual/drawing/vertex_buffer.h"
#include "visual/drawing/index_buffer.h"

#include <glm/glm.hpp>

namespace spriter{

    static Display* dis;
    static VertexBuffer* vb;
    static IndexBuffer* ib;

    bool init(){
        INFO("Hello world from the spriter engine");

        dis = new Display(800, 600, "Hello world");
        dis->changeClearColor(glm::vec4(0.3f, 0.7f, 0.9f, 1.0f));

        vb = new VertexBuffer();
        ib = new IndexBuffer();

        float positions[8] = {
        -0.5f,  0.5f, // top left
         0.5f,  0.5f, // top right
        -0.5f, -0.5f, // bottom left
         0.5f, -0.5f  // bottom right
    };

        unsigned int indices[] = {

    };

        loop();

        return true;
    }

    void loop(){
        while(!dis->isClosed()){
            dis->clear();
            dis->update();
        }
    }
}
