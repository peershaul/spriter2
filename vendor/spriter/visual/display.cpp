#include "display.h"
#include <GL/glew.h>

#include "../utils/logger.h"


Display::Display(int width, int height, const std::string& title){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();
    if(status != GLEW_OK){ ERR("GLEW failed to initialize"); return; }

    is_closed = false;
    INFO("Spriter window was created!");
}

Display::~Display(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::changeClearColor(const glm::vec4& color){
    this->clear_color = glm::vec4(color);
    glClearColor(color.x, color.y, color.z, color.z);
}

void Display::update(){
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    while(SDL_PollEvent(&e)) if(e.type == SDL_QUIT) is_closed = true;
}
