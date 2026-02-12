// #include <iostream>
// #include <vector>
// struct app{
//     std::string name;
//     int pri = 0;
//     std::string start;//难点 怎么比较时间 a.用数字 b.字符串
//     std::string end;
// };

// int main(){
//     int n = 0;
//     std::cin >> n;
//     std::vector<app> input;
//     for(int i=0;i<n;i++){
//         app a;
//         std::cin >> a.name >> a.pri >> a.start >> a.end;
//         if(a.start >= a.end){
//             continue;
//         }
//         //遍历input 删除优先级低的 用什么数据结构好？
//         //a.map  b.vector+sort辅助？
//         //有没有数据结构可以按照起始时间插入 优先级队列？
//         input.push_back(a);
//     }
//     std::string target;
//     std::cin >> target;

//     return 0;
// }

    #include <iostream>
    #include <vector>
    #include <string>
    #include <sstream>
    
    // 定义App类，用于存储App的相关信息
    class App {
    public:
        std::string name; // App名称
        int priority; // App优先级
        int startTime; // App允许使用的起始时间（以分钟为单位）
        int endTime; // App允许使用的结束时间（以分钟为单位）
    
        // App类的构造函数，用于创建App对象
        App(std::string name, int priority, int startTime, int endTime)
            : name(name), priority(priority), startTime(startTime), endTime(endTime) {}
    };
    
    // 时间转换函数，将时间字符串转换为以分钟为单位的整数
    int convertTime(const std::string& time) {
        int hours, minutes;
        char colon;
        std::istringstream iss(time);
        iss >> hours >> colon >> minutes; // 将时间字符串按照":"分割并转换为小时和分钟
        return hours * 60 + minutes; // 将小时和分钟转换为分钟
    }
    
    //REVIEW 模拟方式：然后建一个准确的app数组，遍历读取，添加或者删除已有的app
    int main() {
        int n; // 读取App数量
        std::cin >> n;
    
        std::vector<App> apps; 
        //REVIEW 这里的循环和下个循环合并 但是n的复杂度不影响。
        for (int i = 0; i < n; i++) {
            // 循环读取每个App的信息，并创建App对象添加到列表中
            std::string appName;
            int appPriority, appStartTime, appEndTime;
            std::string startTimeStr, endTimeStr;
            std::cin >> appName >> appPriority >> startTimeStr >> endTimeStr;
            appStartTime = convertTime(startTimeStr);
            appEndTime = convertTime(endTimeStr);
            apps.emplace_back(appName, appPriority, appStartTime, appEndTime);
        }
    
        std::string queryTimeStr;
        std::cin >> queryTimeStr;
        int queryTime = convertTime(queryTimeStr); // 读取查询时间，并转换为分钟
        std::string appAtTime = "NA"; // 初始化查询时间对应的App名称为"NA"
    
        std::vector<App> registeredApps; // 创建已注册App列表
        //REVIEW 多维度价值，没有什么有效的排序或者数据结构来简化
        for (const App& app : apps) {
            bool canInsert = true;//REVIEW 标记是否可以插入 插入有两种情况 没有冲突/冲突但优先级最高
            std::vector<int> needDeletePosition;//REVIEW 需要删除的位置
            if (app.startTime >= app.endTime) continue; // 如果起始时间不小于结束时间，则跳过
            // 遍历已注册的App列表，检查时间冲突
            for (int i = registeredApps.size() - 1; i >= 0; --i) {
                const App& registered = registeredApps[i];
                //REVIEW 区间交集 从没有交集的反面去考虑
                if (std::max(app.startTime, registered.startTime) < std::min(app.endTime, registered.endTime)) {
                    // 如果当前App的优先级高于已注册App的优先级
                    if (app.priority > registered.priority) {
                        // 记录起冲突需要移除的位置
                        needDeletePosition.push_back(i);
                    } else {
                        // 之前注册app优先级比现在大或者相等，这个不能进行注册
                        canInsert = false;
                    }
                }
            }
            // 未有冲突情况或者优先级是最高的那个情况下
            if (canInsert) {
                registeredApps.push_back(app);
                //移除已经起冲突的注册
                for (int i = 0; i < needDeletePosition.size(); i++) {
                    registeredApps.erase(registeredApps.begin() + needDeletePosition[i]);
                }
            }
            
        }
    
        // 遍历已注册App列表，找到查询时间对应的App
        for (const App& app : registeredApps) {
            if (queryTime >= app.startTime && queryTime < app.endTime) {
                appAtTime = app.name; // 更新查询时间对应的App名称
                break; // 找到后退出循环
            }
        }
    
        std::cout << appAtTime << std::endl; // 输出查询时间对应的App名称
    
        return 0;
    }
