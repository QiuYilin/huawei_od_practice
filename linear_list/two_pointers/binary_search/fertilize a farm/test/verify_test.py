#!/usr/bin/env python3
"""
测试脚本 - 适应新的输入输出格式
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
            input_lines = [line.strip() for line in f.readlines() if line.strip()]
            safe_print(f"读取到 {len(input_lines)} 行输入")
        
        with open(output_file, 'r', encoding='utf-8') as f:
            output_lines = [line.strip() for line in f.readlines() if line.strip()]
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
    
    while i < len(input_lines):
        # 解析测试用例
        # 第一行：N 和 E
        if i >= len(input_lines):
            break
            
        first_line = input_lines[i]
        if not first_line:
            i += 1
            continue
            
        # 解析第一行的 N 和 E
        try:
            n_str, e_str = first_line.split()
            N = int(n_str)
            E = int(e_str)
        except:
            safe_print(f"错误: 无法解析第一行 '{first_line}'")
            i += 1
            continue
        
        safe_print(f"测试用例 {total_cases + 1}:")
        safe_print(f"  N={N}, E={E}")
        
        # 准备输入数据
        input_data = first_line + "\n"
        
        # 读取接下来的 E 行
        engine_lines = []
        for j in range(1, E + 1):
            if i + j < len(input_lines):
                engine_line = input_lines[i + j]
                input_data += engine_line + "\n"
                engine_lines.append(engine_line)
                safe_print(f"  发动机 {j}: {engine_line}")
            else:
                safe_print(f"  错误: 缺少第 {j} 个发动机数据")
                break
        
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
                i += E + 1
                output_index += 2
                continue
            
            # 解析实际输出
            actual_output_lines = [line.strip() for line in result.stdout.strip().split('\n') if line.strip()]
            
            # 获取期望输出
            expected_output_lines = []
            if output_index < len(output_lines):
                expected_output_lines.append(output_lines[output_index])
            if output_index + 1 < len(output_lines):
                expected_output_lines.append(output_lines[output_index + 1])
            
            safe_print(f"  期望输出:")
            for idx, line in enumerate(expected_output_lines):
                safe_print(f"    第{idx+1}行: {line}")
            
            safe_print(f"  实际输出:")
            for idx, line in enumerate(actual_output_lines):
                safe_print(f"    第{idx+1}行: {line}")
            
            # 比较输出
            is_passed = True
            if len(actual_output_lines) != len(expected_output_lines):
                safe_print(f"  [X] 失败: 输出行数不匹配 (期望{len(expected_output_lines)}行, 实际{len(actual_output_lines)}行)")
                is_passed = False
            else:
                for idx, (actual, expected) in enumerate(zip(actual_output_lines, expected_output_lines)):
                    if actual != expected:
                        safe_print(f"  [X] 失败: 第{idx+1}行不匹配")
                        safe_print(f"      期望: {expected}")
                        safe_print(f"      实际: {actual}")
                        is_passed = False
                        break
            
            if is_passed:
                safe_print(f"  [V] 通过")
                passed_count += 1
            else:
                safe_print(f"  [X] 失败")
            
            output_index += 2
            total_cases += 1
            
        except subprocess.TimeoutExpired:
            safe_print(f"  [X] 程序运行超时")
            total_cases += 1
        except Exception as e:
            safe_print(f"  [X] 运行错误: {e}")
            total_cases += 1
        
        safe_print("-" * 40)
        i += E + 1  # 移动到下一个测试用例
    
    # 输出测试结果
    safe_print("=" * 60)
    if total_cases > 0:
        safe_print(f"测试完成: {passed_count}/{total_cases} 通过")
        
        if passed_count == total_cases:
            safe_print("所有测试用例通过！")
            sys.exit(0)
        else:
            safe_print("有测试用例失败")
            sys.exit(1)
    else:
        safe_print("没有找到有效的测试用例")
        sys.exit(1)

if __name__ == "__main__":
    main()