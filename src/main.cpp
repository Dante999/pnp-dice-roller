#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "dice.hpp"
#include "roll_instructions.hpp"

namespace {
struct Roll_Result {
    std::vector<int> results;
    int              result_modifier;
};

std::string get_user_input()
{
    std::string input;
    std::cout << ">>";
    getline(std::cin, input);

    return input;
}

Roll_Result roll_dices(const Roll_Instructions &roll_instructions)
{
    Roll_Result roll_result;

    for (const auto &dice : roll_instructions.get_dices()) {
        roll_result.results.emplace_back(dice.roll());
    }

    roll_result.result_modifier = roll_instructions.get_result_modifier();

    return roll_result;
}

void print_roll_result(const Roll_Result &roll_result)
{
    int sum = 0;

    std::string text;

    text += " [";
    for (auto val : roll_result.results) {
        text += std::to_string(val);
        text += "+";

        sum += val;
    }

    sum += roll_result.result_modifier;

    text.back() = ']';
    text += ' ';

    if (roll_result.result_modifier < 0) {
        text += std::to_string(roll_result.result_modifier);
    }
    else {
        text += "+";
        text += std::to_string(roll_result.result_modifier);
    }

    text += " = ";
    text += std::to_string(sum);

    std::cout << text << "\n\n";
}

} // namespace

int main(void)
{
    std::string input;

    while (input != "exit" && input != "quit") {

        input = get_user_input();

        auto roll_instructions = Roll_Instructions{};

        try {
            roll_instructions.parse(input);
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << '\n';
            continue;
        }

        const auto roll_result = roll_dices(roll_instructions);

        print_roll_result(roll_result);
    }
}
