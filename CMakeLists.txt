cmake_minimum_required(VERSION 3.10)
project(px-hub-gui)

set(CMAKE_CXX_STANDARD 14)

######## QT-qmake settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5DBus REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets WebEngineWidgets)
########

include_directories(src)

add_executable(px-hub-gui
        src/main.cpp
        src/Logger.cpp src/Logger.h
        
        )

target_link_libraries(px-hub-gui Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngineWidgets px-gui-library)
install(TARGETS px-hub-gui DESTINATION bin)
install(FILES   desktop/px-hub-gui.desktop
                DESTINATION share/applications)