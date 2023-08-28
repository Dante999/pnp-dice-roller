#ifndef DICE_HPP
#define DICE_HPP


#include <cstddef>
#include <memory>

class Dice
{
private:
    size_t m_sides;
    
public:
    Dice(size_t sides): m_sides{sides} {}
    
    size_t roll() const;
};

#endif // DICE_HPP
