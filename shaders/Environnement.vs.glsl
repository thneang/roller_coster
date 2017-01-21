#version 330

layout(location = 0) in vec2 aVertexPosition;

out vec3 vColor;

void main() {
    vColor = vec3(255,255,255);
    gl_Position = vec4(aVertexPosition, 0, 1);
}
