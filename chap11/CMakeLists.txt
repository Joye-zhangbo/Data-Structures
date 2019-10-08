# CMake最低版本要求
cmake_minimum_required(VERSION 2.6)
 
# 项目信息
PROJECT(binary_tree)
 
# 查找包, opencv使用
# find_package(OpenCV REQUIRED)
 
# 添加头文件路径
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
 
# 添加源文件路径，并将其保存在变量source_path中
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src source_path)
set(binary_tree ${source_path})

# 指定生成目标，引用source_path变量
add_executable(binary_tree ${binary_tree})

# 显式指定编译器
set(CMAKE_CXX_COMPILER "g++")
 
# 开启调试信息
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 开启所有警告
set(CMAKE_CXX_FLAGS "-Wall")
 
# 目标链接库, opencv使用, 表示当前目标文件需要链接库：${OpenCV_LIBS}
target_link_libraries(${PROJECT_NAME} m)

