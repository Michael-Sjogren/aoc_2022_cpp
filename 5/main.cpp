#include <fstream>
#include <string>
#include <iostream>
#include <string_view>
#include <algorithm>
#include <stack>
#include <memory>
#include <vector>
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
    getline(file,line,'\n');
    // get first line and figure out how long the first line is, 
    // this will give us an idea how many stacks should be allocated
    auto line_view = std::string_view(line.c_str(), line.length());
    int gaps = line_view.length() / 4;
    std::cout << "line gaps " << gaps << std::endl;
    int columns = ((line_view.length() - gaps) / 3);
    std::cout << "columns " << columns << std::endl;
    auto boxes = std::make_unique<std::vector<std::stack<char>>>(columns);
    file.seekg(0);
    while(getline(file,line)) {
        line_view = std::string_view(line.c_str(),line.length());
        int col = 0;
        while (line_view.length() != 0)
        {
            if (line_view[0] == '[') {
                if (line_view.length() >= 3) {
                    col += 1;
                    std::cout << line_view[1] << "(" << col << ")" << "\t";
                    line_view.remove_prefix(3);

                }
            }
            else if (line_view.length() > 0) {
                line_view.remove_prefix(1);
            }

        }
        

        std::cout << line_view  << std::endl;
    }

    file.close();
    return 0;
}

