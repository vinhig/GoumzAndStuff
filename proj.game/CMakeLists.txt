cmake_minimum_required(VERSION 3.10.2)
project("goumzandstuffgame")

add_library(GoumzAndStuffGame SHARED
  src/Game.cpp
  src/Log.cpp
  src/Font.cpp
  src/Text.cpp
  src/Math.cpp
  src/OpenGLUtils.cpp
  src/World.cpp
  libs/stb/stb_image.c)

add_subdirectory(libs/freetype)

find_library(log-lib log)

target_link_libraries(GoumzAndStuffGame ${log-lib} -lGLESv3 -landroid freetype)

target_include_directories(GoumzAndStuffGame PUBLIC libs/freetype/include)
target_include_directories(GoumzAndStuffGame PUBLIC libs)
target_include_directories(GoumzAndStuffGame PUBLIC libs/glm)
