GoumzAndStuff.print("HELLO")

last_zoom = 1.0

game = GoumzAndStuff.get_game()
world = game:get_world()

last_x = 0.0
last_y = 0.0

function on_zoom(state, delta)

  if state == GoumzAndStuff.ZOOM_MIDDLE then
    last_zoom = math.max(0.45, math.min(2.20, last_zoom * delta))
    GoumzAndStuff.print("current zoom: " .. last_zoom)
    world:set_zoom(last_zoom)

    GoumzAndStuff.print("wanting to translate of " .. last_x / last_y * (1 - delta))
    GoumzAndStuff.print("wanting to translate of " .. last_y / last_x * (1 - delta))

    last_x = last_x + last_x / last_y * (1 - delta)
    last_y = last_y + last_y / last_x * (1 - delta)
  end

end

function on_drag(state, x, y)

  if state == GoumzAndStuff.DRAG_MIDDLE then
    last_x = last_x + x * 2.0
    last_y = last_y + y * 2.0
    GoumzAndStuff.print("current x: " .. last_x)
    GoumzAndStuff.print("current y: " .. last_y)
    world:set_position(last_x, last_y)
  end
  
end