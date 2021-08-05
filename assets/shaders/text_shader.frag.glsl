#version 300 es

precision mediump float;

layout(location = 0) out vec4 o_color;

uniform vec4 color;

in vec2 o_tex_coord;

uniform sampler2D face_texture;

void main() {
  float c = texture(face_texture, o_tex_coord).r;
  o_color = color * vec4(1.0, 1.0, 1.0, c);
}
