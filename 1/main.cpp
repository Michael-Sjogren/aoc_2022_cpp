#include <iostream>
#include <fstream>
#include <stdio.h>
#include <memory>
#include <vector>
#include <algorithm>

int main()
{
    std::string line;
    std::ifstream input("input.txt");

    int cal = 0;
    int maxCal = 0;
    auto elves = std::make_unique<std::vector<int>>();

    while (getline(input,line))
    {
        if (cal > maxCal) {
            maxCal = cal;
        }

        if (line.empty())
        {
            elves->push_back(cal);
            cal = 0;
            continue;
        }
        if (input.eof()) break;
        int num;
        try
        {
            cal += std::stoi(line);
        }
        catch (std::exception const &ex)
        {
            continue;
        }
    }

    input.close();
    std::sort(elves->begin(),elves->end(), std::greater_equal<int>());
    
    printf("\nelf #1 %d\nelf #2 %d\nelf #3 %d\nTotal top 3: %d\n\r", 
        elves->at(0),
        elves->at(1),
        elves->at(2),
        elves->at(0) + elves->at(1) + elves->at(2)
    );
    return 0;
}