题目描述
实现一个操作历史管理器，使用双向链表存储执行过的操作。支持执行新操作、撤销和重做功能。

功能说明:

执行操作（execute {操作描述}）：执行新操作，并清除当前操作之后的所有历史记录
撤销（undo）：回退到上一个操作状态（上一个操作状态可以为从未执行过任何操作的状态，若当前状态已经是从未执行过任何操作的状态，则 undo 失败）
重做（redo）：前进到下一个操作状态（下一个操作状态是之前撤销过的操作，若没有进行过撤销操作（即链表的下一个操作状态不存在），则 redo 失败）
输入保证命令只会出现 execute {操作描述}、undo、redo 三种类型

输入描述
每一行输出一个命令

输出描述
执行完所有命令后，返回当前操作的描述
若执行 undo时，当前状态是从未执行过任何操作的状态，立即返回 "undo failed"，不继续执行后续命令。（注意：undo可以撤销到从未执行过任何操作的状态）
若执行 redo 时无下一个操作，立即返回 "redo failed"，不继续执行后续命令
若当前状态是从未执行过任何操作，当前操作描述为空字符串 ""
用例1
输入
execute,insert hello
execute,newline
execute,insert woo
undo
execute,insert world
undo
输出
newline
说明
执行insert hello ->当前insert hello
执行newline -> 当前newline
执行insert woo -> 当前 insert woo
撤销 -> 当前newline
执行insert world -> 当前insert world
撤销 -> 当前newline
用例2
输入
execute,insert hello
undo
输出

说明
执行insert hello -> 当前insert hello

撤销，当前状态为"",空字符串

用例3
输入
execute,insert hello
undo
redo
输出
insert hello
说明
执行insert hello,当前为insert hello
撤销，当前状态为""
重做，当前为insert hello