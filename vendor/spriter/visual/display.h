#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

class Display{
    public:
        Display(int width, int height, const std::string& title);

        void update();
        void clear();
        bool isClosed() { return is_closed; }
        virtual ~Display();
        void changeClearColor(const glm::vec4& color);
        void changeClearColor(float r, float g, float b, float a){
                changeClearColor(glm::vec4(r, g, b, a));
        }

    private:
        Display(const Display& other){}
        void operator=(const Display& other){}

        glm::vec4 clear_color;
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool is_closed;
};
