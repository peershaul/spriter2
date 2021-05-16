#include "spriter.h"
#include "utils/logger.h"
#include "utils/error.h"
#include "visual/display.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace spriter{

    static Display* dis;
    static const unsigned int positions_length = 6,
        indices_length = 3;

    static float positions[positions_length] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
    -0.5f,  0.5f
};

    static unsigned int indices[indices_length] = {
        0, 2, 1,
    };


    bool init(){
        INFO("Hello world from the spriter engine");

        dis = new Display(800, 600, "Hello world");
        dis->changeClearColor(glm::vec4(0.3f, 0.7f, 0.9f, 1.0f));

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
