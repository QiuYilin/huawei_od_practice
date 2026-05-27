cmake_minimum_required(VERSION 3.10)
project(test)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建可执行文件
add_executable(main main.cpp)

# # 启用测试
# enable_testing()

# # 查找 Python3
# find_package(Python3 REQUIRED)

# # 添加测试
# add_test(NAME Test
#     COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test/verify_test.py
#             $<TARGET_FILE:main>
#             ${INPUT_FILE}
#             ${OUTPUT_FILE}
# )

# set_tests_properties(Test PROPERTIES
#     ENVIRONMENT "PYTHONIOENCODING=utf-8"
# )