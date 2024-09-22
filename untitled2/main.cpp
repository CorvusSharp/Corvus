#include <iostream>
#include <string>

// Объявляем тестовые функции
void test1_processes();
void test1_threads();
void test2();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Использование: " << argv[0] << " [processes|threads|parallel]" << std::endl;
        return 1;
    }

    std::string test = argv[1];
    if (test == "processes") {
        test1_processes(); // Для задания 1.1
    } else if (test == "threads") {
        test1_threads();   // Для задания 1.2.1
    } else if (test == "parallel") {
        test2();           // Для задания 1.2.2
    } else {
        std::cout << "Указано неверное задание." << std::endl;
        return 1;
    }
    return 0;
}
