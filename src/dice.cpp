#include "dice.hpp"

#include <random>

size_t Dice::roll() const
{
    std::random_device                 r;
    std::default_random_engine         e1(r());
    std::uniform_int_distribution<size_t> uniform_dist(1, m_sides);

    return uniform_dist(e1);
}
