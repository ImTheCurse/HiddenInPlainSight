cmake_minimum_required(VERSION 2.8)
project( HIPS )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( HIPS 
main.cpp 
src/Encode.cpp
src/Encode.hpp
src/Decode.cpp
src/Decode.hpp

)
target_link_libraries( HIPS ${OpenCV_LIBS} )