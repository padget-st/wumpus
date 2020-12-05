#pragma once
#include "Room.h"

constexpr int BATS_NUMBER = 2;

class Bat
{
private:
    const Room* pos;
public:
    Bat(const Room*);
    const Room* move(const Room*);
    const Room* position() const;
};
