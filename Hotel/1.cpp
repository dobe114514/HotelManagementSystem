#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 打开文件
    std::ifstream file("guest.txt");  // 这里的 "example.txt" 是你要读取的文件名

    // 检查文件是否成功打开
    if (!file) {
        std::cerr << "无法打开文件!" << std::endl;
        return 1;  // 如果文件无法打开，退出程序
    }

    std::string line;
    // 逐行读取文件内容
    while (std::getline(file, line)) {
        std::cout << line << std::endl;  // 输出每一行内容
    }

    file.close();  // 关闭文件
    return 0;
}
