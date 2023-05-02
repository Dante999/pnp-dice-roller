#include <iostream>
#include <random>
#include <string>

struct Roll_Parameters {
    int number_of_dices{0};
    int dice_sides{0};
    int modifier{0};
};

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

Roll_Parameters parse_user_input(const std::string &input)
{
    Roll_Parameters roll_parameters;

    size_t pos_dice_sides = std::string::npos;

    pos_dice_sides = input.find_first_of('W');
    if (pos_dice_sides == std::string::npos) {
        std::cout << "Wrong format! Use format "
                     "<number-of-dices>W<dice-sides>[+,-<modifier>]! E.g. 3W10\n";
        return roll_parameters;
    }

    size_t pos_modifier = input.find_first_of('+');
    if (pos_modifier == std::string::npos)
        pos_modifier = input.find_first_of('-');

    const auto number_of_dices_str  = input.substr(0, pos_dice_sides);
    roll_parameters.number_of_dices = std::stoi(number_of_dices_str);

    if (pos_modifier != std::string::npos) {
        const auto dice_sides_str = input.substr(pos_dice_sides + 1, pos_modifier - pos_dice_sides - 1);
        const auto modifier_str   = input.substr(pos_modifier, input.length() - pos_modifier);

        roll_parameters.dice_sides = std::stoi(dice_sides_str);
        roll_parameters.modifier   = std::stoi(modifier_str);
    }
    else {
        const auto dice_sides_str  = input.substr(pos_dice_sides + 1, input.length() - pos_dice_sides);
        roll_parameters.dice_sides = std::stoi(dice_sides_str);
    }

    return roll_parameters;
}

Roll_Result roll_dice(const Roll_Parameters &roll_parameters)
{
    std::random_device                 r;
    std::default_random_engine         e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, roll_parameters.dice_sides);

    Roll_Result roll_result;

    for (int i = 0; i < roll_parameters.number_of_dices; ++i) {
        roll_result.results.emplace_back(uniform_dist(e1));
    }

    roll_result.result_modifier = roll_parameters.modifier;

    return roll_result;
}

void print_dice_result(const Roll_Result &roll_result)
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

int main(void)
{
    std::string input;

    while (input != "exit" || input != "quit") {

        input                = get_user_input();
        auto roll_parameters = parse_user_input(input);

        const auto roll_result = roll_dice(roll_parameters);

        print_dice_result(roll_result);
    }
}
