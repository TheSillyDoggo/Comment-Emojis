cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${GEODE_TARGET_PLATFORM}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
	set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)


project(CommentEmojis VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/EmojiLoader.cpp
    src/CCLabelBMFontExt.cpp
    src/TextAreaExt.cpp
    src/CCProxyNode.cpp
    src/EmojiPickPopup.cpp
    src/Hooks/GlobedChatCell.cpp
    src/Hooks/GlobedChatListPopup.cpp
    src/Hooks/CommentCell.cpp
    src/Hooks/ShareCommentLayer.cpp
    src/EmojiNode.cpp
    # Add your cpp files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
