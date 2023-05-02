cmake_minimum_required(VERSION 3.0)

project(pnp-dice-roller)

add_executable(${PROJECT_NAME} src/main.cpp)

install(TARGETS pnp-dice-roller RUNTIME DESTINATION bin)
