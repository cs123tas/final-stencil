#version 400 core

uniform mat4 view;
uniform mat4 projection;
uniform float scale;

layout (location = 0) in vec3 position;

out vec3 pos_object;

void main() {
     pos_object = normalize(vec3(-position.x, -position.y, position.z));
     gl_Position = projection * view * vec4(position * scale, 1);
}
