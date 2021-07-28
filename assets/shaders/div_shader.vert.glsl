#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coord;

uniform vec2 pos;
uniform vec2 scale;

uniform mat4 projection;
uniform mat2 rotation;

out vec2 o_tex_coord;

void main() {
  // center of quad is currently at bottom left
  // we want it in the center of mass

  // apply scale
  vec2 tricked_pos = position * scale;

  // change interval of [0.0, 1.0] to [-0.5, 0.5]
  tricked_pos =
      vec2(tricked_pos.x - scale.x / 2.0, tricked_pos.y - scale.y / 2.0);

  // apply rotation
  tricked_pos = tricked_pos * rotation;

  // change the center *again* (with respect to scale)
  tricked_pos =
      vec2(tricked_pos.x + scale.x / 2.0, tricked_pos.y + scale.y / 2.0);

  // translate it
  tricked_pos += pos;

  gl_Position = projection * vec4(tricked_pos, 0.0, 1.0);
  o_tex_coord = tex_coord;
}
//