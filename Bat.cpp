#include "Bat.h"
#include "Cave.h"
#include "Random_number.h"
#include <iostream>

using namespace Random_number;

Bat::Bat(const Room* position) : pos{ position }
{}

const Room* Bat::move(const Room* hunt_pos)
{
	int hunt_num{ roll(1, ROOM_LIMIT) }, bat_num{ roll(1, ROOM_LIMIT) };
	while(hunt_num == hunt_pos->get_number() && bat_num == hunt_num)
		hunt_num = roll(1, ROOM_LIMIT);
	pos = get_room(pos, bat_num);
	std::cout << "\nBat is in " << pos->get_number() << '\n';
	return get_room(hunt_pos, hunt_num);
}

const Room* Bat::position() const
{
	return pos;
}
