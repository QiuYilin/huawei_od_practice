#!/usr/bin/env python3
"""
斗地主顺子检测测试脚本
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
        safe_print("用法: python test_poker.py <executable> <input_file> <output_file>")
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
            safe_print(f"输入内容: {input_content}")
        
        with open(output_file, 'r', encoding='utf-8') as f:
            expected_output = f.read().strip()
            safe_print(f"期望输出: {expected_output}")
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 运行测试
    safe_print("开始测试...")
    safe_print("=" * 60)
    
    try:
        # 运行程序
        result = subprocess.run(
            [executable],
            input=input_content,
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
        safe_print(f"实际输出: {actual_output}")
        
        # 比较输出
        if actual_output == expected_output:
            safe_print("[V] 测试通过！")
            sys.exit(0)
        else:
            safe_print("[X] 测试失败: 输出不匹配")
            
            # 对于多行输出，按行比较
            actual_lines = [line.strip() for line in actual_output.split('\n') if line.strip()]
            expected_lines = [line.strip() for line in expected_output.split('\n') if line.strip()]
            
            # 如果都是"No"，也算通过
            if actual_output == "No" and expected_output == "No":
                safe_print("[V] 实际上都是 'No'，测试通过")
                sys.exit(0)
            
            # 检查顺子集合是否相同（忽略顺序）
            actual_straights = set(actual_lines) if actual_output != "No" else set()
            expected_straights = set(expected_lines) if expected_output != "No" else set()
            
            if actual_straights == expected_straights:
                safe_print("[V] 顺子集合相同，测试通过")
                sys.exit(0)
            else:
                safe_print("[X] 顺子集合不同")
                if actual_straights - expected_straights:
                    safe_print(f"    多余顺子: {actual_straights - expected_straights}")
                if expected_straights - actual_straights:
                    safe_print(f"    缺少顺子: {expected_straights - actual_straights}")
                sys.exit(1)
                
    except subprocess.TimeoutExpired:
        safe_print("[X] 程序运行超时")
        sys.exit(1)
    except Exception as e:
        safe_print(f"[X] 运行错误: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()