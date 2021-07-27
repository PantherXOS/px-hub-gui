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

find_package(yaml-cpp)
find_package(CapnProto CONFIG REQUIRED)
set(INTERFACE_DIR interfaces)
set(CAPNPC_SRC_PREFIX "${INTERFACE_DIR}" CACHE STRING "" FORCE)
set(CAPNPC_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/interfaces" CACHE STRING "" FORCE)
message(${CAPNPC_OUTPUT_DIR})
file(MAKE_DIRECTORY "${CAPNPC_OUTPUT_DIR}")
capnp_generate_cpp(CapnpSources CapnpHeaders        
        ${INTERFACE_DIR}/hub.capnp
        )


include_directories(src
        ${CapnProto_INCLUDE_DIRS}        
        ${CAPNPC_OUTPUT_DIR})



add_executable(px-hub-gui
        src/main.cpp
        src/Logger.cpp                  src/Logger.h
        src/AccountParser.cpp           src/AccountParser.h
        src/MainWindow.cpp              src/MainWindow.h
        src/MessageObject.h             src/AccountObject.h
        src/RPCHubClient.cpp            src/RPCHubClient.h
        src/AccountUtils.cpp            src/AccountUtils.h 
        src/AccountsMessageList.cpp     src/AccountsMessageList.h 
        src/AccountsMessageListItem.h   src/Settings.h
        ${CapnpSources} ${CapnpHeaders}      
        )

target_link_libraries(px-hub-gui Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngineWidgets px-gui-library CapnProto::capnp-rpc yaml-cpp)
install(TARGETS px-hub-gui DESTINATION bin)
install(FILES   desktop/px-hub-gui.desktop
                DESTINATION share/applications)