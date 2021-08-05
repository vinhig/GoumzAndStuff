#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coord;

uniform vec2 pos;
uniform vec2 offset;
uniform float zoom;

uniform mat4 projection;

out vec2 o_tex_coord;

void main() {
  vec2 new_pos = position + pos;
  gl_Position = (projection * vec4(new_pos.x, 0.0, new_pos.y, 1.0)) + vec4(offset.x, offset.y, 0.0, 0.0);
  o_tex_coord = tex_coord;
}
