#!/usr/bin/env python3
"""
测试脚本 - 推荐多样性穿插选择问题
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
            input_lines = [line.strip() for line in f.readlines() if line.strip()]
            safe_print(f"读取到 {len(input_lines)} 行输入")
        
        with open(output_file, 'r', encoding='utf-8') as f:
            expected_output = f.read().strip()
            safe_print(f"期望输出: '{expected_output}'")
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 解析输入数据
    try:
        # 第一行是N（窗口数量）
        N = int(input_lines[0])
        safe_print(f"窗口数量 N = {N}")
        
        # 第二行是K（窗口大小）
        K = int(input_lines[1])
        safe_print(f"窗口大小 K = {K}")
        
        # 剩余行是各个列表的元素
        lists = []
        for i in range(2, len(input_lines)):
            elements = input_lines[i].split()
            lists.append(elements)
            safe_print(f"列表 {i-1}: {elements}")
        
        safe_print(f"共有 {len(lists)} 个列表")
        
    except Exception as e:
        safe_print(f"解析输入数据错误: {e}")
        sys.exit(1)
    
    # 准备输入数据
    input_data = f"{N}\n{K}\n"
    for lst in lists:
        input_data += " ".join(lst) + "\n"
    
    safe_print("=" * 60)
    safe_print("开始测试...")
    
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
            safe_print(f"[X] 程序异常退出，返回码: {result.returncode}")
            safe_print(f"错误信息: {result.stderr}")
            sys.exit(1)
        
        # 获取实际输出
        actual_output = result.stdout.strip()
        
        safe_print(f"期望输出: '{expected_output}'")
        safe_print(f"实际输出: '{actual_output}'")
        
        # 比较输出（忽略空格数量的差异）
        actual_normalized = ' '.join(actual_output.split())
        expected_normalized = ' '.join(expected_output.split())
        
        safe_print(f"标准化后期望: '{expected_normalized}'")
        safe_print(f"标准化后实际: '{actual_normalized}'")
        
        # 比较输出
        if actual_normalized == expected_normalized:
            safe_print("[V] 测试通过！")
            sys.exit(0)
        else:
            safe_print("[X] 测试失败: 输出不匹配")
            
            # 详细比较差异
            actual_list = actual_normalized.split()
            expected_list = expected_normalized.split()
            
            safe_print("\n详细比较:")
            safe_print(f"期望长度: {len(expected_list)}, 实际长度: {len(actual_list)}")
            
            if len(actual_list) != len(expected_list):
                safe_print("输出长度不同！")
            
            # 找出第一个不同的位置
            min_len = min(len(actual_list), len(expected_list))
            for i in range(min_len):
                if actual_list[i] != expected_list[i]:
                    safe_print(f"第一个差异在位置 {i}: 期望 '{expected_list[i]}', 实际 '{actual_list[i]}'")
                    break
            if min_len < len(expected_list) and min_len == len(actual_list):
                safe_print(f"实际输出比期望输出短，缺少: {expected_list[min_len:]}")
            elif min_len < len(actual_list) and min_len == len(expected_list):
                safe_print(f"实际输出比期望输出长，多余: {actual_list[min_len:]}")
            
            sys.exit(1)
            
    except subprocess.TimeoutExpired:
        safe_print("[X] 程序运行超时")
        sys.exit(1)
    except Exception as e:
        safe_print(f"[X] 运行错误: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()