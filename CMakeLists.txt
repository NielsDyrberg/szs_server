cmake_minimum_required(VERSION 3.16) # CMake version check
project(soundzone_server_lib VERSION 0.0.4) # Create project "soundzone_server"
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# configure a header file to pass the version number only
configure_file(soundzone_server_config.h.in soundzone_server_config.h)

##########################################################################################
##################################  Make library  ########################################
##########################################################################################

#Generate the static library from the library sources
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_sources(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/szs_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sync_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/szp_handler.cpp
        )

##########################################################################################
################################   Find BCM2835   ########################################
##########################################################################################

# This finds the asound library
find_library(mybcm2835 bcm2835)
if(${mybcm2835})
    message(FATAL_ERROR "bcm2835 lib not found")
else()
    message(STATUS "bcm2835 lib found as ${mybcm2835}")
endif()

##########################################################################################
################################   Find pthread   ########################################
##########################################################################################

# This finds the pthread library
find_library(mypthreadlib pthread)
if(${mypthreadlib})
    message(FATAL_ERROR "pthread lib not found")
else()
    message(STATUS "pthread lib found as ${mypthreadlib}")
endif()

##########################################################################################
###########################   Add subdirectories   #######################################
##########################################################################################

# Externale libaries
add_subdirectory(extern)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} INTERFACE ${mybcm2835} ${mypthreadlib} szs_soundzone_protocol szs_time_sync)

##########################################################################################
########################   Make excecutable project   ####################################
##########################################################################################

# Add main.cpp file of project root directory as source file
set(soundzone_server main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(soundzone_server ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Link libraries to project
target_link_libraries(soundzone_server soundzone_server_lib)

##########################################################################################
##################################  Add tests  ###########################################
##########################################################################################

# Tests concerning szs client
add_subdirectory(tests)