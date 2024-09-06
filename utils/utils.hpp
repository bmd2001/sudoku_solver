#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
#include <set>
#include "generator.hpp"

Generator<std::pair<std::pair<int, int>, int>> findUniqueElements(Generator<std::pair<std::pair<int, int>, std::set<int>>>& constraints);
std::string setToString(const std::set<int>& mySet);

template <typename T>
std::vector<std::vector<T>> generateCombinations(const std::vector<T>& elements, int k) {
    std::vector<std::vector<T>> combinations;
    if (k <= elements.size()) {
        std::vector<bool> mask(elements.size(), false);
        std::fill(mask.begin(), mask.begin() + k, true);
        do {
            std::vector<T> combination;
            for (size_t i = 0; i < mask.size(); ++i) {
                if (mask[i]) {
                    combination.push_back(elements[i]);
                }
            }
            combinations.push_back(combination);
        } while (std::prev_permutation(mask.begin(), mask.end()));
    }
    return combinations;
}

#endif