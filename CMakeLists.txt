cmake_minimum_required(VERSION 3.25)
project(ITIP_CPP_PR_5_HDL)

set(CMAKE_CXX_STANDARD 17)

add_executable(ITIP_CPP_PR_5_HDL main.cpp MainWindow.cpp MainWindow.h DeLorean.cpp DeLorean.h LightningAnimation.cpp LightningAnimation.h MainMenu.cpp MainMenu.h Explosion.cpp Explosion.h)

set(SFML_DIR C:/SFML-2.6.0/lib/cmake/SFML)

include_directories(C:/SFML-2.6.0/include)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(ITIP_CPP_PR_5_HDL PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(SFML COMPONENTS audio CONFIG REQUIRED)
target_link_libraries(ITIP_CPP_PR_5_HDL PRIVATE sfml-audio)
