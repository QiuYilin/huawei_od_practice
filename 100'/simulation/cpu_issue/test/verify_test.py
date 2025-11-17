#!/usr/bin/env python3
"""
测试脚本 - AI处理器亲和性调度
专门测试 main.cpp
"""

import os
import subprocess
import sys
import ast

def safe_print(message):
    """安全打印函数"""
    print(message)

def compare_results(actual, expected):
    """比较两个结果是否相同"""
    try:
        # 解析实际输出和期望输出
        actual_list = ast.literal_eval(actual) if actual.strip() else []
        expected_list = ast.literal_eval(expected) if expected.strip() else []
        
        # 对内部列表排序以便比较
        def normalize_result(result):
            if not result:
                return []
            sorted_result = []
            for item in result:
                if isinstance(item, list):
                    sorted_result.append(sorted(item))
                else:
                    sorted_result.append(item)
            return sorted(sorted_result)
        
        actual_normalized = normalize_result(actual_list)
        expected_normalized = normalize_result(expected_list)
        
        return actual_normalized == expected_normalized
    except Exception as e:
        safe_print(f"比较结果错误: {e}")
        return False

def run_test_case(executable, array_input, num_input):
    """运行单个测试用例"""
    try:
        # 准备输入数据
        input_data = f"{array_input}\n{num_input}\n"
        
        result = subprocess.run(
            [executable],
            input=input_data,
            capture_output=True,
            text=True,
            timeout=5,
            encoding='utf-8'
        )
        
        if result.returncode != 0:
            return None, f"程序异常退出，返回码: {result.returncode}\n错误信息: {result.stderr}"
        
        return result.stdout.strip(), None
    except subprocess.TimeoutExpired:
        return None, "程序运行超时"
    except Exception as e:
        return None, f"运行错误: {e}"

def main():
    # 从命令行参数获取路径
    if len(sys.argv) != 4:
        safe_print("用法: python test_processor.py <executable> <input_file> <output_file>")
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
        
        with open(output_file, 'r', encoding='utf-8') as f:
            expected_outputs = [line.strip() for line in f.readlines() if line.strip()]
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 运行测试
    passed_count = 0
    total_cases = 0
    
    safe_print("开始测试AI处理器亲和性调度...")
    safe_print("=" * 60)
    
    # 处理测试用例 - 每两行输入对应一行输出
    i = 0
    test_cases = []
    
    # 解析输入文件，每组测试用例包含两行
    while i < len(input_lines):
        if i + 1 < len(input_lines):
            array_line = input_lines[i]
            num_line = input_lines[i + 1]
            expected_output = expected_outputs[len(test_cases)] if len(test_cases) < len(expected_outputs) else ""
            test_cases.append((array_line, num_line, expected_output))
            i += 2
        else:
            break
    
    # 运行所有测试用例
    for idx, (array_input, num_input, expected_output) in enumerate(test_cases):
        safe_print(f"测试用例 {idx + 1}:")
        safe_print(f"  输入数组: {array_input}")
        safe_print(f"  申请数量: {num_input}")
        safe_print(f"  期望输出: {expected_output}")
        
        # 运行程序
        actual_output, error = run_test_case(executable, array_input, num_input)
        
        if error:
            safe_print(f"  [X] 运行失败: {error}")
            total_cases += 1
            continue
        
        safe_print(f"  实际输出: {actual_output}")
        
        # 比较结果
        if compare_results(actual_output, expected_output):
            safe_print(f"  [V] 通过")
            passed_count += 1
        else:
            safe_print(f"  [X] 失败: 输出不匹配")
        
        total_cases += 1
        safe_print("-" * 40)
    
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