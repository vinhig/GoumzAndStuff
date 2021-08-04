cmake_minimum_required(VERSION 3.10.2)
project("goumzandstuffgame")

file(GLOB LUA_SRC_FILES "libs/lua/*.c")
list(REMOVE_ITEM LUA_SRC_FILES "${SRCDIR}/lua.c" "${SRCDIR}/luac.c")

add_library(lua STATIC
  ${LUA_SRC_FILES}
)

add_library(GoumzAndStuffGame SHARED
  "src/Game.cpp"
  "src/Log.cpp"
  "src/Font.cpp"
  "src/Text.cpp"
  "src/Math.cpp"
  "src/OpenGLUtils.cpp"
  "src/World.cpp"
  "src/Input.cpp"
  "swig/game_wrap.cxx"
  "libs/stb/stb_image.c")

add_subdirectory(libs/freetype)

find_library(log-lib log)

target_link_libraries(GoumzAndStuffGame ${log-lib} -lGLESv3 -landroid freetype lua)

target_include_directories(GoumzAndStuffGame PUBLIC src/)
target_include_directories(GoumzAndStuffGame PUBLIC libs/freetype/include)
target_include_directories(GoumzAndStuffGame PUBLIC libs)
target_include_directories(GoumzAndStuffGame PUBLIC libs/lua)
target_include_directories(GoumzAndStuffGame PUBLIC libs/glm)
