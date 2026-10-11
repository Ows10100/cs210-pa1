cmake_minimum_required(VERSION 4.3)
project(cs210_pa1_boilerplate)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cs210_pa1_boilerplate
        main.cpp
        Player.h
        Stack.h
        List.h
        Card.h
        ArrayList.h
        LinkedList.h
        Node.h)
