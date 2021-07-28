#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coord;

uniform vec2 pos;

uniform mat4 projection;
uniform mat4 view;

out vec2 o_tex_coord;

void main() {
  gl_Position = projection * vec4(position + pos, 0.0, 1.0);
  o_tex_coord = tex_coord;
}
//