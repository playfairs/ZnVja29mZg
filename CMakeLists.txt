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
  src/core/main.c
  src/core/app.c
  src/core/gfx.c
  src/core/audio.c
  src/core/rnd.c
  src/core/vec.c
  src/core/sys.c
  src/core/util_math.c
  src/visuals/s0.c
  src/visuals/s1.c
  src/visuals/s2.c
  src/visuals/s3.c
  src/visuals/s4.c
  src/visuals/s5.c
  src/visuals/s6.c
  src/visuals/s7.c
  src/visuals/s8.c
  src/visuals/s9.c
  src/visuals/sA.c
  src/visuals/sB.c
  src/visuals/sC.c
  src/visuals/sD.c
  src/visuals/sE.c
  src/visuals/sF.c
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
