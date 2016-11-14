cmake_minimum_required(VERSION 2.8)
project( DisplayImage )


find_package( OpenCV REQUIRED )
find_package(PCL 1.7)


include_directories(${PCL_INCLUDE_DIRS})

add_executable( DisplayImage display_image.cpp)
target_link_libraries( DisplayImage ${OpenCV_LIBS}
                                     ${PCL_LIBRARIES} )

link_directories(${PCL_LIBRARY_DIRS})
