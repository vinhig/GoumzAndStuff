#version 300 es

precision mediump float;

layout(location = 0) out vec4 o_color;

in vec2 o_tex_coord;

uniform sampler2D face_texture;

void main() {
  o_color = texture(face_texture, vec2(o_tex_coord.x, 1.0 - o_tex_coord.y));
}
