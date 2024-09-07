cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set the project name
project(MyGTestProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_options(-Werror=return-type)
#add_compile_options(-Werror=format)

include_directories(src)


# Add Google Test
# add_subdirectory(googletest)  # If using submodule, otherwise see the alternative below


# Find Google Test
find_package(GTest REQUIRED)
message(STATUS "GTest include directories: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTEST_LIBRARIES}")
include_directories(${GTEST_INCLUDE_DIRS})


# Manually set OpenMP flags for Clang on macOS
if(APPLE)
   message(STATUS "Compile on Apple")
   set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
   set(OpenMP_C_LIB_NAMES "omp")
   set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
   set(OpenMP_CXX_LIB_NAMES "omp")
   set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
   
   #set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-14")
   #set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")
   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++") #  libstdc++ for GCC 
   #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libstdc++")

   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11") #for libc++ for Clang , 
   #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

   # Apply these flags to the compiler and linker
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")
else()
    find_package(OpenMP REQUIRED)
endif()

# Add the OpenMP flags to the compiler
if(OpenMP_CXX_FOUND)
	#    target_compile_options(runTests PUBLIC ${OpenMP_CXX_FLAGS})
endif()

 

include_directories(src/IBJts/source/cppclient/)
include_directories(src/IBJts/source/cppclient/client/)
include_directories(src/IBJts/samples/Cpp/TestCppClient/)

find_package(Boost REQUIRED COMPONENTS log log_setup system thread)
include_directories(${Boost_INCLUDE_DIRS})

#postgresql
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)
include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})
if(APPLE)
   include_directories(/opt/homebrew/opt/libpq/include)
   link_directories(/opt/homebrew/opt/libpq/lib)
else()
   include_directories(/usr/include/postgresql)
   link_directories(${PostgreSQL_LIBRARY_DIRS})
endif()


file(GLOB_RECURSE IB_API_SRC_FILES IBJts/source/cppclient/client/*.cpp)
# Add the test executable
file(GLOB_RECURSE SRC_FILES  ./src/*.cpp)

message(STATUS "Source files: ${SRC_FILES}")
add_executable(runTests ${SRC_FILES} ${IB_API_SRC_FILES}
        src/src/main.cpp
        src/src/IBClient.cpp
        src/src/IBClient.h
        src/src/log.cpp
        src/src/log.h
        src/src/event/DataEvent.cpp
        src/src/event/DataEvent.h
        src/src/stage.h)
# Link test executable against gtest & gtest_main
target_link_libraries(runTests    pthread ${Boost_LIBRARIES}  ${PQXX_LIBRARIES}  pq )
