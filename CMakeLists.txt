cmake_minimum_required(VERSION 3.7)
project(county)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules)

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

include_directories(include ${SFML_INCLUDE_DIR})

set(SOURCE_FILES
        src/CE/Core/Act.cpp
        include/CE/Core/Act.hpp
        src/CE/Core/Node.cpp
        include/CE/Core/Node.hpp
        src/CE/Core/VisualNode.cpp
        include/CE/Core/VisualNode.hpp
        src/CE/Core/CircleNode.cpp
        include/CE/Core/CircleNode.hpp
        src/CE/Core/MimicNode.cpp
        include/CE/Core/MimicNode.hpp
        src/CE/Core/RectangleNode.cpp
        include/CE/Core/RectangleNode.hpp
        src/CE/Core/SpriteNode.cpp
        include/CE/Core/SpriteNode.hpp
        src/CE/Core/Stage.cpp
        include/CE/Core/Stage.hpp
        include/CE/Event/Listener.hpp
        src/CE/Event/Speaker.cpp
        include/CE/Event/Speaker.hpp
        src/CE/UI/Button.cpp
        include/CE/UI/Button.hpp
        src/CE/UI/ProgressBar.cpp
        include/CE/UI/ProgressBar.hpp
        src/CE/UI/Text.cpp
        include/CE/UI/Text.hpp
        include/CE/constant.hpp
        src/CE/Core/TransformableNode.cpp
        include/CE/Core/TransformableNode.hpp
        include/CE/Utility/StdEnableSharedFromThisWrapper.hpp
        include/CE/Utility/EnableSharedFromThis.hpp)
add_library(county STATIC ${SOURCE_FILES})

target_link_libraries(county ${SFML_LIBRARIES})