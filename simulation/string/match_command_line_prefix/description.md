题目内容
给定一组命令行字符串和一个命令前缀，需要找出所有以该前缀开头的命令行表达式中，前缀之后的第一个关键字，并将这些关键字按字典序排序后返回。 如果找不到相匹配的前缀则返回空，匹配多个相同关键字仅返回一个即可。

示例 
1
1：给定的命令行表达式为 
[
"
d
i
s
p
l
a
y
["display 
d
e
v
i
c
e
device","
d
i
s
p
l
a
y
display 
p
o
r
t
port 
s
t
a
t
u
s
status"
]
], 输入前缀是 "
d
i
s
p
l
a
y
display", 则返回 
[
["
d
e
v
i
c
e
device","
p
o
r
t
port"
]
]

示例 
2
2：给定的命令行表达式为 
[
["
s
e
t
set 
n
e
g
o
t
i
a
t
i
o
n
negotiation 
m
o
d
e
mode ","
s
e
t
set 
p
o
r
t
port 
d
o
w
n
down"
]
], 输入前缀是 "", 则返回 
[
["
s
e
t
set"
]
]

示例 
3
3：给定的命令行表达式为 
[
["
g
i
t
git 
c
o
m
m
i
t
−
m
commit−m 
m
e
s
s
a
g
e
message","
g
i
t
git 
p
u
s
h
push 
o
r
i
g
i
n
origin 
m
a
s
t
e
r
master", "
g
i
t
git 
p
u
l
l
pull"
]
], 输入前缀是 "
g
i
t
git ", 则返回 
[
["
c
o
m
m
i
t
commit","
p
u
l
l
pull","
p
u
s
h
push"
]
]

补充说明:

1
1、命令行条数 
0
0~
1000
1000 条，每个命令行的长度为 
[
1
,
200
]
[1,200]。 
2
2、每个命令行表达式中的关键字均由小写字母 、_ 或 - 组成。 
3
3、命令行关键字不包含空格，命令行中的字段有空格进行间隔。 
4
4、仅命令关键字之间的空格有意义，字符串开始或结尾的空格需要忽略, 如 " " 等价于 "", "
a
a 
b
b " 等价于 "
a
a 
b
b"

输入描述
第一行输入前缀

从第二行到结束每行输入一个命令行

输出描述
找出所有以该前缀开头的命令行表达式中，前缀之后的第一个关键字，并将这些关键字按字典序排序后输出，以空格分割

样例1
输入
display
display port status
display device 
输出
device port
说明
每个命令行都和前缀 "
d
i
s
p
l
a
y
display" 匹配，则返回每个命令的第二个关键字

样例2
输入
set negotiation mode 
set port down
输出
set
说明
首先匹配 "" 的命令关键字为 
2
2 个 "
s
e
t
set", 去重后返回 
1
1 个 "
s
e
t
set"

样例3
输入
test

输出

说明
输入命令行列表为空

样例4
输入
ssss
ttttt
输出

说明
前缀匹配没找到