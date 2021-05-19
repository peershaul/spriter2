#type vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 a_color;

out vec4 f_color;

void main(){
    gl_Position = vec4(position, 0, 1);
    f_color = a_color;
}

#type fragment

#version 330 core

in vec4 f_color;

out vec4 color;

void main(){
    color = f_color;
}
