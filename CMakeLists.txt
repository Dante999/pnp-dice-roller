cmake_minimum_required(VERSION 3.0)

project(pnp-dice-roller CXX)


add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/dice.cpp
    src/roll_instructions.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS pnp-dice-roller RUNTIME DESTINATION bin)
