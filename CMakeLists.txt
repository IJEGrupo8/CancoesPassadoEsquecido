cmake_minimum_required(VERSION 2.8.0)

PROJECT(cancoes)

# Set directory folders
set (PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/src")
set (PROJECT_ASSETS_DIR  "${PROJECT_SOURCE_DIR}/assets")

# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES "${PROJECT_SRC_DIR}/*.cpp"
                          "${PROJECT_SRC_DIR}/*.c")

# Include Headers
include_directories("${PROJECT_INCLUDE_DIR}")



#### Compilation ####

# Compilation Flags
set(COMPILE_FLAGS "")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -std=c++11 -Wshadow -O2 -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -std=c++11 -Wshadow -O2 -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} /Wall")
endif()

# Cmake compilation flags redefinition
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")



#### Dependencies ####

# Add engine
set (PROJECT_ENGINE_DIR "${PROJECT_SOURCE_DIR}/engine")
add_subdirectory(${PROJECT_ENGINE_DIR})
include_directories(${ENGINE_INCLUDE_DIR})



#### Executable ####

add_executable(cancoes ${SOURCES})

target_link_libraries(cancoes
                      engine
                      SDL2 SDL2_image SDL2_ttf SDL2_mixer)



#### Custom Commands ####

# Copy assets folder to build
add_custom_command(TARGET cancoes POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets)

INSTALL(TARGETS cancoes DESTINATION "/bin")
INSTALL(DIRECTORY assets DESTINATION "/opt/cancoes")

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Igor Duarte")
SET(CPACK_PACKAGE_VENDOR "Igor Duarte")
SET(CPACK_GENERATOR "DEB")

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

SET(CPACK_PACKAGE_DESCRIPTION "Canções de um Passado Esquecido")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Uma garota possui um instrumento que quando tocado provoca reações nas pessoas, encantando-as, irritando-as, dentre outros. Ela perde a memória em um conflito na vila em que ela mora, quando tentam roubar seu instrumento a fim de obterem seus poderes. Ela acorda perdida e se lembra somente de uma canção.")

SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-dev, libsdl2-image-2.0-0, libsdl2-image-dev, libsdl2-mixer-2.0-0, libsdl2-mixer-dev, libsdl2-ttf-2.0-0, libsdl2-ttf-dev")

INCLUDE(CPack)
