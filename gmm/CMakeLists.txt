cmake_minimum_required(VERSION 3.5)
project(gmm)
find_package(PkgConfig)

pkg_check_modules(OPENCV opencv)
link_directories(
${OPENCV_LIBRARY_DIRS}
)
include_directories(
${OPENCV_INCLUDE_DIRS}
)

add_executable(gmm gmm.cpp)
target_link_libraries(gmm
	${OPENCV_LIBRARIES}
)