# Define minimum required versions of CMAKE and COMPILER
cmake_minimum_required(VERSION 3.5.0)
project(Graph_TIProject VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Request for GoogleTest Testing Suite per instructions provided by GoogleTest Documentation 
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  DOWNLOAD_EXTRACT_TIMESTAMP = true
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define paths to header and cpp files for compiler
set( TARGET ${PROJECT_NAME} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/includes" )
set( TEST_PATH ${SOURCE_PATH}/tests.cc)

# Ensure inclusion of ALL header files found in associated directory and vice versa for cpp files in its associated directory
file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

# Define executable file and ensure all files in both directories are included
add_executable( ${TARGET} ${CPPS} ${HPPS} )
target_include_directories( ${TARGET} PUBLIC ${INCLUDE_PATH} )

# Define compiler flags and g++ compiler version to use for compiling project executable
# Set compiler flags
if (CMAKE_CXX_COMPILER MATCHES "gcc.exe")
    target_compile_options( ${TARGET} PRIVATE -Wall -O3 -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )
    target_compile_features( ${TARGET} PRIVATE cxx_std_17 )
elseif (CMAKE_CXX_COMPILER MATCHES "cl.exe")
    target_compile_options( ${TARGET} PRIVATE /Wall /EHsc /Qspectre )
    target_compile_features( ${TARGET} PRIVATE cxx_std_17 )
    target_compile_definitions( ${TARGET} PRIVATE VS_PRESENT )
endif()

# Have CMake send different definitions to compiler based on its build type value/configuration
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:RelWithDebInfo>:RELDEBUG>
)

# Define path to executable file used for GoogleTest Testing suite
enable_testing()
add_executable(tests ${TEST_PATH})
target_link_libraries(tests GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(tests)

# Define install path
install( 
    TARGETS ${TARGET} 
    RUNTIME DESTINATION 
)