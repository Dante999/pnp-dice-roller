#ifndef ROLL_INSTRUCTIONS_HPP
#define ROLL_INSTRUCTIONS_HPP

#include <vector>
#include <string>

#include "dice.hpp"


class Roll_Instructions
{
private:
    std::vector<Dice> m_dices;
    int m_result_modifier{0};
    
public:
    void parse(const std::string &input);
    
    const std::vector<Dice> & get_dices() const { return m_dices; }
    int get_result_modifier() const { return m_result_modifier; }
};


#endif // ROLL_INSTRUCTIONS_HPP
