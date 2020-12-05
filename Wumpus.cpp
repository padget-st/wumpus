#include "Wumpus.h"
#include "Random_number.h"

Wumpus::Wumpus(const Room* position) : pos{ position }
{}

void Wumpus::move()
{
	wump_dir dir{ get_direction() };
	switch (dir)
	{
	case wump_dir::left: 
		pos = pos->get_left();
		break;
	case wump_dir::right:
		pos = pos->get_right();
		break;
	case wump_dir::forward:
		pos = pos->get_forward();
		break;
	case wump_dir::stay: break;
	}
}

const Room* Wumpus::position() const
{
	return pos;
}

wump_dir get_direction()
{
	int num{ Random_number::roll(1, 4) };
	switch(num)
	{
	case 1: return wump_dir::left;
	case 2: return wump_dir::right;
	case 3: return wump_dir::forward;
	default: return wump_dir::stay;
	}
}