#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <thread>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Time {
    int year, month, day;
    int hour, minute, second;

public:
    Time() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

    Time(int y, int m, int d, int h, int min, int sec)
        : year(y), month(m), day(d), hour(h), minute(min), second(sec) {}

    Time(const Time& t)
        : year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second) {}

    // 获取当前时间
    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        // 使用 std::tm 结构体来格式化时间
        std::tm buf;
        localtime_s(&buf, &in_time_t);  // 在 Windows 下使用 localtime_s 安全版本（Linux 系统可用 localtime）

        // 使用 stringstream 来格式化时间
        std::stringstream ss;
        ss << std::put_time(&buf, "%Y-%m-%d %H:%M");  // 设定格式为 YYYY-MM-DD HH:MM

        return ss.str();
    }
};
int main(){
    std::cout<<Time::getCurrentTime();
    return 0;
}