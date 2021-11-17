
############################################################
# Initial defs
############################################################
cmake_minimum_required(VERSION 3.16) # CMake version check
project(szs_time_sync VERSION 0.1.0) # Create project "szs_time_sync"

##########################################################################################
##########################################################################################
##########################################################################################

#Generate the static library from the library sources
add_library(szs_time_sync INTERFACE)

target_include_directories(szs_time_sync INTERFACE
        include
        )

target_sources(${PROJECT_NAME} INTERFACE
        src/syncMaster.cpp
        src/syncSlave.cpp
        src/timeKeeper.cpp
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
###########################   Add subdirectories   #######################################
##########################################################################################

add_subdirectory(extern)

# Link libraries to project
target_link_libraries(${PROJECT_NAME} INTERFACE ${mybcm2835} szs_datatransport)

add_subdirectory(tests)