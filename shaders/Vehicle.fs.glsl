#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform sampler2D uTextureKa;
uniform sampler2D uTextureKd;
uniform sampler2D uTextureKs;
uniform sampler2D uTextureNormal;


void main() {
    fFragColor = texture(uTexture, vTexCoords).xyz;
}
