#!/usr/bin/env python3
"""
测试脚本 - 适应文本编辑器测试格式
"""

import os
import subprocess
import sys

def safe_print(message):
    """安全打印函数"""
    print(message)

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
            input_content = f.read().strip()
            input_lines = [line.strip() for line in input_content.split('\n') if line.strip()]
            safe_print(f"读取到 {len(input_lines)} 行输入")
        
        with open(output_file, 'r', encoding='utf-8') as f:
            expected_outputs = [line.strip() for line in f.read().strip().split('\n') if line.strip()]
            safe_print(f"读取到 {len(expected_outputs)} 个期望输出")
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 解析测试用例 - 文本编辑器格式
    test_cases = []
    i = 0
    
    while i < len(input_lines):
        try:
            # 第一行是指令数量 K
            k_line = input_lines[i]
            K = int(k_line.strip())
            safe_print(f"找到测试用例: K={K}")
            
            # 第二行是原始文本
            if i + 1 < len(input_lines):
                original_text = input_lines[i + 1]
                safe_print(f"  原始文本: '{original_text}'")
            else:
                safe_print("错误: 缺少原始文本")
                break
            
            # 接下来的 K 行是指令
            commands = []
            for j in range(K):
                if i + 2 + j < len(input_lines):
                    command_line = input_lines[i + 2 + j]
                    commands.append(command_line)
                else:
                    safe_print(f"错误: 缺少第 {j+1} 条指令")
                    break
            
            if len(commands) == K:
                test_cases.append({
                    'k': K,
                    'original_text': original_text,
                    'commands': commands
                })
                safe_print(f"  包含 {len(commands)} 条指令")
            
            i += 2 + K  # 移动到下一个测试用例
            
        except Exception as e:
            safe_print(f"解析测试用例时出错: {e}")
            i += 1
    
    safe_print(f"共解析出 {len(test_cases)} 个测试用例")
    
    # 运行测试
    passed_count = 0
    total_cases = len(test_cases)
    
    safe_print("开始测试...")
    safe_print("=" * 60)
    
    for case_idx, test_case in enumerate(test_cases):
        safe_print(f"测试用例 {case_idx + 1}:")
        safe_print(f"  K={test_case['k']}")
        safe_print(f"  原始文本: '{test_case['original_text']}'")
        
        # 显示指令
        for idx, command in enumerate(test_case['commands']):
            safe_print(f"  指令{idx+1}: {command}")
        
        # 准备输入数据 - 文本编辑器格式
        input_data = f"{test_case['k']}\n"
        input_data += test_case['original_text'] + "\n"
        for command in test_case['commands']:
            input_data += command + "\n"
        
        safe_print(f"  输入数据预览:")
        safe_print(f"    {test_case['k']}")
        safe_print(f"    {test_case['original_text']}")
        for cmd in test_case['commands']:
            safe_print(f"    {cmd}")
        
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
                continue
            
            # 获取实际输出
            actual_output = result.stdout.strip()
            
            # 获取期望输出
            expected_output = ""
            if case_idx < len(expected_outputs):
                expected_output = expected_outputs[case_idx].strip()
            
            safe_print(f"  期望输出: '{expected_output}'")
            safe_print(f"  实际输出: '{actual_output}'")
            
            # 比较输出
            if actual_output == expected_output:
                safe_print(f"  [V] 通过")
                passed_count += 1
            else:
                safe_print(f"  [X] 失败: 输出不匹配")
                
                # 详细比较字符
                safe_print(f"  详细比较:")
                safe_print(f"    期望长度: {len(expected_output)}, 实际长度: {len(actual_output)}")
                
                # 找到第一个不同的字符
                min_len = min(len(expected_output), len(actual_output))
                for idx in range(min_len):
                    if expected_output[idx] != actual_output[idx]:
                        safe_print(f"    第{idx}个字符不同: 期望 '{expected_output[idx]}'(ASCII {ord(expected_output[idx])}), 实际 '{actual_output[idx]}'(ASCII {ord(actual_output[idx])})")
                        break
                if len(expected_output) != len(actual_output):
                    safe_print(f"    长度不同: 期望长度 {len(expected_output)}, 实际长度 {len(actual_output)}")
            
        except subprocess.TimeoutExpired:
            safe_print(f"  [X] 程序运行超时")
        except Exception as e:
            safe_print(f"  [X] 运行错误: {e}")
        
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