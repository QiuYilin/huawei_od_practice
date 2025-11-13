#!/usr/bin/env python3
"""
测试脚本 - 适应时间范围查询测试格式
输入格式:
第一行: startTime,endTime
第二行: 记录数N
接下来N行: startTime,endTime,kpi
"""

import os
import subprocess
import sys

def safe_print(message):
    """安全打印函数"""
    print(message)

def read_test_case(input_file):
    """读取单个测试用例"""
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = [line.strip() for line in f.readlines() if line.strip()]
    
    if len(lines) < 2:
        safe_print("错误: 输入文件格式不正确，至少需要2行")
        return None
    
    # 第一行: 查询时间范围
    time_range = lines[0]
    
    # 第二行: 记录数
    try:
        n = int(lines[1])
    except ValueError:
        safe_print(f"错误: 无法解析记录数 '{lines[1]}'")
        return None
    
    # 接下来的n行: 压缩记录
    if len(lines) < 2 + n:
        safe_print(f"错误: 文件行数不足，期望{2+n}行，实际{len(lines)}行")
        return None
    
    records = lines[2:2+n]
    
    return {
        'time_range': time_range,
        'n': n,
        'records': records
    }

def read_expected_output(output_file):
    """读取期望输出"""
    with open(output_file, 'r', encoding='utf-8') as f:
        lines = [line.strip() for line in f.readlines() if line.strip()]
    return lines

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
    
    # 读取测试用例
    safe_print("读取测试用例...")
    test_case = read_test_case(input_file)
    if test_case is None:
        sys.exit(1)
    
    # 读取期望输出
    safe_print("读取期望输出...")
    expected_lines = read_expected_output(output_file)
    
    # 显示测试用例信息
    safe_print("=" * 60)
    safe_print("测试用例信息:")
    safe_print(f"  查询范围: {test_case['time_range']}")
    safe_print(f"  记录数: {test_case['n']}")
    safe_print("  压缩记录:")
    for idx, record in enumerate(test_case['records']):
        safe_print(f"    {idx+1}: {record}")
    
    safe_print(f"  期望输出行数: {len(expected_lines)}")
    safe_print("  期望输出内容:")
    for line in expected_lines:
        safe_print(f"    {line}")
    
    # 准备输入数据
    input_data = f"{test_case['time_range']}\n"
    input_data += f"{test_case['n']}\n"
    for record in test_case['records']:
        input_data += f"{record}\n"
    
    safe_print("=" * 60)
    safe_print("运行程序...")
    
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
        actual_lines = [line.strip() for line in actual_output.split('\n') if line.strip()]
        
        safe_print("程序输出:")
        if actual_output:
            for line in actual_lines:
                safe_print(f"  {line}")
        else:
            safe_print("  (无输出)")
        
        safe_print("=" * 60)
        safe_print("测试结果:")
        
        # 特殊情况: 期望输出为-1
        if len(expected_lines) == 1 and expected_lines[0] == "-1":
            if actual_output.strip() == "-1":
                safe_print("[V] 通过: 正确输出-1")
                sys.exit(0)
            else:
                safe_print("[X] 失败: 期望输出-1，但程序有其他输出")
                sys.exit(1)
        
        # 比较输出行数
        if len(actual_lines) != len(expected_lines):
            safe_print(f"[X] 失败: 输出行数不匹配")
            safe_print(f"    期望: {len(expected_lines)} 行")
            safe_print(f"    实际: {len(actual_lines)} 行")
            sys.exit(1)
        
        # 逐行比较
        all_pass = True
        for i, (actual, expected) in enumerate(zip(actual_lines, expected_lines)):
            if actual == expected:
                safe_print(f"[V] 第{i+1}行: 通过")
            else:
                safe_print(f"[X] 第{i+1}行: 不匹配")
                safe_print(f"    期望: {expected}")
                safe_print(f"    实际: {actual}")
                all_pass = False
        
        if all_pass:
            safe_print("[V] 所有测试通过！")
            sys.exit(0)
        else:
            safe_print("[X] 有测试失败")
            sys.exit(1)
            
    except subprocess.TimeoutExpired:
        safe_print("[X] 程序运行超时")
        sys.exit(1)
    except Exception as e:
        safe_print(f"[X] 运行错误: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()