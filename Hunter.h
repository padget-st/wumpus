#pragma once
#include "Room.h"
#include <vector>
#include <string>

constexpr int ARROWS_NUMBER = 5;
constexpr int SHOT_RANGE = 3;

class Hunter
{
private:
    int arrows;
    const Room* pos;
public:
    Hunter(int, const Room*);
    void move();
    void move(const Room*);
    std::vector<int> shoot();
    int arrows_num() const;
    const Room* position() const;
};

int user_number();
std::string get_and_parse_line();