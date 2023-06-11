#include <fstream>
#include <string>
#include <iostream>
#include <string_view>


void* operator new(std::size_t size) {
    std::cout << size << " bytes allocated." << std::endl;
    return malloc(size);
}

enum State {
    GetBoxPositions,
    ParseAndMoveBox,
};

int main()
{
    std::ifstream file("input-test.txt");
    std::string line;
    State state = State::GetBoxPositions;

    while (getline(file, line))
    {
        auto line_view = std::string_view(line.c_str(), line.length());
        std::cout << line_view << std::endl;
    }
    file.close();
    return 0;
}

