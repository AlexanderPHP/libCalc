cmake_minimum_required(VERSION 3.5)
project(FileManager)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c11 -O0 -g")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")
set(SOURCE_FILES src/main.c src/tui.c src/files.c src/event.c src/event.h)
add_executable(FileManager ${SOURCE_FILES})

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (FileManager ${CURSES_LIBRARIES} menu panel)
endif()