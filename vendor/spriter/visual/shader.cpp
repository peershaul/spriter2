#include "shader.h"

#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include "../utils/logger.h"
#include "../utils/error.h"

unsigned int Shader::bound = 0;

Shader::Shader(const std::string& path){
    this->path = path;
    INFO("Shader path: \"%s\"", path.c_str());

    std::string contents = "", line;
    std::ifstream file_stream(path);

    if(!file_stream) ERR("Cannot open file \"%s\"", path.c_str());
    else{

        ShaderType type = ShaderType::NONE;

        while(std::getline(file_stream, line)){
            if(line.find("#type") != std::string::npos){
                if(line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
                else type = ShaderType::FRAGMENT;
            }
            else if(type != ShaderType::NONE)
                shaders[type] << line << std::endl;
        }

        //std::cout << "VERTEX\n\n" << shaders[ShaderType::VERTEX].str();
        //std::cout << "FRAGMENT\n\n" << shaders[ShaderType::FRAGMENT].str();
    }

    compile();
}


void Shader::compile(){
    compile_shaders();

    gle::clear();
    id = glCreateProgram();
    gle::check();

    for(int i = 0; i < 2; i++){
        GLE(glAttachShader(id, shader_ids[i]));
    }

    GLE(glLinkProgram(id));

    int compiled;
    GLE(glGetProgramiv(id, GL_LINK_STATUS, &compiled));
    if(compiled != GL_TRUE){
        int log_length;
        char message[4096];
        GLE(glGetShaderInfoLog(id, 4096, &log_length, message));
        ERR("Failed to link the program \"%s\" error is:\n%s", path.c_str(), message);
    }
}



void Shader::compile_shaders(){
    const GLenum types[2] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

    for(int i = 0; i < 2; i++){
        gle::clear();
        shader_ids[i] = glCreateShader(types[i]);
        gle::check();

        std::string str = shaders[i].str();
        const char* src = str.c_str();
        GLE(glShaderSource(shader_ids[i], 1, &src, NULL));
        GLE(glCompileShader(shader_ids[i]));

        int compiled;
        GLE(glGetShaderiv(shader_ids[i], GL_COMPILE_STATUS, &compiled));
        if(compiled != GL_TRUE){
            int log_length;
            char message[4096];
            GLE(glGetShaderInfoLog(shader_ids[i], 4096, &log_length, message));
            ERR("Failed to compile the %s shader in the program \"%s\" The error is:\n%s",
                ((i == 0)? "vertex" : "fragment"), path.c_str(), message);
        }
    }
}

void Shader::s_bind(unsigned int id){
    bound = id;
    GLE(glUseProgram(id));
}
