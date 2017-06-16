cmake_minimum_required(VERSION 3.7)
project(county)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/CE/Core/Act.cpp
        include/CE/Core/Act.hpp
        src/CE/Core/AbstractNode.cpp
        include/CE/Core/AbstractNode.hpp
        src/CE/Core/AbstractVisualNode.cpp
        include/CE/Core/AbstractVisualNode.hpp
        src/CE/Core/CircleNode.cpp
        include/CE/Core/CircleNode.hpp
        src/CE/Core/MimicNode.cpp
        include/CE/Core/MimicNode.hpp
        src/CE/Core/RectangleNode.cpp
        include/CE/Core/RectangleNode.hpp
        src/CE/Core/RootNode.cpp
        include/CE/Core/RootNode.hpp
        src/CE/Core/SpriteNode.cpp
        include/CE/Core/SpriteNode.hpp
        src/CE/Core/Stage.cpp
        include/CE/Core/Stage.hpp
        include/CE/Event/Listener.hpp
        src/CE/Event/Speaker.cpp
        include/CE/Event/Speaker.hpp
        src/CE/UI/Button.cpp
        include/CE/UI/Button.hpp
        src/CE/UI/Parameters.cpp
        include/CE/UI/Parameters.hpp
        src/CE/UI/ProgressBar.cpp
        include/CE/UI/ProgressBar.hpp
        src/CE/UI/Text.cpp
        include/CE/UI/Text.hpp
        include/CE/constant.hpp)

add_library(county STATIC ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(county ${SFML_LIBRARIES})
endif()
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)