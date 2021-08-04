BUILDING.name = "Coal Extractor"
BUILDING.description = "Extracts coal from the ground. Infinite supply."
BUILDING.author = "Vincent"
BUILDING.size_x = 1
BUILDING.size_y = 1


function BUILDING:onCreate(x, y)
  world = GoumzAndStuff.get_game():get_world()

  world:set_tile(x + 1, y + 1, GoumzAndStuff.DIRT)
  world:set_tile(x, y + 1, GoumzAndStuff.DIRT)
  world:set_tile(x + 1, y, GoumzAndStuff.DIRT)
  world:set_tile(x - 1, y - 1, GoumzAndStuff.DIRT)
  world:set_tile(x , y - 1, GoumzAndStuff.DIRT)
  world:set_tile(x - 1, y, GoumzAndStuff.DIRT)
end