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
using namespace std;
int Month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int timeTOtime(string t1,string t2){
    stringstream ss(t1);
    int year,month,day,hour,minute,year1,month1,day1,hour1,minute1;
    char dash1, dash2, colon;
    ss >> year >> dash1 >> month >> dash2 >> day >> hour >> colon >> minute;
    stringstream sss(t2);
    sss >> year1 >> dash1 >> month1 >> dash2 >> day1 >> hour1 >> colon >> minute1;
    int i = year;
    int Day = 0;
    int Day1 = 0,Day2 = 0;
    if(year%400 == 0 || year%4==0 ||year %100 == 0){
        Month[1] = 29;
    }else{
        Month[1] = 28;
    }
    for(int j = month;j<=12;j++){
        Day1 += Month[j-1];
    }
    Day1 -= day-1;
    if(year1%400 == 0 || year1%4==0 ||year1 %100 == 0){
        Month[1] = Month[1] + 1;
    }else{
        Month[1] = 28;
    }
    for(int j = month1;j<=12;j++){
        Day2 += Month[j-1];
    }
    Day2 -= day1-1;

    
    while(i!=year1){
        if(i%400 == 0 || i%4==0 ||i %100 == 0){
            Day += 366;
        }else{
            Day+=365;
        }
        i++;
    }
    Day = Day + Day1 - Day2;
    return Day;
}







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
	
    static int getDifferenceInDays(string filename,string number,string room){
        ifstream file(filename);
        if(!file.is_open()){
            cerr<<"无法打开文件"<<endl;
            return 0;
        }

        string line;
        getline(file,line);
        while(getline(file,line)){
            if(line.find(room) != string::npos&&line.find(number) != string::npos){
                stringstream ss(line);
                string one,two,three;
                ss>>one>>two>>three;
                string time = two + "  " + three;
                return timeTOtime(time,Time::getCurrentTime());

                
           
            }
        }
    }


};



int main(){
    
    std::cout<<Time::getDifferenceInDays("TimeofReserve.txt","2024212329","201");
    return 0;
}