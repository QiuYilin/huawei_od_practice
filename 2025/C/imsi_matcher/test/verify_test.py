# #!/usr/bin/env python3
# """
# 简单测试脚本 - 逐行比较输入输出
# """

# import os
# import subprocess
# import sys

# # 设置标准输出的编码
# if sys.stdout.encoding != 'utf-8':
#     sys.stdout.reconfigure(encoding='utf-8')

# def main():
#     # 配置
#     executable = "C:\\Users\\Qiu\\program\\huawei_od_practice\\2025\\C\\imsi_matcher\\build\\Debug\\imsi_matcher.exe"  # 编译后的可执行文件
#     input_file = "C:\\Users\\Qiu\\program\\huawei_od_practice\\2025\\C\\imsi_matcher\\test\\input.txt"
#     output_file = "C:\\Users\\Qiu\\program\\huawei_od_practice\\2025\\C\\imsi_matcher\\test\\output.txt"
    
#     # 检查文件是否存在
#     if not os.path.exists(executable):
#         print(f"错误: 可执行文件 '{executable}' 不存在")
#         sys.exit(1)
    
#     if not os.path.exists(input_file):
#         print(f"错误: 输入文件 '{input_file}' 不存在")
#         sys.exit(1)
    
#     if not os.path.exists(output_file):
#         print(f"错误: 期望输出文件 '{output_file}' 不存在")
#         sys.exit(1)
    
#     # 读取文件内容
#     with open(input_file, 'r', encoding='utf-8') as f:
#         input_lines = [line.strip() for line in f.readlines()]
#         print(f"input_lines {input_lines}")
    
#     with open(output_file, 'r', encoding='utf-8') as f:
#         output_lines = [line.strip() for line in f.readlines()]
    
#     # 运行测试
#     passed_count = 0
#     total_cases = 0
    
#     print("开始测试...")
#     print("=" * 60)
    
#     i = 0
#     output_index = 0
    
#     while i < len(input_lines) - 1:
#         # 读取两行输入
#         config_line = input_lines[i]
#         imsi_line = input_lines[i + 1]
        
#         # 跳过空行
#         if not config_line and not imsi_line:
#             i += 2
#             continue
        
#         total_cases += 1
#         print(f"测试用例 {total_cases}:")
#         print(f"  配置: {config_line}")
#         print(f"  IMSI: {imsi_line}")
        
#         # 准备输入数据
#         input_data = f"{config_line}\n{imsi_line}\n"
        
#         # 运行程序
#         try:
#             result = subprocess.run(
#                 [executable],
#                 input=input_data,
#                 capture_output=True,
#                 text=True,
#                 timeout=5
#             )
            
#             if result.returncode != 0:
#                 print(f"  ❌ 程序异常退出，返回码: {result.returncode}")
#                 print(f"     错误信息: {result.stderr}")
#                 i += 2
#                 output_index += 1
#                 continue
            
#             actual_output = result.stdout.strip()
            
#             # 获取期望输出
#             if output_index < len(output_lines):
#                 expected_output = output_lines[output_index]
#             else:
#                 expected_output = "null"
            
#             print(f"  期望输出: {expected_output}")
#             print(f"  实际输出: {actual_output}")
            
#             # 比较输出
#             if actual_output == expected_output:
#                 print(f"通过")
#                 passed_count += 1
#             else:
#                 print(f"失败")
            
#             output_index += 1
            
#         except subprocess.TimeoutExpired:
#             print(f"程序运行超时")
#         except Exception as e:
#             print(f"运行错误: {e}")
        
#         print("-" * 40)
#         i += 2
    
#     # 输出测试结果
#     print("=" * 60)
#     print(f"测试完成: {passed_count}/{total_cases} 通过")
    
#     if passed_count == total_cases:
#         print("所有测试用例通过！")
#         sys.exit(0)
#     else:
#         print("有测试用例失败")
#         sys.exit(1)

# if __name__ == "__main__":
#     main()

#!/usr/bin/env python3
"""
简单测试脚本 - 逐行比较输入输出
"""

import os
import subprocess
import sys

# 设置标准输出的编码
if sys.stdout.encoding != 'utf-8':
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except:
        pass  # 如果reconfigure不可用，忽略错误

def safe_print(message):
    """安全打印函数，处理编码问题"""
    try:
        print(message)
    except UnicodeEncodeError:
        # 替换 Unicode 字符
        safe_message = message.replace('❌', '[X]').replace('✅', '[V]')
        print(safe_message)

def main():
    # 从命令行参数获取路径
    if len(sys.argv) != 4:
        safe_print("用法: python verify_test.py <executable> <input_file> <output_file>")
        safe_print(f"当前参数: {sys.argv}")
        sys.exit(1)
    
    executable = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]
    
    safe_print(f"可执行文件: {executable}")
    safe_print(f"输入文件: {input_file}")
    safe_print(f"输出文件: {output_file}")
    
    # 检查文件是否存在
    if not os.path.exists(executable):
        safe_print(f"错误: 可执行文件 '{executable}' 不存在")
        sys.exit(1)
    
    if not os.path.exists(input_file):
        safe_print(f"错误: 输入文件 '{input_file}' 不存在")
        sys.exit(1)
    
    if not os.path.exists(output_file):
        safe_print(f"错误: 期望输出文件 '{output_file}' 不存在")
        sys.exit(1)
    
    # 读取文件内容
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            input_lines = [line.strip() for line in f.readlines()]
            safe_print(f"读取到 {len(input_lines)} 行输入")
        
        with open(output_file, 'r', encoding='utf-8') as f:
            output_lines = [line.strip() for line in f.readlines()]
            safe_print(f"读取到 {len(output_lines)} 行期望输出")
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 运行测试
    passed_count = 0
    total_cases = 0
    
    safe_print("开始测试...")
    safe_print("=" * 60)
    
    i = 0
    output_index = 0
    
    while i < len(input_lines) - 1:
        # 读取两行输入
        config_line = input_lines[i]
        imsi_line = input_lines[i + 1]
        
        # 跳过空行
        if not config_line and not imsi_line:
            i += 2
            continue
        
        total_cases += 1
        safe_print(f"测试用例 {total_cases}:")
        safe_print(f"  配置: {config_line}")
        safe_print(f"  IMSI: {imsi_line}")
        
        # 准备输入数据
        input_data = f"{config_line}\n{imsi_line}\n"
        
        # 运行程序
        try:
            result = subprocess.run(
                [executable],
                input=input_data,
                capture_output=True,
                text=True,
                timeout=5,
                encoding='utf-8'
            )
            
            if result.returncode != 0:
                safe_print(f"  [X] 程序异常退出，返回码: {result.returncode}")
                safe_print(f"     错误信息: {result.stderr}")
                i += 2
                output_index += 1
                continue
            
            actual_output = result.stdout.strip()
            
            # 获取期望输出
            if output_index < len(output_lines):
                expected_output = output_lines[output_index]
            else:
                expected_output = "null"
            
            safe_print(f"  期望输出: {expected_output}")
            safe_print(f"  实际输出: {actual_output}")
            
            # 比较输出
            if actual_output == expected_output:
                safe_print(f"  [V] 通过")
                passed_count += 1
            else:
                safe_print(f"  [X] 失败")
            
            output_index += 1
            
        except subprocess.TimeoutExpired:
            safe_print(f"  [X] 程序运行超时")
        except Exception as e:
            safe_print(f"  [X] 运行错误: {e}")
        
        safe_print("-" * 40)
        i += 2
    
    # 输出测试结果
    safe_print("=" * 60)
    safe_print(f"测试完成: {passed_count}/{total_cases} 通过")
    
    if passed_count == total_cases:
        safe_print("所有测试用例通过！")
        sys.exit(0)
    else:
        safe_print("有测试用例失败")
        sys.exit(1)

if __name__ == "__main__":
    main()