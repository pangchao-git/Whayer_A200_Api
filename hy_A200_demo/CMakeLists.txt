project(A200_npu_sample )
cmake_minimum_required(VERSION 3.5.1)
add_compile_options(-std=c++11  )
set(tools /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)
set(TARGET whayer_SCA200_Sample_public)
set(3RD_PARTY_LIB /home/pc/work/code_view/whayer_work/whayer_git_work/whayer_ai_data/zhixin/zhixin_A200/whayer_A200_project_public/3rd_lib)
include_directories(
        ./include
        ${3RD_PARTY_LIB}/opencv-3.4.1_aarch/include

)
link_directories(${3RD_PARTY_LIB}/opencv-3.4.1_aarch/lib
        ./lib)



add_executable(${TARGET} demo.cpp )
target_link_libraries(
        ${TARGET}
        detection_atlas
        ${3RD_PARTY_LIB}/libcjson.a
        ${3RD_PARTY_LIB}/libnpu.a
        ${3RD_PARTY_LIB}/librcu.a
        ${3RD_PARTY_LIB}/libsns_sc2310.a
        ${3RD_PARTY_LIB}/libmpi.a
        opencv_core opencv_highgui
        opencv_imgproc opencv_imgcodecs
        opencv_videoio
        pthread

)
#add_subdirectory(hy_A200_detect_project)
