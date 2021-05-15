#include "spriter.h"
#include "utils/logger.h"
#include "visual/display.h"

#include <glm/glm.hpp>

namespace spriter{
    bool init(){
        INFO("Hello world from the spriter engine");

        Display dis(800, 600, "Hello world from spriter");
        dis.changeClearColor(glm::vec4(0.3f, 0.7f, 0.9f, 1.0f));
        while(!dis.isClosed()){
            dis.clear();
            dis.update();
        }

        return true;
    }
}
