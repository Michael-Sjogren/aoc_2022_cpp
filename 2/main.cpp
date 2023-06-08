#include <vector>
#include <stdio.h>
#include <fstream>
#include <bits/stdc++.h>
#include <map>

enum Move
{
    rock = 1,
    paper = 2,
    scissors = 3
};

enum GameResult
{
    win = 6,
    draw = 3,
    loss = 0
};


std::tuple<Move,Move> getMoves(char op, char me) {
    Move opMove;
    Move myMove; 
    switch (op) {
        case 'A':
            opMove = rock;
        break;
        case 'B':
            opMove = paper;
        break;
        case 'C':
            opMove = scissors;
        break;
        default:
        break;
    }


    switch (me) {
        case 'Y':
            myMove = paper;
        break;
        case 'X':
            myMove = rock;
        break;
        case 'Z':
            myMove = scissors;
        break;
        default:
        break;
    }

    return std::make_tuple(opMove,myMove);
}

void part1(std::ifstream &inFile)
{
    
    auto combos = std::map<std::tuple<Move,Move>, GameResult> {
        std::make_pair(std::make_tuple<Move, Move>(scissors, rock), win),
        std::make_pair(std::make_tuple<Move, Move>(rock, rock), draw),
        std::make_pair(std::make_tuple<Move, Move>(paper, rock), loss),
        
        std::make_pair(std::make_tuple<Move, Move>(scissors, paper), loss),
        std::make_pair(std::make_tuple<Move, Move>(rock, paper), win),
        std::make_pair(std::make_tuple<Move, Move>(paper, paper), draw),

        std::make_pair(std::make_tuple<Move, Move>(scissors, scissors), draw),
        std::make_pair(std::make_tuple<Move, Move>(rock, scissors), loss),
        std::make_pair(std::make_tuple<Move, Move>(paper, scissors), win),
    };
    std::string line;
    int total = 0;
    while (getline(inFile, line))
    {        
        auto tup = getMoves(line[0], line[2]);
        auto second = std::get<1>(tup);
        auto game = combos[tup];
        auto result = game + second;
        
        printf("%c %c = %d + %d = %d \n",
        line[0],
        line[2],
        second,
        game,
        result
        );
        total += result;
    }

    printf("\ntotal %d",total);
}



int main()
{

    auto file = std::ifstream("input.txt");
    part1(file);
    file.close();
}
