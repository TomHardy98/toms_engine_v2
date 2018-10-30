cmake_minimum_required(VERSION 2.6)
project(TOMSENGINE)

include_directories(
  src
  contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
	contrib/glm/include
	contrib/msvc-windows-x86/ogg/include
	contrib/msvc-windows-x86/openal-soft/include
	contrib/msvc-windows-x86/vorbis/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/ogg/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/vorbis/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(tomsengine
  src/tomsengine/Core.cpp
  src/tomsengine/Core.h
  src/tomsengine/Shader.cpp
  src/tomsengine/Shader.h
  src/tomsengine/Entity.cpp
  src/tomsengine/Entity.h
  src/tomsengine/Component.cpp
  src/tomsengine/Component.h
  src/tomsengine/VertexArray.cpp
  src/tomsengine/VertexArray.h
  src/tomsengine/VertexBuffer.cpp
  src/tomsengine/VertexBuffer.h
  src/tomsengine/MeshRenderer.cpp
  src/tomsengine/MeshRenderer.h
  src/tomsengine/Audio.cpp
  src/tomsengine/Audio.h
  src/tomsengine/Texture.cpp
  src/tomsengine/Texture.h
  contrib/stb_image/stb_image.cpp
  contrib/stb_image/stb_image.h
)

add_executable(game
  src/game/main.cpp
)

target_link_libraries(game tomsengine)

if(MSVC)
  target_link_libraries(tomsengine
    SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile
  )
else()
  target_link_libraries(tomsengine
    SDL2 GLU GLEW GL AL ogg vorbis vorbisfile
  )
endif()

if(MSVC)
  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:game>"
  )

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:game>"
  )

   add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:game>"
  )
endif()