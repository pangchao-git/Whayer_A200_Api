project(detection_atlas )
cmake_minimum_required(VERSION 3.5.1)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(tools /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)
set(TARGET detection_atlas)
set(3RD_PARTY_LIB /home/pc/work/code_view/whayer_work/whayer_git_work/whayer_ai_data/zhixin/zhixin_A200/whayer_A200_project_public/3rd_lib)
include_directories(
        ./Include/
        ./sample_npu_software
        ./sample/
        ./common/
        ./include/
        ${3RD_PARTY_LIB}/opencv-3.4.1_aarch/include

)
link_directories(${3RD_PARTY_LIB}/opencv-3.4.1_aarch/lib)

file( GLOB SRCS
        ./src/*.cpp
#        ./sample/*.c
        ./common/*.c
        ./sample_npu_software/*.c
        ./common/*.cpp
        ./sample_npu_software/*.cpp


        )

##
add_library(${TARGET} SHARED ${SRCS} )
#add_executable(${TARGET} sample_npu_main.cpp ${SRCS})
target_link_libraries(
        ${TARGET}
#        ${3RD_PARTY_LIB}/libcjson.a
#        ${3RD_PARTY_LIB}/libnpu.a
#        ${3RD_PARTY_LIB}/librcu.a
#        ${3RD_PARTY_LIB}/libsns_sc2310.a
#        ${3RD_PARTY_LIB}/libmpi.a
        opencv_core opencv_highgui
        opencv_imgproc opencv_imgcodecs
        opencv_videoio
        pthread

)
