#include "naked_groups.hpp"
#include <utility>
#include "utils.hpp"

bool NakedGroups::apply(SudokuBoard& board, Constraints& constraints){
    bool result = false;
    naked_groups.clear();

    for (int i = 0; i < board.N; ++i) {
        // Initialize vector of shared pointers to Generator objects
       std::vector<std::pair<ResettableGenerator<std::pair<std::pair<int, int>, std::set<int>>>, std::string>> cons_generators;


        cons_generators.emplace_back(
            ResettableGenerator<std::pair<std::pair<int, int>, std::set<int>>>(
                std::function<Generator<std::pair<std::pair<int, int>, std::set<int>>> ()>(
                    [i, &constraints]() { return constraints.getRowConstraints(i); }
                )
            ),
            "row"
        );

        cons_generators.emplace_back(
            ResettableGenerator<std::pair<std::pair<int, int>, std::set<int>>>(
                std::function<Generator<std::pair<std::pair<int, int>, std::set<int>>> ()>(
                    [i, &constraints]() { return constraints.getColumnConstraints(i); }
                )
            ),
            "column"
        );

        cons_generators.emplace_back(
            ResettableGenerator<std::pair<std::pair<int, int>, std::set<int>>>(
                std::function<Generator<std::pair<std::pair<int, int>, std::set<int>>> ()>(
                    [i, &constraints]() { return constraints.getBoxConstraints(i); }
                )
            ),
            "box"
        );

        for (auto& [cons, type] : cons_generators) {

            for (int group_size = 2; group_size <= 4; ++group_size) {
                std::vector<std::pair<Cell, std::set<int>>> group_candidates;

                for (const auto& [pair, candidates] : cons.generator()) {
                    if (candidates.size() <= group_size && candidates.size() >= 2){
                        group_candidates.push_back({pair, candidates});
                    }
                }
                if (!group_candidates.empty()){
                    Combinations combinations = generateCombinations(group_candidates, group_size);
                    for (const auto& combination : combinations) {
                        std::vector<std::set<int>> combined_candidates;
                        std::vector<Cell> cells;
                        for (const auto& [cell, candidates] : combination) {
                            combined_candidates.push_back(candidates);
                            cells.push_back(cell);
                        }

                        // Check if the number of unique candidates is the same as the group size
                        const auto& [valid, group] = isGroupValid(combined_candidates, group_size, cells);
                        if (valid) {
                            group_size = 5;
                            naked_groups.emplace_back(type, i+1, cells, group);
                            constraints.modifyGroup(i, type, cells, group);
                            result = true;
                        }
                    }
                }
                cons.reset();
            }
        }
    }
    

    return result;
}

void NakedGroups::print() const {
    std::cout << name() << ":\n";
    if (naked_groups.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& [type, index, cells, group] : naked_groups) {
            std::string string_to_print = "In " + type + " " + std::to_string(index) + ", "
                    "the group " + setToString(group) + " is present in cells [";
            for (size_t i = 0; i < cells.size(); ++i) {
                const auto& [row, col] = cells[i];
                string_to_print += "(" + std::to_string(row+1) + ", " + std::to_string(col+1) + ")";
                // Print a space between pairs, but not after the last pair
                if (i < cells.size() - 1) {
                    string_to_print += " ";
                }
            }
            string_to_print += "]\n";
            std::cout << string_to_print;
        }
    }
}

std::string NakedGroups::name() const{
    return "Naked Groups";
}

std::pair<bool, std::set<int>> NakedGroups::isGroupValid(const std::vector<std::set<int>>& candidates, int group_size,  std::vector<Cell> cells){
    if (candidates.size() == group_size){
        // Prepare a container to store the result
        std::set<int> union_set;

        // Iterate through the vector of sets and compute the union
        for (const auto& constraints : candidates) {
            std::set<int> temp_set;
            std::set_union(union_set.begin(), union_set.end(),
                            constraints.begin(), constraints.end(),
                            std::inserter(temp_set, temp_set.begin()));
            union_set.swap(temp_set);
        }

        if (union_set.size() == group_size && already_visited.find(std::make_pair(cells, union_set)) == already_visited.end()){
            already_visited.emplace(std::make_pair(cells, union_set));
            return {true, union_set};
        }
    }

    return {false, std::set<int>()};
}