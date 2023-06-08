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
    int count = 0;
    void add(bool seen)
    {
        count += seen;
    }

    int total()
    {
        return count;
    }
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

int get_index_from_letter(char letter)
{
    switch (getCase(letter))
    {
    case upper:
        return letter - 'A' + 26;
    case lower:
        return letter - 'a';
    }
    return -1;
}


char get_letter_from_index(int index)
{
    if (index >= 26) {
        return 'A' + index % 26;
    }else if (index < 26) {
        return 'a' + index % 26;
    }

    printf("\n index out of range: %d" , index);
    //throw std::invalid_argument("index out of range , should be between 0 and 52");
    return 'a';
}



int get_priority_from_letter(char letter)
{
    switch (getCase(letter))
    {
    case upper:
        return letter - 'A' + 26;
    case lower:
        return letter - 'a' + 1;
    }

    return 0;
}

void part1()
{
    auto file = std::ifstream("input-test.txt");
    if (!file.is_open())
        throw std::runtime_error("Could not open file");
    std::string sack;
    auto rucksack = std::make_unique<std::unordered_map<char, Item>>();
    int size = 26 * 2;
    // alphabet holds a-z and A-Z in the other half with a count of the times that char has been seen
    int badgeOccurences[size];
    std::fill_n(badgeOccurences, size, 0);
    int total = 0;
    int i = 0;
    int groupTotal = 0;

    while (getline(file, sack))
    {
        int length = sack.length();
        // go over each letter in rucksack and add to the seen letters i the map
        for (auto j = 0; j < length; j++)
        {
            char c = sack[j];
            Item item = Item{.count = 1};
            if (rucksack->count(c))
            {
                item = rucksack->at(c);
            }
            item.add(true);
            rucksack->insert(std::pair<char, Item>(c, item));
        }
        const auto pair = std::max_element(
            rucksack->begin(), rucksack->end(),
            [](const auto &x, const auto &y)
            {
                Item itemX = x.second;
                Item itemY = y.second;
        return (itemX.total() > itemY.total()); });

        auto &item = pair->second;
        char c = pair->first;
        badgeOccurences[get_index_from_letter(c)] += 1;
        if (i % 3 == 0 && i != 0)
        {

            int max_index = 0;
            for (int k = 0; k < size; k++)
            {
                printf("\n%c(%d) ", get_letter_from_index(k),badgeOccurences[k]);
                if (badgeOccurences[k] > badgeOccurences[max_index])
                {
                    max_index = k;
                }
            }
            printf("max i: %d\n", max_index);

            char badge = get_letter_from_index(max_index);
            printf("Badge max: %c\n", badge);
            total += get_priority_from_letter(badge);
            // reset
            std::fill_n(badgeOccurences, size, 0);
        }

        printf("%s\n", sack.c_str());
        rucksack->erase(rucksack->begin(), rucksack->end());
        i += 1;
    }
    file.close();

    printf("\ntotal: %d", total);
}

int main()
{
    part1();
    return 0;
}
