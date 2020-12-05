#include <Cave.h>
#include "Hunter.h"
#include <iostream>

Hunter::Hunter(int ar_num, const Room* position)
    : arrows{ ar_num }, pos{ position }
{
    if(ar_num < 1)
        throw std::runtime_error("Hunter: arrows < 1");
}

void Hunter::move()
{
    std::vector<const Room*> v{ pos->get_left(), pos->get_right(), 
        pos->get_forward() };
    std::cout << "You can move into a room #: ";
    for (auto r : v)
        std::cout << r->get_number() << ' ';
    std::cout << '\n';

    int num{};
    while (true)
    {
        num = user_number();
        for (auto r : v)
            if (r->get_number() == num)
            {
                pos = r;
                return;
            }
        std::cout << "You cannot move there\n";
    }
}

void Hunter::move(const Room* r)
{
    pos = r;
}

std::vector<int> Hunter::shoot()
{
    std::string str{}, shot{};
    std::vector<int> v_s;
    const Room* temp{ pos };

    std::cout << "Enter numbers (x-x-x): \n>";
    str = get_and_parse_line();

    for (unsigned int i{}; i < str.size(); i++)
    {
        if(isdigit(str[i]))
            shot += str[i];
        if(str[i] == '-' || i == (str.size() - 1))
        {
            int r{ atoi(shot.c_str()) };
            if (temp->get_left()->get_number() == r || temp->get_right()->get_number() == r
                || temp->get_forward()->get_number() == r)
            {
                v_s.push_back(r);
                shot = "";
                temp = get_room(temp, r);
            }
            else break;
        }
    }
    if (v_s.size())
    {
        std::cout << "You shot through the rooms #: ";
        for (auto n : v_s)
            std::cout << n << ' ';
    }
    else std::cout << "You overshot";

    arrows--;
    return v_s;
}

int Hunter::arrows_num() const
{
    return arrows;
}

const Room* Hunter::position() const
{
    return pos;
}

int user_number()
{
    int num{};
    while (true)
    {
        std::cout << '>';
        std::cin >> num;
        if (!std::cin)
        {
            std::cout << "Wrong input\n";
            std::cin.clear();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return num;
    }
}

std::string get_and_parse_line()
{
    std::string str{};
    bool flag{ true };
    int count{};
    while (flag)
    {
        std::getline(std::cin, str);
        if (!isdigit(str[0]))
        {
            std::cout << "Incorrect input.\n>";
            continue;
        }
        for (unsigned int i{}; i < str.size(); i++)
        {
            if (isdigit(str[i]))
                continue;
            if (str[i] == '-' && isdigit(str[i - 1]))
                count++;
            else
            {
                std::cout << "Incorrect input.\n>";
                break;
            }
        }
        count++;
        if (count <= SHOT_RANGE)
            flag = false;
        else std::cout << "Incorrect input.\n>";      
    }
    return str;
}