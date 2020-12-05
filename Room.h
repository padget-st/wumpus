#pragma once

class Room
{
private:
    Room* left;
    Room* right;
    Room* forward;
    int number;
    bool hole;
public:
    Room(int, bool);
    int get_number() const;
    bool is_hole() const;
    const Room* get_left() const;
    const Room* get_right() const;
    const Room* get_forward() const;
    friend class Cave;
};
