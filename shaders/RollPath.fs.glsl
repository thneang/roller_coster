#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    fFragColor = vec3(0,255,0);
}
