#!/usr/bin/env python3
"""
测试脚本 - 适应打卡记录测试格式
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
            output_content = f.read().strip()
            output_lines = [line.strip() for line in output_content.split('\n') if line.strip()]
            safe_print(f"读取到 {len(output_lines)} 行期望输出")
    except Exception as e:
        safe_print(f"读取文件错误: {e}")
        sys.exit(1)
    
    # 解析测试用例
    test_cases = []
    i = 0
    
    while i < len(input_lines):
        # 每个测试用例以数字 N 开始
        try:
            n_line = input_lines[i]
            N = int(n_line.strip())
            safe_print(f"找到测试用例: N={N}")
        except:
            safe_print(f"错误: 无法解析N '{n_line}'")
            i += 1
            continue
        
        # 读取接下来的 N 行打卡记录
        records = []
        for j in range(1, N + 1):
            if i + j < len(input_lines):
                record_line = input_lines[i + j]
                records.append(record_line)
            else:
                safe_print(f"错误: 缺少第 {j} 条打卡记录")
                break
        
        if len(records) == N:
            test_cases.append({
                'n': N,
                'records': records
            })
            safe_print(f"  包含 {len(records)} 条记录")
        
        i += N + 1
    
    safe_print(f"共解析出 {len(test_cases)} 个测试用例")
    
    # 运行测试
    passed_count = 0
    total_cases = len(test_cases)
    
    safe_print("开始测试...")
    safe_print("=" * 60)
    
    for case_idx, test_case in enumerate(test_cases):
        safe_print(f"测试用例 {case_idx + 1}:")
        safe_print(f"  N={test_case['n']}")
        
        # 显示记录
        for idx, record in enumerate(test_case['records']):
            safe_print(f"  记录{idx+1}: {record}")
        
        # 准备输入数据
        input_data = f"{test_case['n']}\n"
        for record in test_case['records']:
            input_data += record + "\n"
        
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
            if case_idx < len(output_lines):
                expected_output = output_lines[case_idx].strip()
            
            safe_print(f"  期望输出: '{expected_output}'")
            safe_print(f"  实际输出: '{actual_output}'")
            
            # 比较输出
            if actual_output == expected_output:
                safe_print(f"  [V] 通过")
                passed_count += 1
            else:
                safe_print(f"  [X] 失败: 输出不匹配")
                
                # 详细比较
                if actual_output == "null" and expected_output == "null":
                    safe_print("  [V] 实际上都是 'null'，通过")
                    passed_count += 1
                else:
                    # 对于分号分隔的输出，比较集合是否相同
                    actual_set = set(actual_output.split(';')) if actual_output != "null" else set()
                    expected_set = set(expected_output.split(';')) if expected_output != "null" else set()
                    
                    if actual_set == expected_set:
                        safe_print("  [V] 输出记录集合相同，顺序可能不同但内容正确")
                        passed_count += 1
                    else:
                        safe_print(f"  [X] 记录集合不同")
                        if actual_set - expected_set:
                            safe_print(f"      多余记录: {actual_set - expected_set}")
                        if expected_set - actual_set:
                            safe_print(f"      缺少记录: {expected_set - actual_set}")
            
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