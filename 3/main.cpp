#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <memory>

enum Case
{
    upper,
    lower
};

struct Item
{
    int in_compartment_1 = 0;
    int in_compartment_2 = 0;
};

Case getCase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return upper;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return lower;
    }
    throw std::invalid_argument("Not a letter");
}



void part1()
{
    auto file = std::ifstream("input.txt");
    if (!file.is_open())
        throw std::runtime_error("Could not open file");
    std::string sack;
    auto rucksack = std::make_unique<std::unordered_map<char, Item>>();
    int total = 0;
    auto i = 0;
    while (getline(file, sack) , i++)
    {
        if (i%3 == 0) {

            rucksack->erase(rucksack->begin(),rucksack->end());
        }
        int length = sack.length();
        std::string comp_1 = sack.substr(0, length/2);
        std::string comp_2 = sack.substr(length / 2, length);
        for (char l : sack)
        {
            rucksack->insert(std::pair<char, Item>(l, {}));
        }

        for (auto i = 0; i < length / 2; i++)
        {
            char c1 = comp_1[i];
            char c2 = comp_2[i];

            auto& item1 = rucksack->at(c1);
            item1.in_compartment_1 += 1;
            rucksack->insert(std::pair<char, Item>(c1, item1));

            auto& item2 = rucksack->at(c2);
            item2.in_compartment_2 += 1;
            rucksack->insert(std::pair<char, Item>(c2, item2));
        }

        for (auto it = rucksack->begin(); it != rucksack->end(); it++)
        {
            const auto item = it->second;
            char c = it->first;
            printf("\n%c\tcomp1:%d\tcomp2:%d\n", c,item.in_compartment_1,item.in_compartment_2);

            if (item.in_compartment_1 && item.in_compartment_2 )
            {
                switch (getCase(c))
                {
                case upper:
                    total += (int)(c - 'A') + 27;
                    continue;

                case lower:
                    total += (int)(c - 'a') + 1;
                    continue;
                }
            }
        }
    }
    file.close();

    printf("\ntotal: %d", total);
}



int main()
{
    part1();
    return 0;
}
