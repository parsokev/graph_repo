cmake_minimum_required(VERSION 3.0.0)
project(Graph_TIProject VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set( TARGET ${PROJECT_NAME} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/includes" )
set( TEST_PATH ${SOURCE_PATH}/tests.cc)

file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )
add_executable( ${TARGET} ${CPPS} ${HPPS} )

target_include_directories( ${TARGET} PUBLIC ${INCLUDE_PATH} )
target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )
target_compile_features( ${TARGET} PRIVATE cxx_std_20 )

enable_testing()
add_executable(tests ${TEST_PATH})
target_link_libraries(tests GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(tests)

install( 
    TARGETS ${TARGET} 
    RUNTIME DESTINATION 
)