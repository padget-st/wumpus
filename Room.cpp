#include "Room.h"

Room::Room(int num, bool isHole) : number{ num }, hole{ isHole },
left{ nullptr }, right{ nullptr }, forward{ nullptr }
{}

int Room::get_number() const
{
    return number;
}

bool Room::is_hole() const
{
    return hole;
}

const Room* Room::get_left() const
{
    return left;
}

const Room* Room::get_right() const
{
    return right;
}

const Room* Room::get_forward() const
{
    return forward;
}