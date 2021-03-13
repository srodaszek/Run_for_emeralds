cmake_minimum_required(VERSION 3.10)

project(Run_For_Emeralds VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SFML_DIR "SFML/lib/cmake/SFML")
#include_directiories(${CMAKE_CURRENT_SOURCE_DIR}/include )
set(SOURCES main.cpp include/Confuse_Trap.cpp include/Fake_Trap.cpp include/Game_Graphic.cpp include/Game_Logic.cpp include/Main_Menu.cpp include/Player.cpp include/Stone.cpp include/Tar_Trap.cpp include/Teleport_Trap.cpp include/Trap.cpp)

find_package(SFML COMPONENTS system graphics audio network REQUIRED)
add_executable (Run_For_Emeralds "main.cpp" "include/Confuse_Trap.cpp" "include/Fake_Trap.cpp" "include/Game_Graphic.cpp" "include/Game_Logic.cpp" "include/Main_Menu.cpp" "include/Player.cpp" "include/Stone.cpp" "include/Tar_Trap.cpp" "include/Teleport_Trap.cpp" "include/Trap.cpp")
target_link_libraries(Run_For_Emeralds PRIVATE sfml-audio sfml-graphics sfml-network sfml-system)

