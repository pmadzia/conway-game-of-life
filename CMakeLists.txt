cmake_minimum_required(VERSION 3.11.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(game
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    )

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)


# add warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(game PRIVATE
        -Wall               # All standard warnings
        -Wextra             # Extra warnings
        -Wpedantic          # Strict ISO compliance
        -Wuninitialized     # Warn on uninitialized variables
        -Wunused-variable   # Warn about unused variables
        -Wshadow            # Warn about shadowing
    )
endif()
