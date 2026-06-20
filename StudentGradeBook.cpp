#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>
#include <iomanip>

class Student {
private:
    std::string name;
    int age;
    std::vector<double> grades;

    static const double PASSING_AVERAGE;

public:
    Student(const std::string& studentName, int studentAge) {
        if (studentName.empty()) {
            throw std::invalid_argument("Iм'я студента не може бути порожнiм.");
        }
        if (studentAge <= 0) {
            throw std::invalid_argument("Вiк студента має бути додатним числом.");
        }
        name = studentName;
        age = studentAge;
    }

    void addGrade(double grade) {
        if (grade < 0.0 || grade > 100.0) {
            throw std::out_of_range("Оцiнка повинна бути в межах вiд 0 до 100.");
        }
        grades.push_back(grade);
    }

    double getAverageGrade() const {
        if (grades.empty()) {
            return 0.0;
        }
        double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
        return sum / static_cast<double>(grades.size());
    }

    bool isPassing() const {
        return getAverageGrade() >= PASSING_AVERAGE;
    }

    void printInfo() const {
        std::cout << "Iм'я: " << name << '\n';
        std::cout << "Вiк: " << age << '\n';

        std::cout << "Оцiнки: ";
        if (grades.empty()) {
            std::cout << "немає оцiнок";
        } else {
            std::cout << std::defaultfloat;
            for (size_t i = 0; i < grades.size(); ++i) {
                std::cout << grades[i];
                if (i + 1 < grades.size()) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << '\n';

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Середнiй бал: " << getAverageGrade() << '\n';
        std::cout << "Статус: " << (isPassing() ? "склав навчання" : "не склав навчання") << '\n';
    }

    const std::string& getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }
};

const double Student::PASSING_AVERAGE = 60.0;

int main() {
    std::vector<Student> students;
    students.emplace_back("Олена Коваленко", 20);
    students.emplace_back("Iван Петренко", 19);
    students.emplace_back("Марiя Сидоренко", 21);

    students[0].addGrade(85);
    students[0].addGrade(90);
    students[0].addGrade(78);
    students[0].addGrade(92);
    students[0].addGrade(88);

    students[1].addGrade(45);
    students[1].addGrade(50);
    students[1].addGrade(40);
    students[1].addGrade(55);
    students[1].addGrade(48);

    students[2].addGrade(60);
    students[2].addGrade(65);
    students[2].addGrade(58);
    students[2].addGrade(70);
    students[2].addGrade(62);

    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << "=== Студент " << (i + 1) << " ===\n";
        students[i].printInfo();
        std::cout << '\n';
    }

    return 0;
}
