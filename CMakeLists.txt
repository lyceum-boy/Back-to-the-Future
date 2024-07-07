cmake_minimum_required(VERSION 3.25)
project(ITIP_CPP_PR_5_HDL)

set(CMAKE_CXX_STANDARD 17)

add_executable(ITIP_CPP_PR_5_HDL main.cpp
        MainWindow.cpp MainWindow.h
        MainMenu.cpp MainMenu.h
        GameOverScreen.cpp GameOverScreen.h VictoryScreen.cpp VictoryScreen.h EndScreen.h
        DeLorean.cpp DeLorean.h
        ClockFace.cpp ClockFace.h
        Thundercloud.cpp Thundercloud.h
        Explosion.cpp Explosion.h FireTrace.cpp FireTrace.h Lightning.cpp Lightning.h Animation.h)

# set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.0/lib/cmake/SFML)

include_directories(C:/SFML-2.6.0/include)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(ITIP_CPP_PR_5_HDL PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(SFML COMPONENTS audio CONFIG REQUIRED)
target_link_libraries(ITIP_CPP_PR_5_HDL PRIVATE sfml-audio)
