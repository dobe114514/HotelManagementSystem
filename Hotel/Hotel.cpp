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
/*
用户登录  管理者登录 
	用户登录或者注册       账号username 密码password     ->查询有无该住客 
		有以下功能：
		查询房间信息  预约房间  入住房间  退房  退预约  
	管理者有以下功能：
		改房间信息  创建或删除房间  查询住客信息
*/

//数据库
//用户信息

class Users{
	std::string username; 
    std::string password; 
    std::string number;
};

class Customer{
    std::string username; 
    std::string password; 
    std::string number;
    Customer* next;

    
    
    public:

	    
    	
    	
    	//添加用户
		static bool add(const string& filename,std::string username, std::string password,std::string number){
			ifstream file(filename);	        	       
		    if (!file.is_open()) {
	            cerr << "无法读取名单" << endl;
	        }
	         
			string line;
			//跳过第一行
	        getline	(file,line);
			bool t =true;
	        while(getline(file,line)){
	        	stringstream ss(line);
	        	string one;string two,three;
	        	ss>>one>>two>>three;
	        	if(three == number){
					cout<<"已有该用户"<<endl;
					t = false;
				}
				
			}
			file.close();
			if(t){
				std::ofstream outfile(filename, std::ios::app);
				
				// 检查文件是否成功打开
				if (!outfile) {
					std::cerr << "无法打开文件！" << std::endl;
					return false;
				}

				// 向文件中追加内容
				outfile<<std::endl;
				outfile << username<<"   "<<password<<"  "<<number<<"  "<< std::endl;


				// 关闭文件
				outfile.close();
			}
            if(t){
                return true;
            }else{
                return false;
            }

		}
    	
    	//删除用户
		static void deleteOne(const string &filename, string number){
			std::string line;                    // 用于存储每一行的字符串
			std::ifstream infile(filename);    // 打开输入文件流，读取原始数据
			std::ofstream outfile("temp.txt");   // 打开输出文件流，将处理后的数据写入临时文件
			 if (!infile) {  // 检查输入文件是否成功打开
				std::cerr << "打开输入文件失败。" << std::endl;
				return ;  // 打开文件失败，退出程序
			}

			if (!outfile) {  // 检查输出文件是否成功打开
				std::cerr << "打开输出文件失败。" << std::endl;
				return ;  // 打开文件失败，退出程序
			}

			getline(infile,line);

			while(getline(infile,line)){
				if(line.find(number) == std::string::npos){
					outfile << line << std::endl;  // 将符合条件的行写入临时文件
				}
			}

			infile.close();  // 关闭输入文件
			outfile.close(); // 关闭输出文件

			// 删除原文件并重命名临时文件为原文件名
			std::remove(filename.c_str());	
			std::rename("temp.txt",filename.c_str());
		}
		
		//输出用户名 
    	static void print(string filename){

		}  		

		//删除全部用户信息
		static void deleteAll(){

		}
    	
    	


		//查询住客信息（按学号）
		static bool check(string filename,string number){
			ifstream file(filename);
			if (!file.is_open()) {
	            cerr << "无法打开文件！" << endl;
	            return false;
	        }

			string line;
			getline(file,line);

			while(getline(file,line)){
				if(line.find(number) != std::string::npos){
					return true;
				}
			}
			return false;
		}
};













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
	
	/* // 获取两个时间点之间的天数差
	static int getDifferenceInDays(const Time& t1, const Time& t2) {
	    std::tm tm1 = {};
	    tm1.tm_year = t1.year - 1900;
	    tm1.tm_mon = t1.month - 1;
	    tm1.tm_mday = t1.day;
	    tm1.tm_hour = t1.hour;
	    tm1.tm_min = t1.minute;
	    tm1.tm_sec = t1.second;
	
	    std::tm tm2 = {};
	    tm2.tm_year = t2.year - 1900;
	    tm2.tm_mon = t2.month - 1;
	    tm2.tm_mday = t2.day;
	    tm2.tm_hour = t2.hour;
	    tm2.tm_min = t2.minute;
	    tm2.tm_sec = t2.second;
	
	    std::time_t time1 = std::mktime(&tm1);
	    std::time_t time2 = std::mktime(&tm2);
	
	    // 计算两个时间点之间的秒数差，并转换为天数
	    return static_cast<int>(std::fabs(std::difftime(time2, time1)) / (60 * 60 * 24)); // 60秒 * 60分钟 * 24小时 = 1天
	}

	
    // 获取两个时间点之间的小时差（向上取整）
    static int getDifferenceInHours(const Time& t1, const Time& t2) {
        std::tm tm1 = {};
        tm1.tm_year = t1.year - 1900;
        tm1.tm_mon = t1.month - 1;
        tm1.tm_mday = t1.day;
        tm1.tm_hour = t1.hour;
        tm1.tm_min = t1.minute;
        tm1.tm_sec = t1.second;

        std::tm tm2 = {};
        tm2.tm_year = t2.year - 1900;
        tm2.tm_mon = t2.month - 1;
        tm2.tm_mday = t2.day;
        tm2.tm_hour = t2.hour;
        tm2.tm_min = t2.minute;
        tm2.tm_sec = t2.second;

        std::time_t time1 = std::mktime(&tm1);
        std::time_t time2 = std::mktime(&tm2);

        return static_cast<int>(std::ceil(std::fabs(std::difftime(time2, time1)) / 3600)); // 3600秒 = 1小时
    }

    // 输出时间
    void print() const {
        std::cout << "Time: "
                  << year << "-"
                  << std::setw(2) << std::setfill('0') << month << "-"
                  << std::setw(2) << std::setfill('0') << day << " "
                  << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << minute << ":"
                  << std::setw(2) << std::setfill('0') << second
                  << std::endl;
    } */
};





class Room {
	string RoomNumber;
    double depositMoney; // 押金费用
    Time t1; //预约开始时间
    bool yuyue; //是否预约
    int type; // 按小时为1，按日数为2
    bool full; // 是否入住
    double moneyPerDay; // 每日住宿费
    double moneyPerHour; // 每小时住宿费
    double depositPerDay; // 每日押金
    double depositPerHour; // 每小时押金
    double reservationDeposit; // 预约押金
    double totalMoney; // 所需费用
    Time t; // 入住时间

public:
     Room()
        : depositMoney(200), yuyue(false), type(1), full(false), moneyPerDay(100), moneyPerHour(10),
          depositPerDay(50), depositPerHour(5), reservationDeposit(20), totalMoney(0) {}

    /*Room(string RoomNumber, double depositMoney, bool yuyue, int type, double moneyPerDay, double moneyPerHour, double depositPerDay, double depositPerHour, double reservationDeposit)
        :RoomNumber(RoomNumber), depositMoney(depositMoney), yuyue(false), type(type), full(false), moneyPerDay(moneyPerDay), moneyPerHour(moneyPerHour),
          depositPerDay(depositPerDay), depositPerHour(depositPerHour), reservationDeposit(reservationDeposit),  totalMoney(0) {}*/

    //退预约
    static void DEreserve(string filename,string number,string room,string type) {
        ifstream file(filename);
        

		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}
        bool t = false;
		string line;
		getline(file,line);
		while(getline(file,line)){
            if(line.find(room) != string::npos && line.find("无") == string::npos)
            {   
                t = true;
            }
        }
        file.close();
        if(t){
                std::string line;                    // 用于存储每一行的字符串
                std::ifstream infile(filename);    // 打开输入文件流，读取原始数据
                std::ofstream outfile("TimeofReserveCOPY.txt");   // 打开输出文件流，将处理后的数据写入临时文件
                if (!infile) {  // 检查输入文件是否成功打开
                    std::cerr << "打开输入文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                if (!outfile) {  // 检查输出文件是否成功打开
                    std::cerr << "打开输出文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                getline(infile,line);
                outfile << line << std::endl;
                while(getline(infile,line)){
                    if(line.find(room) == std::string::npos){
                        outfile << line << std::endl;  // 将符合条件的行写入临时文件
                    }else{
                        outfile<<room<<"   "<<Time::getCurrentTime()<<"   "<<(type == "1"?"按日":"按时")<<std::endl;
                    }
                }

                infile.close();  // 关闭输入文件
                outfile.close(); // 关闭输出文件

                // 删除原文件并重命名临时文件为原文件名
                std::remove(filename.c_str());	
                std::rename("TimeofReserveCOPY.txt",filename.c_str());
            }

        
    }



    //预约
    static void reserve(string filename,string number,string room,string type) {
        ifstream file(filename);
        

		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}
        bool t = false;
		string line;
		getline(file,line);
		while(getline(file,line)){
            if(line.find(room) != string::npos && line.find("无") != string::npos)
            {   
                t = true;
            }
        }
        file.close();
        if(t){
                std::string line;                    // 用于存储每一行的字符串
                std::ifstream infile(filename);    // 打开输入文件流，读取原始数据
                std::ofstream outfile("TimeofReserveCOPY.txt");   // 打开输出文件流，将处理后的数据写入临时文件
                if (!infile) {  // 检查输入文件是否成功打开
                    std::cerr << "打开输入文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                if (!outfile) {  // 检查输出文件是否成功打开
                    std::cerr << "打开输出文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                getline(infile,line);
                outfile << line << std::endl;
                while(getline(infile,line)){
                    if(line.find(room) == std::string::npos){
                        outfile << line << std::endl;  // 将符合条件的行写入临时文件
                    }else{
                        outfile<<room<<"   "<<Time::getCurrentTime()<<"   "<<(type == "1"?"按日":"按时")<<std::endl;
                    }
                }

                infile.close();  // 关闭输入文件
                outfile.close(); // 关闭输出文件

                // 删除原文件并重命名临时文件为原文件名
                std::remove(filename.c_str());	
                std::rename("TimeofReserveCOPY.txt",filename.c_str());
            }

        
    }

    //入住
    static void in(string filename,string number,string room,string type) {
       ifstream file(filename);
        

		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}
        bool t = false;
		string line;
		getline(file,line);
		while(getline(file,line)){
            if(line.find(room) != string::npos && line.find("无") != string::npos)
            {   
                t = true;
            }
        }
        file.close();
        if(t){
                std::string line;                    // 用于存储每一行的字符串
                std::ifstream infile(filename);    // 打开输入文件流，读取原始数据
                std::ofstream outfile("TimeofInCOPY.txt");   // 打开输出文件流，将处理后的数据写入临时文件
                if (!infile) {  // 检查输入文件是否成功打开
                    std::cerr << "打开输入文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                if (!outfile) {  // 检查输出文件是否成功打开
                    std::cerr << "打开输出文件失败。" << std::endl;
                    return ;  // 打开文件失败，退出程序
                }

                getline(infile,line);
                outfile << line << std::endl;
                while(getline(infile,line)){
                    if(line.find(room) == std::string::npos){
                        outfile << line << std::endl;  // 将符合条件的行写入临时文件
                    }else{
                        outfile<<room<<"   "<<Time::getCurrentTime()<<"   "<<(type == "1"?"按日":"按时")<<std::endl;
                    }
                }

                infile.close();  // 关闭输入文件
                outfile.close(); // 关闭输出文件

                // 删除原文件并重命名临时文件为原文件名
                std::remove(filename.c_str());	
                std::rename("TimeofInCOPY.txt",filename.c_str());
            }

    }


    //显示所有房间信息
    static void scanRoom(string filename){
        ifstream file(filename);
		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}

		string line;
		getline(file,line);
		while(getline(file,line)){
            stringstream ss(line);
            string one,two,three,four,five,six,seven,eight;
            ss>>one>>two>>three>>four>>five>>six>>seven>>eight;
            cout<<"房间号："<<one<<"  是否有人入住："<<(two=="有"?"  已入住":"未入住")<<"  押金（已有人入住）："<<three
    <<"  押金（按日）："<<four<<"  押金（按小时）："<<five<<"  住宿费(按日):"<<six<<
    "  住宿费（按小时):"<<seven<<"  预约状态:"<<eight<<endl;
        }
    }




	//显示未预约/未入住房间
    static void checkRoom(string filename){
        ifstream file(filename);
		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}

		string line;
		getline(file,line);
		bool t = false;
		while(getline(file,line)){
			if(line.find("未")==std::string::npos && line.find("无")==std::string::npos){
                stringstream ss(line);
				string one,two,three,four,five,six,seven,eight;
				ss>>one>>two>>three>>four>>five>>six>>seven>>eight;
                if(two == "无" && eight == "未预约"){
                    cout<<"房间号："<<one<<"  是否有人入住："<<(two=="有"?"  已入住":"未入住")<<"  押金（已有人入住）："<<three
		<<"  押金（按日）："<<four<<"  押金（按小时）："<<five<<"  住宿费(按日):"<<six<<
		"  住宿费（按小时):"<<seven<<"  预约状态:"<<eight<<endl;
				    t = true;
                }
            }
            if(!t){
                cout<<"无空余房间"<<endl;
            }
        }
    }


    //查询房间号并输出 
    static void checkRoom(string filename, string number){
		ifstream file(filename);
		if(!file.is_open()){
			cerr<<"无法打开文件"<<endl;
			return;

		}

		string line;
		getline(file,line);
		bool t = false;
		while(getline(file,line)){
			if(line.find(number)!=std::string::npos){
				stringstream ss(line);
				string one,two,three,four,five,six,seven,eight;
				ss>>one>>two>>three>>four>>five>>six>>seven>>eight;
				if(one == number){
                    cout<<"房间号："<<one<<"  是否有人入住："<<(two=="有"?"  已入住":"未入住")<<"  押金（已有人入住）："<<three
		<<"  押金（按日）："<<four<<"  押金（按小时）："<<five<<"  住宿费(按日):"<<six<<
		"  住宿费（按小时):"<<seven<<"  预约状态:"<<eight<<endl;
				    t = true;
                }


			}
		}
		if(!t){
			cout<<"无该房间"<<endl;
		}
	}    	   	
	
    
    //读入房间信息  手动
   

    //删除房间信息  手动
	
		

    
    
};

class Administor{
	private:
		std::string username; 
		std::string password; 
		std::string number;
		Room* RoomHead;
		int RoomCount;
		Customer* CustomerHead;
		Customer* CustomerLast; 



	public:		
		void scanRoom(){
			
		}

		void checkCustomer(string number){
			
		}


		//查找有无该管理员
		static bool readAdministorFromFile(const string& filename,string number) {
	        ifstream file(filename);	        	       
		    if (!file.is_open()) {
	            cerr << "无法读取管理员名单" << endl;
	            return false;
	        }
	         
			string line;
			//跳过第一行
	        getline	(file,line);

	        while(getline(file,line)){
	        	stringstream ss(line);
	        	string one;string two,three;
	        	ss>>one>>two>>three;
	        	if(three == number){
					return true;
				}
				
			}
			return false;
		}

};
	
	
    
	
	
int main() {
    bool t = true;  // 主循环
    while (t) {
        int interact = 0;
        cout << "1管理员登陆  2住客登录  3退出" << endl;
        if (std::cin >> interact) {
        } else {
            
            std::cin.clear(); // 清除错误标志
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略当前输入行
        }
        switch (interact) {
            case 1: {
                string number;
                cout << "输入学号" << endl;
                cin >> number;
                // 查找是否存在该管理员
                if (Administor::readAdministorFromFile("administor.txt", number)) {
                    interact = 0;
                    cout << "1所有房间信息  2单一房间信息  3已住住客信息  4预约住客信息  5本日收入  6本月收入 7返回上一页面" << endl;
                    cin >> interact;
                    Room::scanRoom("room.txt");
                } else {
                    cout << "无该管理员" << endl;
                    break;
                }
                break;
            }
            case 2: {
                cout << "1登陆  2注册" << endl;
                if (std::cin >> interact) {
                } else {
                    
                    std::cin.clear(); // 清除错误标志
                    std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略当前输入行
                }
                switch (interact) {
                    case 1: {
                        string number;
                        cout << "输入学号" << endl;
                        cin >> number;
                        if (Customer::check("guest.txt", number)) {
                            cout << "已登录" << endl;
                            interact = 0;
                            cout << "1查询未入住/预约房间 2预订 3入住 4退房  5取消预约" << endl;
                           if (std::cin >> interact) {
                            } else {
                                
                                std::cin.clear(); // 清除错误标志
                                std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略当前输入行
                            }
                            switch(interact){
                                case 1:{
                                    
                                    break;
                                }
                                case 2:{
                                    Room::reserve("TimeofReserve.txt",number,"601","0");
                                    cout<<"已预订"<<endl;
                                    
                                    break;
                                }
                                case 3:{
                                    Room::in("TimeofIn.txt",number,"601","1");
                                    break;
                                }
                                case 4:{
                                    break;
                                }
                                case 5:{
                                    break;
                                } 
                            }
                        }else {
                            cout << "无该用户" << endl;
                            break;
                        }
                        break;
                    }
                    case 2: {
                        cout << "请输入你的用户名 密码 学号（不可重复）" << endl;
                        string username, password, number;
                        string a, b, c;
                        cin >> username >> password >> number;
                        cout << "再次输入验证是否正确" << endl;
                        cout << "请输入用户名" << endl;
                        cin >> a;
                        if (username == a) {
                            cout << "用户名正确" << endl;
                        } else {
                            cout << "用户名错误" << endl;
                            break;
                        }
                        cout << "请输入密码" << endl;
                        cin >> b;
                        if (password == b) {
                            cout << "密码正确" << endl;
                        } else {
                            cout << "密码错误" << endl;
                            break;
                        }
                        cout << "请输入学号" << endl;
                        cin >> c;
                        if (number == c) {
                            cout << "学号正确" << endl;
                        } else {
                            cout << "学号错误" << endl;
                            break;
                        }
                        // 注册成功，添加用户
                        if(Customer::add("guest.txt", username, password, number)){
                            cout << "注册成功！请登录" << endl;
                        }else{
                            cout<<"注册失败！"<<endl;
                        }
                        
                        break;
                    }
                    default: {
                        cout << "输入错误" << endl;
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "退出程序" << endl;
                t = false;  // 设置 t 为 false，退出循环
                break;
            }
            default: {
                cout << "输入错误" << endl;
                break;
            }
        }
    }

    return 0;
}