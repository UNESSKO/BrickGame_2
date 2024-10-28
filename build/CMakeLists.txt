cmake_minimum_required(VERSION 3.22)
project(CPP3_BrickGame_v2_0_1)

# Укажите версию Qt и необходимые компоненты
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Установите стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая обработка moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

## Включите папки с заголовочными файлами
#include_directories(../brick_game/snake/include)
#include_directories(../brick_game/tetris)
#include_directories(../gui/cli)
#include_directories(../gui/desktop)

add_executable(CPP3_BrickGame_v2_0_1
        ../brick_game/controller/Controller.h
        ../brick_game/controller/Controller.cpp
        ../brick_game/snake/include/Snake.h
        ../brick_game/snake/sourses/Snake.cpp
        ../brick_game/snake/include/SnakeModel.h
        ../brick_game/snake/sourses/SnakeModel.cpp
        #        ../brick_game/snake/tests/SnakeTests.cpp
        #        ../brick_game/snake/tests/tests.cpp
        #        ../brick_game/snake/tests/tests.h
        ../components/game_selection/GameSelection.h
        ../components/game_selection/GameSelection.cpp
        ../components/gui_templates/desktop/DesktopViewTemplate.cpp
        ../components/gui_templates/desktop/DesktopViewTemplate.h
        ../components/gui_templates/cli/ConsoleViewTemplate.h
        ../components/gui_templates/cli/ConsoleViewTemplate.cpp
        ../components/interfaces/IModel.h
        ../components/interfaces/IView.h
        ../components/GameInfo.h
        ../gui/desktop/DesktopView.cpp
        ../gui/desktop/DesktopView.h
        ../brick_game/tetris/model/TetrisModel.cpp
        ../brick_game/tetris/model/TetrisModel.h
        ../brick_game/tetris/include/tetris.h
        ../brick_game/tetris/sourses/tetris.c
        ../gui/cli/CLI.h
        ../gui/cli/CLI.c
        ../main.cpp
)

# Линкуйте проект с Qt
target_link_libraries(CPP3_BrickGame_v2_0_1
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        -lstdc++
        -lncursesw
)
