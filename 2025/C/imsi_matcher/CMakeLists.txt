cmake_minimum_required(VERSION 3.10)
project(HuaweiIMSI)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义路径变量
set(INPUT_FILE ${CMAKE_SOURCE_DIR}/test/input.txt)
set(OUTPUT_FILE ${CMAKE_SOURCE_DIR}/test/output.txt)

if(NOT EXISTS ${INPUT_FILE})
    message(WARNING "输入文件不存在: ${INPUT_FILE}")
endif()

if(NOT EXISTS ${OUTPUT_FILE})
    message(WARNING "输出文件不存在: ${OUTPUT_FILE}")
endif()

# 创建可执行文件
add_executable(imsi_matcher main.cpp)

# 启用测试
enable_testing()

# 查找 Python3
# find_package(Python3 COMPONENTS Development REQUIRED)
# target_link_libraries(imsi_matcher PRIVATE Python3::Python)
find_package(Python3 REQUIRED)

# 添加测试
add_test(NAME IMSI_Matching_Test
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/verify_test.py
            $<TARGET_FILE:imsi_matcher>
            ${INPUT_FILE}
            ${OUTPUT_FILE}
)

set_tests_properties(IMSI_Matching_Test PROPERTIES
    ENVIRONMENT "PYTHONIOENCODING=utf-8"
)