#include <stdio.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
// the range of section ids an elf is assigned to work in
struct SectionRange {
    int start = 0;
    int end = 0;
};


SectionRange parse_range(const std::string& line) {
    auto range = SectionRange{};
    int i = 0;
    int range_split = line.find('-');
    range.start = std::stoi(line.substr(0,range_split));
    range.end = std::stoi(line.substr(range_split+1,line.length()));
    return range;
}

std::pair<SectionRange,SectionRange> get_pair(const std::string& line) {
    SectionRange pair1;
    SectionRange pair2;
    auto mid = line.find(',');
    
    if (!mid) {
        throw std::invalid_argument("no ',' delimiter found");
    }
    pair1 = parse_range(line.substr(0,mid));
    pair2 = parse_range(line.substr(mid+1,line.length()));

    return std::make_pair(pair1,pair2);
}

bool is_overlapping(int value,int low, int high) {
    return value >= low && value <= high;
}

int main() {
    std::ifstream file("input-test.txt");
    std::string line;
    int pairsOverlapping = 0;
    while(getline(file,line)) {
        
        auto pair = get_pair(line);
        bool overlaps = 
        is_overlapping(pair.first.start,pair.second.start,pair.second.end)
        || is_overlapping(pair.second.start,pair.first.start,pair.first.end);
        printf("%d-%d,%d-%d %d\n",
            pair.first.start,
            pair.first.end,
            pair.second.start,
            pair.second.end,
            overlaps
        );
        // split pair 1 and 2

        // split and parse range startN-endN

    }

    printf("Overlapping pairs: %d\n\r",pairsOverlapping);
    return 0;
}