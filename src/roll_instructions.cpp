#include "roll_instructions.hpp"

#include <stdexcept>

void Roll_Instructions::parse(const std::string &input)
{
    auto idx_dice_sides = input.find_first_of('W');
    if (idx_dice_sides == std::string::npos) {
        idx_dice_sides = input.find_first_of('w');
    }
    
    if (idx_dice_sides == std::string::npos) {
        throw std::invalid_argument(
            "Wrong format! Expected '<number-of-dices>W<dice-sides>[+,- <modifier>]! E.g. 3W10+3");
    }

    const auto number_of_dices_str = input.substr(0, idx_dice_sides);
    const auto number_of_dices     = std::stoi(number_of_dices_str);

    size_t idx_result_modifier = input.find_first_of('+');
    if (idx_result_modifier == std::string::npos)
        idx_result_modifier = input.find_first_of('-');

    if (idx_result_modifier != std::string::npos) {
        const auto dice_sides_str = input.substr(idx_dice_sides + 1, idx_result_modifier - idx_dice_sides - 1);
        const auto modifier_str   = input.substr(idx_result_modifier, input.length() - idx_result_modifier);

        const auto dice_sides = std::stoi(dice_sides_str);
        m_result_modifier     = std::stoi(modifier_str);

        m_dices.resize(number_of_dices, Dice(dice_sides));
    }
    else {
        const auto dice_sides_str = input.substr(idx_dice_sides + 1, input.length() - idx_dice_sides);
        const auto dice_sides     = std::stoi(dice_sides_str);

        m_result_modifier = 0;

        m_dices.resize(number_of_dices, Dice(dice_sides));
    }
}
