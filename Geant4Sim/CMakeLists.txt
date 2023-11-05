#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Simulation)

#----------------------------------------------------------------------------
# Find Geant4 package
#
find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources, headers and macros for this project
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES
   "*.mac"
)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we build the executable
#
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(pet_simulation pet_simulation.cc ${sources} ${headers}) #executable name and cc file name
target_link_libraries(pet_simulation ${Geant4_LIBRARIES}) #executable name

add_custom_target(Simulation DEPENDS pet_simulation) #project name DEPENDS executable name
