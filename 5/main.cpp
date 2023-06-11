#include <fstream>
#include <string>
#include <stdio.h>
#include <string_view>

int main()
{
    std::ifstream file("input-test.txt");
    std::string line;
    while (getline(file, line))
    {
        
        printf("%s\n",line.c_str());
    }
    file.close();
    return 0;
}