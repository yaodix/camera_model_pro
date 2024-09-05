cmake_minimum_required(VERSION 2.8.3)
project(camera_model)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    )

find_package(Boost REQUIRED COMPONENTS filesystem program_options system)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV 4.5 REQUIRED)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})


find_package(Eigen3 REQUIRED)
include_directories("/usr/include/eigen3")
# find_package(Ceres REQUIRED)
# include_directories(${CERES_INCLUDE_DIRS})
add_subdirectory(ceres)
include_directories(${PROJECT_SOURCE_DIR}/ceres/include)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES camera_model
    CATKIN_DEPENDS roscpp std_msgs
    DEPENDS system_lib
    )

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${code_utils_INCLUDE_DIRS}
    )

include_directories("include")


add_executable(Calibration 
    src/intrinsic_calib.cc
    src/chessboard/Chessboard.cc
    src/calib/CameraCalibration.cc
    src/camera_models/Camera.cc
    src/camera_models/CameraFactory.cc
    src/camera_models/CostFunctionFactory.cc
    src/camera_models/PinholeCamera.cc
    src/camera_models/CataCamera.cc
    src/camera_models/EquidistantCamera.cc
    src/camera_models/ScaramuzzaCamera.cc
    src/camera_models/PolyFisheyeCamera.cpp
    src/camera_models/FovCamera.cpp
    src/sparse_graph/Transform.cc
    src/gpl/gpl.cc
    src/code_utils/math_utils/Polynomial.cpp
    src/gpl/EigenQuaternionParameterization.cc)


add_library(camera_model STATIC
    src/chessboard/Chessboard.cc
    src/calib/CameraCalibration.cc
    src/camera_models/Camera.cc
    src/camera_models/CameraFactory.cc
    src/camera_models/CostFunctionFactory.cc
    src/camera_models/PinholeCamera.cc
    src/camera_models/CataCamera.cc
    src/camera_models/EquidistantCamera.cc
    src/camera_models/ScaramuzzaCamera.cc
    src/camera_models/PolyFisheyeCamera.cpp
    src/camera_models/FovCamera.cpp
    src/sparse_graph/Transform.cc
    src/gpl/gpl.cc
    src/code_utils/math_utils/Polynomial.cpp
    src/gpl/EigenQuaternionParameterization.cc)

target_compile_definitions(Calibration PRIVATE CERES_USE_CXX11_THREADS=1)
target_compile_definitions(camera_model PRIVATE CERES_USE_CXX11_THREADS=1)
    
target_link_libraries(Calibration
    ${Boost_LIBRARIES}
    ${OpenCV_LIBS}
    ceres
    ${code_utils_LIBRARIES})
target_link_libraries(camera_model
    ${Boost_LIBRARIES}
    ${OpenCV_LIBS}
    ceres
    ${code_utils_LIBRARIES})


add_executable(test src/test.cc
src/chessboard/Chessboard.cc
src/calib/CameraCalibration.cc
src/camera_models/Camera.cc
src/camera_models/CameraFactory.cc
src/camera_models/CostFunctionFactory.cc
src/camera_models/PinholeCamera.cc
src/camera_models/CataCamera.cc
src/camera_models/EquidistantCamera.cc
src/camera_models/ScaramuzzaCamera.cc
src/camera_models/PolyFisheyeCamera.cpp
src/camera_models/FovCamera.cpp
src/sparse_graph/Transform.cc
src/gpl/gpl.cc
src/code_utils/math_utils/Polynomial.cpp
src/gpl/EigenQuaternionParameterization.cc)

target_compile_definitions(test PRIVATE CERES_USE_CXX11_THREADS=1)


target_link_libraries(test ${Boost_LIBRARIES} ${OpenCV_LIBS} ceres ${code_utils_LIBRARIES})
