
############################################################
# Initial defs
############################################################
cmake_minimum_required(VERSION 3.16) # CMake version check
project(szs_datatransport VERSION 0.1.4) # Create project "szs_datastransport"

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(szs_datatransport INTERFACE)

target_include_directories(szs_datatransport INTERFACE
        include
        )

target_sources(szs_datatransport INTERFACE
        src/dataTransport.cpp
        src/udp_client.cpp
        src/udp_server.cpp
        )

add_subdirectory(tests)