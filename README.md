# Whayer_A200_public
1 需要设置交叉编译工具链 
set(tools /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)
