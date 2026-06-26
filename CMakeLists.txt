cmake_minimum_required(VERSION 3.22)
project(ZnVja29mZg LANGUAGES C)
set(CMAKE_C_STANDARD 2x)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(SDL3 REQUIRED)
find_package(SDL3_gpu QUIET)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
add_executable(ZnVja29mZg
  src/main.c
  src/app.c
  src/gfx.c
  src/rnd.c
  src/vec.c
  src/sys.c
  src/util_math.c
  src/s0.c
  src/s1.c
  src/s2.c
  src/s3.c
  src/s4.c
  src/s5.c
  src/s6.c
  src/s7.c
  src/s8.c
  src/s9.c
  src/sA.c
  src/sB.c
  src/sC.c
  src/sD.c
  src/sE.c
  src/sF.c
)
target_include_directories(ZnVja29mZg PRIVATE ${CMAKE_SOURCE_DIR}/include)
if(SDL3_gpu_FOUND)
  target_compile_definitions(ZnVja29mZg PRIVATE USE_GPU)
  target_link_libraries(ZnVja29mZg PRIVATE SDL3::SDL3 SDL3_gpu::SDL3_gpu)
else()
  target_link_libraries(ZnVja29mZg PRIVATE SDL3::SDL3)
endif()
if(APPLE)
  target_link_libraries(ZnVja29mZg PRIVATE "-framework Cocoa")
endif()
