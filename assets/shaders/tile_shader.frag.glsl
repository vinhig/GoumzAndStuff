
#version 300 es

layout(location = 0) out vec4 o_color;

in vec2 o_tex_coord;

layout(binding = 0) uniform sampler2D face_texture;

void main() {
  o_color = texture(face_texture, vec2(o_tex_coord.x, 1.0 - o_tex_coord.y));
}
//