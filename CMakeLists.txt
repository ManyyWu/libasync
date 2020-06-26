cmake_minimum_required(VERSION 3.4)
project(libasync LANGUAGES C)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 90)

set(AS_VERSION_MAJOR 0)
set(AS_VERSION_MINOR 1)
set(AS_VERSION_PATCH 0)
set(AS_VERSION "${AS_VERSION_MAJOR}.${AS_VERSION_MINOR}.${AS_VERSION_PATCH}")

option(as_build_static "Build static libray" ON)
option(as_build_shared "Build shared libray" ON)
option(as_build_http "Build the http modules" ON)
option(as_build_test "Build the unit tests" ON)

list(APPEND compile_flags
     )

configure_file(config.h.in ${CMAKE_SOURCE_DIR}/include/async/config.h)

list(APPEND inc_dirs
     include
     src
     src/core
     src/event
     src/fs
     src/net
     src/os
     src/stream
     src/tty)

if(as_build_http)
  list(APPEND async_http_srcs
       src/http/http.c)
endif()

include_directories(${inc_dirs})

list(APPEND async_srcs
     src/core/core.c
     src/core/common.c
     src/core/log.c
     src/core/timer.c)

if(WIN32)
  list(APPEND async_srcs
       src/core/win_core.c
       src/core/win_util.c
       src/core/win_thread.c)
  list(APPEND async_libs
       ws2_32)
else()
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND async_srcs
         src/core/linux_core.c)
  elseif(APPLE)
    list(APPEND async_srcs
         src/core/darwin.c)
  endif()

  list(APPEND async_srcs
       src/core/posix_thread.c)
  list(APPEND async_libs
       pthread)
endif()
message(${async_srcs})

if (as_build_test)
  set(as_build_static ON)
endif()

if(as_build_static)
  add_library(async_a STATIC ${async_srcs})
  target_link_libraries(async_a PUBLIC ${async_libs})

  if(as_build_http)
    list(APPEND async_http_libs
         async_a)
    add_library(async_http_a STATIC ${async_http_srcs})
    target_link_libraries(async_http_a PUBLIC ${async_http_libs})
  endif()
endif()

if(as_build_shared)
  add_library(async SHARED ${async_srcs})
  target_link_libraries(async PUBLIC ${async_libs})
  target_compile_definitions(async INTERFACE AS_USING_SHARED PRIVATE AS_BUILDING_SHARED)

  if(as_build_http)
    list(APPEND async_http_libs
         async)
    add_library(async_http SHARED ${async_http_srcs})
    target_link_libraries(async_http PUBLIC ${async_http_libs})
  endif()
endif()

if (as_build_test)
  list(APPEND async_test_srcs
       test/cmockery.c
       test/run_test.c
       test/test-util.c
       test/test-get-time.c
       test/test-error.c
       test/test-lock.c
       test/test-thread.c
       )
  add_executable(async_run_test ${async_test_srcs})
  target_include_directories(async_run_test PUBLIC test)
  target_link_libraries(async_run_test async_a)
  add_test(NAME async_run_test
           COMMAND async_run_test
           WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()