#pragma once
#include "Bat.h"
#include "Room.h"
#include "Hunter.h"
#include "Wumpus.h"
#include <vector>

constexpr int ROOM_LIMIT = 20;
constexpr int FIRST_LEVEL_LAST_ROOM = 5;
constexpr int SECOND_LEVEL_LAST_ROOM = 15;
constexpr int HOLES_NUMBER = 2;
constexpr int ACTIVE_OBJECTS = HOLES_NUMBER + BATS_NUMBER + 2;

class Cave
{
private:
    Room* first;
    Wumpus* wumpus;
    Hunter* hunter;
    Bat* bat;
public:
    Cave();
    ~Cave();
    void start();
};

void check_danger(const Hunter* h, const Wumpus* w, const Bat* b);
bool theres_wumpus(const Hunter* h, const Wumpus* w);
bool theres_hole(const Hunter* h);
Room* init_room(int, std::vector<int>);
const Room* get_room(const Room*, int);
std::vector<int> get_rand_nums(int);
char user_choise();
