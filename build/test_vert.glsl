#version 330 core

in vec2 pos;

out vec2 uv;

void main() {
     gl_Position = vec4(pos, 0.0, 1.0);

     uv = pos;
}