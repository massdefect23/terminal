cmake_minimum_required(VERSION 3.15)
project(terminal VERSION 1.0.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ----------------------------------------------------------------------------
# Set output directories for different build types (Debug, Release, etc.)
# ----------------------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/debug/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/debug/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/debug/bin")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/release/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/release/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/release/bin")

# Find ncurses
find_package(Curses REQUIRED)
include_directories(
    ${CURSES_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Create the executable
add_executable(terminal
    src/main.cpp
    src/App.cpp
    src/MainScreen.cpp
    src/SplashScreen.cpp
)

target_link_libraries(terminal PRIVATE ${CURSES_LIBRARIES})

#-----------------------------------------------------
# Installation: This will let us do `make install`
#-----------------------------------------------------
install(
    TARGETS terminal
    RUNTIME DESTINATION bin
)

#-----------------------------------------------------
# Optional Packaging with CPack to build a .dmg on macOS
#-----------------------------------------------------
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "terminal")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_GENERATOR "DragNDrop")  # Creates a .dmg on macOS
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-MacOS")

include(CPack)