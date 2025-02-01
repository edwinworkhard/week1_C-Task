#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // 定义三个向量分别存储名字、学号和成绩
    std::vector<std::string> names;
    std::vector<std::string> studentIds;
    std::vector<int> scores;

    // 打开文件
    std::ifstream file("C:\\C Code\\carlearn\\students.txt");
    if (!file.is_open()) {
        std::cerr << "无法打开文件！" << std::endl;
        return 1;
    }

    std::string line;
    // 逐行读取文件内容
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, studentId;
        int score;
        // 从每行中提取名字、学号和成绩
        if (iss >> name >> studentId >> score) {
            names.push_back(name);
            studentIds.push_back(studentId);
            scores.push_back(score);
        } else {
            std::cerr << "解析行时出错: " << line << std::endl;
        }
    }

    // 关闭文件
    file.close();

    // 输出分类结果进行验证
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout << "名字: " << names[i] << ", 学号: " << studentIds[i] << ", 成绩: " << scores[i] << std::endl;
    }

    return 0;
}