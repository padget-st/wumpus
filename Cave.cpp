#include "Cave.h"
#include "Random_number.h"
#include <iostream>

Cave::Cave() : first{ nullptr }
{
    auto rand_nums{ get_rand_nums(ACTIVE_OBJECTS) };

    first = init_room(1, rand_nums);
    Room* current{ first }, *outer{ nullptr }, *inner_first{ first };

    for (int i{ 2 }; i <= ROOM_LIMIT; i++)
    {
        current->left = init_room(i, rand_nums);
        current->left->right = current;
        current = current->left;

        if (i == FIRST_LEVEL_LAST_ROOM || i == SECOND_LEVEL_LAST_ROOM)
        {
            i++;
            current->forward = init_room(i, rand_nums);
            current->forward->forward = current;
            current->left = inner_first;
            inner_first->right = current;
            outer = current;
            current = current->forward;
            inner_first = current;
            continue;
        }

        if (i > FIRST_LEVEL_LAST_ROOM && i <= SECOND_LEVEL_LAST_ROOM && i % 2 == 0)
        {
            outer = outer->left;
            outer->forward = current;
            current->forward = outer;
            continue;
        }

        if (i > SECOND_LEVEL_LAST_ROOM)
        {
            outer = outer->left->left;
            current->forward = outer;
            outer->forward = current;
            if (i == ROOM_LIMIT)
            {
                current->left = inner_first;
                inner_first->right = current;
            }
        }
    }

    wumpus = new Wumpus(get_room(first, rand_nums[ACTIVE_OBJECTS - 1]));
    hunter = new Hunter(ARROWS_NUMBER, get_room(first, rand_nums[ACTIVE_OBJECTS - 2]));
    bat = new Bat[BATS_NUMBER]{ get_room(first, rand_nums[ACTIVE_OBJECTS - 3]), 
        get_room(first, rand_nums[ACTIVE_OBJECTS - 4]) };
}

Cave::~Cave()
{
    delete[] bat;
    delete hunter;
    delete wumpus;

    Room* temp{ nullptr };
    for (int i{ 1 }; i <= ROOM_LIMIT; i++)
    {
        temp = first;
        if (first->number == FIRST_LEVEL_LAST_ROOM
            || first->number == SECOND_LEVEL_LAST_ROOM)
            first = first->forward;
        else
            first = first->left;
        delete temp;
    }
}

void Cave::start() 
{
    std::cout << "-----------> HUNT THE WUMPUS! <------------\n\n"
        << "Find and kill the Wumpus! You only have 5 arrows.\n"
        << "Beware of holes and bats. Good luck!\n\n";

    char choise{};

    std::cout << "Now you are in the room #" << hunter->position()->get_number();
    while (hunter->arrows_num() > 0)
    {      
        if (theres_wumpus(hunter, wumpus)) return;
        if (theres_hole(hunter)) return;
        check_danger(hunter, wumpus, bat);
        std::cout << "\nMove or shoot (m/s)?: \n>";
        choise = user_choise();
        if (choise == 'm')
        {
            hunter->move();
            for (int i{}; i < BATS_NUMBER; i++)
            {
                if ((bat + i)->position() == hunter->position())
                {
                    std::cout << "Oh, no! It's a bat!";
                    hunter->move(((bat + i)->move(hunter->position())));
                    std::cout << "\nIt carried you into room #" << hunter->position()->get_number();
                    i = -1;
                }
            }
        }
        else
        {
            auto shots{ hunter->shoot() };
            for (int i{}; i < shots.size(); i++)
                if (shots[i] == wumpus->position()->get_number())
                {
                    std::cout << "\nYou killed the Wumpus!";
                    return;
                }
            wumpus->move();
        }       
    }
    std::cout << "You have no arrows...You lost";
}

Room* init_room(int r_num, std::vector<int> v)
{
    for (int i{}; i < HOLES_NUMBER; i++)
        if (r_num == v[i])
            return new Room(r_num, true);
    return new Room(r_num, false);
}

const Room* get_room(const Room* r, int num)
{
    if (!r) return nullptr;
    if (num < 1 || num > ROOM_LIMIT) return nullptr;

    while (r->get_number() != num)
    {
        if (r->get_number() < num)
        {
            if (r->get_number() == FIRST_LEVEL_LAST_ROOM
                || r->get_number() == SECOND_LEVEL_LAST_ROOM)
            {
                r = r->get_forward();
                continue;
            }
            r = r->get_left();
        }
        else if (r->get_number() > num)
        {
            if (r->get_number() == (FIRST_LEVEL_LAST_ROOM + 1)
                || r->get_number() == (SECOND_LEVEL_LAST_ROOM + 1))
            {
                r = r->get_forward();
                continue;
            }
            r = r->get_right();
        }
    }
    return r;
}

std::vector<int> get_rand_nums(int n)
{
    if (n >= ROOM_LIMIT || n < 0)
        throw std::runtime_error("Wrong value of \'n\'");

    std::vector<int> v(n);
    bool flag{ false };
    for (int i{}, num{}; i < n; i++)
    {
        num = Random_number::roll(1, 20);
        for (int j{}; j < i; j++)
        {
            if (v[j] == num)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            i--;
            flag = false;
        }
        else v[i] = num;
    }
    return v;
}

void check_danger(const Hunter* h, const Wumpus* w, const Bat* b)
{
    std::vector<const Room*> v_h{ h->position()->get_left(),
        h->position()->get_right(), h->position()->get_forward() };

    for (auto p : v_h)
        if (p == w->position())
            std::cout << "\nThe Wumpus is near!";

    for (auto p : v_h)
        if (p->is_hole())
        {
            std::cout << "\nI feel the wind";
            break;
        }

    for (auto p : v_h)
        for (int i{}; i < BATS_NUMBER; i++)
            if ((b + i)->position() == p)
            {
                std::cout << "\nI hear a bat!";
                return;
            }
}

bool theres_wumpus(const Hunter* h, const Wumpus* w)
{
    if (h->position() == w->position())
    {
        std::cout << "\nOops! The Wumpus found you!";
        return 1;
    }
    return 0;
}

bool theres_hole(const Hunter* h)
{
    if (h->position()->is_hole())
    {
        std::cout << "You fell into a hole...";
        return 1;
    }
    return 0;
}

char user_choise()
{
    char choise{};
    while (true)
    {
        std::cin >> choise;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choise = tolower(choise);
        if (choise != 'm' && choise != 's')
        {
            std::cout << "Choose the correct answer\n";
            continue;
        }
        return choise;
    }
}