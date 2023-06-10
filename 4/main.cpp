#include <stdio.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
// the range of section ids an elf is assigned to work in
struct SectionRange
{
    int start = 0;
    int end = 0;
};

SectionRange parse_range(const std::string &line)
{
    auto range = SectionRange{};
    int i = 0;
    int range_split = line.find('-');
    range.start = std::stoi(line.substr(0, range_split));
    range.end = std::stoi(line.substr(range_split + 1, line.length()));
    return range;
}

std::pair<SectionRange, SectionRange> get_pair(const std::string &line)
{
    SectionRange pair1;
    SectionRange pair2;
    auto mid = line.find(',');

    if (!mid)
    {
        throw std::invalid_argument("no ',' delimiter found");
    }
    pair1 = parse_range(line.substr(0, mid));
    pair2 = parse_range(line.substr(mid + 1, line.length()));

    return std::make_pair(pair1, pair2);
}

bool is_fully_overlapping(const SectionRange& rangeA, const SectionRange& rangeB)
{
    return rangeA.start >= rangeB.start && rangeA.end <= rangeB.end;
}

int main()
{
    std::ifstream file("input.txt");
    std::string line;
    int pairsOverlapping = 0;

    while (getline(file, line))
    {
        auto pair = get_pair(line);
        bool overlaps = is_fully_overlapping(pair.first,pair.second) || is_fully_overlapping(pair.second, pair.first);

        printf("%d-%d,%d-%d %d\n",
               pair.first.start,
               pair.first.end,
               pair.second.start,
               pair.second.end,
               overlaps);
        pairsOverlapping += 1 ? overlaps : 0;
    }
    file.close();
    printf("Overlapping pairs: %d\n\r", pairsOverlapping);
    return 0;
}