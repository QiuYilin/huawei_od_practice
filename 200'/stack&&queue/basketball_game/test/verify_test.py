#!/usr/bin/env python3
"""
篮球游戏测试脚本
"""

import os
import subprocess
import sys

def main():
    # 从命令行参数获取路径
    if len(sys.argv) != 4:
        print("用法: python test_basketball.py <executable> <input_file> <output_file>")
        print(f"当前参数: {sys.argv}")
        sys.exit(1)
    
    executable = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]
    
    print(f"可执行文件: {executable}")
    print(f"输入文件: {input_file}")
    print(f"输出文件: {output_file}")
    
    # 检查文件是否存在
    if not os.path.exists(executable):
        print(f"错误: 可执行文件 '{executable}' 不存在")
        sys.exit(1)
    
    if not os.path.exists(input_file):
        print(f"错误: 输入文件 '{input_file}' 不存在")
        sys.exit(1)
    
    if not os.path.exists(output_file):
        print(f"错误: 期望输出文件 '{output_file}' 不存在")
        sys.exit(1)
    
    # 读取测试用例
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            input_lines = [line.strip() for line in f.readlines() if line.strip()]
        
        with open(output_file, 'r', encoding='utf-8') as f:
            expected_outputs = [line.strip() for line in f.readlines() if line.strip()]
    except Exception as e:
        print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 解析测试用例（每两行输入对应一行输出）
    test_cases = []
    i = 0
    case_num = 0
    
    while i < len(input_lines):
        if i + 1 < len(input_lines):
            # 每个测试用例有两行输入
            input1 = input_lines[i]
            input2 = input_lines[i + 1]
            
            # 对应的期望输出
            expected_output = ""
            if case_num < len(expected_outputs):
                expected_output = expected_outputs[case_num]
            
            test_cases.append({
                'input1': input1,
                'input2': input2,
                'expected': expected_output
            })
            
            i += 2
            case_num += 1
        else:
            break
    
    print(f"共解析出 {len(test_cases)} 个测试用例")
    
    # 运行测试
    passed_count = 0
    total_cases = len(test_cases)
    
    print("开始测试篮球游戏...")
    print("=" * 60)
    
    for case_idx, test_case in enumerate(test_cases):
        print(f"测试用例 {case_idx + 1}:")
        print(f"  输入1: {test_case['input1']}")
        print(f"  输入2: {test_case['input2']}")
        print(f"  期望输出: '{test_case['expected']}'")
        
        # 准备输入数据（两行输入）
        input_data = test_case['input1'] + "\n" + test_case['input2'] + "\n"
        
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
                print(f"  [X] 程序异常退出，返回码: {result.returncode}")
                print(f"     错误信息: {result.stderr}")
                continue
            
            # 获取实际输出
            actual_output = result.stdout.strip()
            print(f"  实际输出: '{actual_output}'")
            
            # 比较输出
            if actual_output == test_case['expected']:
                print(f"  [V] 通过")
                passed_count += 1
            else:
                print(f"  [X] 失败: 输出不匹配")
                
                # 对于NO的情况，检查是否都是NO
                if actual_output.upper() == "NO" and test_case['expected'].upper() == "NO":
                    print("  [V] 实际上都是 'NO'，通过")
                    passed_count += 1
                else:
                    # 对于操作序列，检查长度是否相同（可能顺序不同但都正确）
                    if len(actual_output) == len(test_case['expected']):
                        print(f"      输出长度相同但内容不同")
                    else:
                        print(f"      输出长度不同: 期望{len(test_case['expected'])}, 实际{len(actual_output)}")
            
        except subprocess.TimeoutExpired:
            print(f"  [X] 程序运行超时")
        except Exception as e:
            print(f"  [X] 运行错误: {e}")
        
        print("-" * 40)
    
    # 输出测试结果
    print("=" * 60)
    if total_cases > 0:
        print(f"测试完成: {passed_count}/{total_cases} 通过")
        
        if passed_count == total_cases:
            print("所有测试用例通过！")
            sys.exit(0)
        else:
            print("有测试用例失败")
            sys.exit(1)
    else:
        print("没有找到有效的测试用例")
        sys.exit(1)

if __name__ == "__main__":
    main()