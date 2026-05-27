题目描述
9月份开学第一天，小学某班级进行班长选举活动，班级共有N个学生，每个学生最多可投3票（对同一个人只能投一票），也可以弃权不投票，大家投票时写上对应学生的名字（假设学生不存在重名，考虑到部分少数民族名字带分隔，且整体较长，同学在投票时为了方便，允许同学写全称，也可以只写其中的部分连续段，比如班级里只有22个少数民族名称带点的同学，A同学叫买买提-艾尔肯-巴图尔，B同学叫买买提-艾尔肯-库尔班，那要给A同学投票，可以写 买买提-艾尔肯-巴图尔 或者 艾尔肯-巴图尔 或者 巴图尔，但是不能写 买买、买买提-艾、肯-库尔班、肯-库这种某名字未写全的情况），学生可以把票投给自己。

得票最多的同学当选班长，如果票数相同，则按名字做字符串排序，排序靠前的当选班长。

如果选票上写的名字不合理（要求投票的名字必需是连续的，少数民族可以是连续的若干段，但要求每段名称要写全，选票上的名字需要能唯一匹配某个人），则认为是无效票，直接忽略。

如果出现原始输入总选票数超过3倍班级总人数、某位同学的得票数超过班级总人数、没有一个同学被选中这些情况，则认为选举无效，返回固定字符串 "Invalid election."。

现在投票环节已完成，进入唱票环节，请你完善代码根据投票数据，给出当选班长对应的完整名称。 方法共2个参数，第一个参数是全班同学的名称集合，第二个参数是选票数据集合。

考虑到部分语言对中文处理不太友好，名称输入统一为普通的ASCII字符，选票中少数民族名称中的连接符（⋅）改用英文横杠连接符(−)。

输入描述
第一行给出全班同学名称集合，空格分割

第二行给出选票数据集合，空格分割

输出描述
返回选举出来的班长名称，如果选举无效返回Invalid election.

用例1
输入
Zhangsan Lisi Wangwu
Zhangsan Lisi Zhangsan

输出
Zhangsan
说明
Zhangsan得2张选票，Lisi只得1张选票，Zhangsan票数更高，因此Zhangsan当选班长。

用例2
输入
Zhangsanfeng Zhangsande
Zhangsan Zhangsande Zhangsan
输出
Zhangsande
说明
虽然Zhangsan有2张选票，由于不属于班级成员，对应选票无效，因此获得1张选票的Zhangsande当选班长。

用例3
输入
maimaiti-aierken-batuer maimaiti-aierken-kuerban
batuer aierken-batuer maimaiti maimaiti-aierken-kuerban
输出
maimaiti-aierken-batuer
说明
"batuer"和"aierken-batuer"都能唯一匹配"maimaiti-aierken-batuer"，因此"maimaiti-aierken-batuer"获得2票，"maimaiti"因为有多个名字都匹配，认定为无效票。"maimaiti-aierken-kuerban"能唯一匹配，获得1票，所以得票更多的"maimaiti-aierken-batuer"当选班长