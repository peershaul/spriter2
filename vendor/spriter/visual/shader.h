#pragma once

#include <string>
#include <sstream>

class Shader{
    private:
        unsigned int id;
        std::string path;
        std::stringstream shaders[2];
        unsigned int shader_ids[2];

        static unsigned int bound;

        enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

        void compile();
        void compile_shaders();
    public:
        Shader(const std::string& path);
        void bind() { s_bind(id); }
        void unbind() { ubind(); }

        static void s_bind(unsigned int id);
        static void s_bind(Shader* shader) { s_bind(shader->id); }
        static void ubind() { s_bind((int) 0); }

        static unsigned int get_bound() { return bound; }
};
