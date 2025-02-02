#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 定义 Student 类来表示学生信息
class Student {
public:
    std::string id;
    std::string name;
    int score;

    // 构造函数
    Student(const std::string& _id, const std::string& _name, int _score)
        : id(_id), name(_name), score(_score) {}

    // 显示学生信息的函数
    void display() const {
        std::cout << "学号: " << id << ", 姓名: " << name << ", 成绩: " << score << std::endl;
    }
};

// 定义 StudentManager 类来管理学生信息
class StudentManager {
private:
    std::vector<Student> students;

    // 检查学号是否重复
    bool isIdDuplicate(const std::string& id) const {
        for (const auto& student : students) {
            if (student.id == id) {
                return true;
            }
        }
        return false;
    }

public:
    // 从已有的三个列表初始化学生信息
    void initialize(const std::vector<std::string>& names, const std::vector<std::string>& studentIds, const std::vector<int>& scores) {
        for (size_t i = 0; i < names.size(); ++i) {
            students.emplace_back(studentIds[i], names[i], scores[i]);
        }
    }

    // 添加学生信息
    void addStudent() {
        std::string id, name;
        int score;
        while (true) {
            std::cout << "请输入学生的学号: ";
            std::cin >> id;
            if (!isIdDuplicate(id)) {
                break;
            }
            std::cout << "学号重复，请重新输入。" << std::endl;
        }
        std::cout << "请输入学生的姓名: ";
        std::cin >> name;
        std::cout << "请输入学生的成绩: ";
        std::cin >> score;
        students.emplace_back(id, name, score);
        std::cout << "学生信息添加成功。" << std::endl;
    }

    // 查询学生信息
    void queryStudent() const {
        std::string key;
        std::cout << "请输入要查询的学号或姓名: ";
        std::cin >> key;
        bool found = false;
        for (const auto& student : students) {
            if (student.id == key || student.name == key) {
                student.display();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "未找到" << std::endl;
        }
    }

    // 修改学生信息
    void modifyStudent() {
        std::string id;
        std::cout << "请输入要修改信息的学生学号: ";
        std::cin >> id;
        for (auto& student : students) {
            if (student.id == id) {
                char choice;
                std::cout << "是否修改姓名？(y/n): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    std::cout << "请输入新的姓名: ";
                    std::cin >> student.name;
                }
                std::cout << "是否修改成绩？(y/n): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    std::cout << "请输入新的成绩: ";
                    std::cin >> student.score;
                }
                std::cout << "学生信息修改成功。" << std::endl;
                return;
            }
        }
        std::cout << "未找到该学号对应的学生。" << std::endl;
    }

    // 删除学生信息
    void deleteStudent() {
        std::string id;
        std::cout << "请输入要删除的学生学号: ";
        std::cin >> id;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                std::cout << "学生信息删除成功。" << std::endl;
                return;
            }
        }
        std::cout << "未找到该学号对应的学生。" << std::endl;
    }

    // 按学号排序
    static bool compareById(const Student& a, const Student& b) {
        return a.id < b.id;
    }

    // 按成绩排序
    static bool compareByScore(const Student& a, const Student& b) {
        return a.score < b.score;
    }

    // 显示所有学生信息
    void displayAllStudents() const {
        char sortChoice;
        std::cout << "按学号排序请输入 'i'，按成绩排序请输入 's': ";
        std::cin >> sortChoice;
        std::vector<Student> sortedStudents = students;
        if (sortChoice == 'i' || sortChoice == 'I') {
            std::sort(sortedStudents.begin(), sortedStudents.end(), compareById);
        } else if (sortChoice == 's' || sortChoice == 'S') {
            std::sort(sortedStudents.begin(), sortedStudents.end(), compareByScore);
        } else {
            std::cout << "无效的排序选项，将按原始顺序显示。" << std::endl;
        }
        for (const auto& student : sortedStudents) {
            student.display();
        }
    }

    // 统计功能
    void statistics() const {
        if (students.empty()) {
            std::cout << "没有学生信息，无法进行统计。" << std::endl;
            return;
        }
        int totalScore = 0;
        int maxScore = students[0].score;
        int minScore = students[0].score;
        for (const auto& student : students) {
            totalScore += student.score;
            if (student.score > maxScore) {
                maxScore = student.score;
            }
            if (student.score < minScore) {
                minScore = student.score;
            }
        }
        double averageScore = static_cast<double>(totalScore) / students.size();
        std::cout << "全班平均成绩: " << averageScore << std::endl;
        std::cout << "全班最高分: " << maxScore << std::endl;
        std::cout << "全班最低分: " << minScore << std::endl;
    }
};

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

    // 初始化 StudentManager 并加载数据
    StudentManager manager;
    manager.initialize(names, studentIds, scores);

    int choice;
    do
    {
        std::cout << "学生信息管理系统菜单：\n" << std::endl;
        std::cout << "1. 添加学生信息" << std::endl;
        std::cout << "2. 查询学生信息" << std::endl;
        std::cout << "3. 修改学生信息" << std::endl;
        std::cout << "4. 删除学生信息" << std::endl;
        std::cout << "5. 显示所有学生信息" << std::endl;
        std::cout << "6. 统计功能" << std::endl;
        std::cout << "0. 退出" << std::endl;
        std::cout << "请输入你的选择: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.queryStudent();
                break;
            case 3:
                manager.modifyStudent();
                break;
            case 4:
                manager.deleteStudent();
                break;
            case 5:
                manager.displayAllStudents();
                break;
            case 6:
                manager.statistics();
                break;
            case 0:
                std::cout << "退出系统。" << std::endl;
                break;
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
        }
    } while (choice != 0);

    return 0;
}