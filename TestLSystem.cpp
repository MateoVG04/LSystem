#include <fstream> // For file operations
#include <iostream>
#include "catch2/catch.hpp"

#include <unordered_set>
#include <vector>
#include "LSystem/LSystem.h"


TEST_CASE("LSystem Construction Verification") {
    using StringType = std::string;

    const std::vector<StringType> axiom = {"f"};
    std::unordered_set<Production<StringType>> productions{
            Production<StringType>("f", {"o", "o"})
    };

    const std::unordered_set<StringType> alphabet{"f", "o"};

    LSystemInterpreter<StringType> lsys_interpreter = LSystemInterpreter(axiom, productions, alphabet);
}

TEST_CASE("Production Application in 1 it") {
    using StringType = std::string;

    const std::vector<StringType> base_case = {"f"};
    std::unordered_set<Production<StringType>> rule_set{
            Production<StringType>("f", {"f", "o", "o"})
    };
    const std::unordered_set<StringType> alphabet{"f", "o"};

    LSystemInterpreter<StringType> lsys_interpreter = LSystemInterpreter(base_case, rule_set, alphabet);
    std::vector<std::vector<StringType>> outcomes(1);

    std::generate(outcomes.begin(), outcomes.end(), lsys_interpreter);

    const std::vector<StringType> expected_outcome{"f", "o", "o"};
    CHECK(expected_outcome == outcomes.at(0));
}


TEST_CASE("Verify Valid Production Rules") {
    using StringType = std::string;

    const auto rule_invalid = Production<StringType>("n", {"n", "o"});
    const auto rule_semi_invalid_1 = Production<StringType>("j", {"n", "o"});
    const auto rule_semi_invalid_2 = Production<StringType>("n", {"j", "a"});
    const auto rule_valid = Production<StringType>("j", {"a", "a"});
    const std::unordered_set<StringType> alphabet{"j", "a"};

    CHECK(!isValidProduction(rule_invalid, alphabet));
    CHECK(!isValidProduction(rule_semi_invalid_1, alphabet));
    CHECK(!isValidProduction(rule_semi_invalid_2, alphabet));
    CHECK(isValidProduction(rule_valid, alphabet));
}

TEST_CASE("Ten Iteration Check") {
    using StringType = std::string;

    const std::vector<StringType> starting_point = {"f"};
    std::unordered_set<Production<StringType>> production_rules{
            Production<StringType>("f", {"f", "o", "o"})
    };
    const std::unordered_set<StringType> symbol_catalog{"f", "o"};

    LSystemInterpreter<StringType> lsys_analyzer = LSystemInterpreter(starting_point, production_rules, symbol_catalog);
    std::vector<std::vector<StringType>> test_results(5);

    std::generate(test_results.begin(), test_results.end(), lsys_analyzer);

    const std::vector<StringType> anticipated_result{"f", "o", "o", "o", "o", "o", "o", "o", "o", "o", "o"};
    CHECK(anticipated_result == test_results.at(4));
}

TEST_CASE("Complex Production Patterns Test") {
    using StringType = std::string;

    const std::vector<StringType> axiom_pattern = {"a", "b", "a"};
    std::unordered_set<Production<StringType>> production_rules{
            Production<StringType>("a", {"a", "b"}),
            Production<StringType>("b", {"a"})
    };
    const std::unordered_set<StringType> valid_symbols{"a", "b"};

    LSystemInterpreter<StringType> lsys_processor = LSystemInterpreter(axiom_pattern, production_rules, valid_symbols);
    std::vector<std::vector<StringType>> outcome_series(1);

    std::generate(outcome_series.begin(), outcome_series.end(), lsys_processor);

    const std::vector<StringType> expected_series{"a", "b", "a", "a", "b"};
    CHECK(expected_series == outcome_series.at(0));
}

TEST_CASE("Algae Growth Simulation Through Iterations") {
    using StringType = std::string;

    const std::vector<StringType> axiom = {"a"};
    std::unordered_set<Production<StringType>> production_set{
            Production<StringType>("a", {"a", "b"}),
            Production<StringType>("b", {"a"})
    };
    const std::unordered_set<StringType> symbol_pool{"a", "b"};

    LSystemInterpreter<StringType> algae_simulator = LSystemInterpreter(axiom, production_set, symbol_pool);
    std::vector<std::vector<StringType>> growth_results(5);

    std::generate(growth_results.begin(), growth_results.end(), algae_simulator);

    const std::vector<StringType> growth_phase_one{"a", "b"};
    const std::vector<StringType> growth_phase_two{"a", "b", "a"};
    const std::vector<StringType> growth_phase_three{"a", "b", "a", "a", "b"};
    const std::vector<StringType> growth_phase_four{"a", "b", "a", "a", "b", "a", "b", "a"};
    const std::vector<StringType> growth_phase_five{"a", "b", "a", "a", "b", "a", "b", "a", "a", "b", "a", "a", "b"};
    CHECK(growth_phase_one == growth_results.at(0));
    CHECK(growth_phase_two == growth_results.at(1));
    CHECK(growth_phase_three == growth_results.at(2));
    CHECK(growth_phase_four == growth_results.at(3));
    CHECK(growth_phase_five == growth_results.at(4));
}

TEST_CASE("Different Data Type Test - Characters") {
    using CharType = char;

    const std::vector<CharType> base_case = {'a', 'b', 'a'};
    std::unordered_set<Production<CharType>> rule_set{
            Production<CharType>('a', {'a', 'b'}),
            Production<CharType>('b', {'a'})
    };
    const std::unordered_set<CharType> valid_chars{'a', 'b'};

    LSystemInterpreter<CharType> char_interpreter = LSystemInterpreter(base_case, rule_set, valid_chars);
    std::vector<std::vector<CharType>> char_results(3);

    std::generate(char_results.begin(), char_results.end(), char_interpreter);

    const std::vector<CharType> expected_first_step{'a', 'b', 'a', 'a', 'b'};
    const std::vector<CharType> expected_second_step{'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a'};
    const std::vector<CharType> expected_third_step{'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'a', 'b', 'a', 'a', 'b'};
    CHECK(expected_first_step == char_results.at(0));
    CHECK(expected_second_step == char_results.at(1));
    CHECK(expected_third_step == char_results.at(2));
}

TEST_CASE("Write to file"){
    std::vector<char> axiom = {'X'}; // Example axiom
    std::unordered_set<char> alphabet = {'F', '+', '-','[',']','X'};
    //std::unordered_set<Production<char>> productions;
    std::unordered_set<Production<char>> productions{
            Production<char>('X', {'F', '[', '+', 'X', ']','[','-','X',']','F','X'}),
            Production<char>('F', {'F','F'})
    };

//    std::unordered_set<Production<char>> productions{
//            Production<char>('X', {'F', '-', '[', '[', 'X',']','+','X',']','+','F', '[', '+', 'F','X',']',
//                                   '-','X'}),
//            Production<char>('F', {'F','F'})
//    };

    //productions.insert(Production<char>('F', {'F', '[', '-', 'F', ']','[','+','F',']'}));

    int iterations = 5;

    LSystemInterpreter<char> lsystem(axiom, productions, alphabet);

    for (int i = 0; i < iterations; ++i) {
        lsystem();
    }

    std::vector<char> final_sequence = lsystem.getCurrentState();


    std::ofstream outfile("C:\\Users\\Mateo\\CLionProjects\\Ba2S1_Data_Structures\\7_Project\\outputFile\\lsystem_output.txt");
    for (char symbol : final_sequence) {
        outfile << symbol;
    }
    outfile.close();
}



