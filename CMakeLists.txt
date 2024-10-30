cmake_minimum_required(VERSION 3.15.0)

project(Pong)

add_executable(${PROJECT_NAME}  main.cpp 
                                Ball.cpp
                                Bot.cpp
                                Figure.cpp
                                GameState.cpp
                                MenuState.cpp
                                Multiplayer.cpp
                                ScoreState.cpp
                                Singleplayer.cpp
                                State.cpp
                                StateMachine.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY figures/ DESTINATION bin/figures/)