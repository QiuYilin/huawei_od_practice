题目描述
模拟一个系统的命令行配置，包含添加、修改、删除三项操作，详情如下：

添加操作命令：add_rule rule_id=1 rule_index=18
修改操作命令：mod_rule rule_id=1 rule_index=100
删除操作命令：del_rule rule_id=1
其中：add_rule、mod_rule、del_rule是操作关键字，rule_id和rule_index是属性关键字且属性取值范围为数字 1 - 9999 之间，操作、属性之间都用空格进行分割。

在进行所有操作时，如果缺少关键字，或者相应的 rule_id、rule_index的取值不符合要求，则操作失败。
在进行添加操作时，参数必须包含 rule_id 和 rule_index,如果当前不存在，则添加成功，如果添加已经存在的 rule_id，则操作失败。
在进行修改操作时，参数必须包含rule_id和rule_index，如果当前rule_id不存在，或前后rule_index没有变化，则操作失败。
在进行删除操作时，参数必须包含rule_id，如果当前rule_id不存在，则操作失败
在进行批量操作时，一个命令失败后可以继续下一条命令的操作。现给有一组批量操作的字符串，包括不超过 1000 条连续的操作指令，格式为 [cmd][cmd][cmd]，请将字符串解析后按照顺序进入你实现的系统，统计出配置失败的次数。

输入描述
输入命令以空格分割

输出描述
输出失败命令数量

用例1
输入
add_rule rule_id=1 rule_index=9999
mod_rule rule_id=1 rule_index=10
del_rule rule_id=1
输出
0
说明
所有操作都成功。

用例2
输入
add_rule rule_id=1
mod_rule rule_id=1 rule_index=10
del_rule rule_id=1
输出
3
说明
add操作不包含rule_index,添加失败，后续修改和删除操作，无对应rule_id数据，也会失败。

用例3
输入
add_rule rule_id=1 rule_index=10000
输出
1
说明
rule_index超过范围