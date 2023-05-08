#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream file1("dyydata.txt", std::ios::out);
    std::ifstream file2("dyydata.txt", std::ios::in);
    file1 << "Hello world!" << std::endl;
    file1 << "Nice to meet you!";
    std::string temp;
    file2 >> temp;
    std::cout << temp;
    file1.close();
    file2.close();
    return 0;
}