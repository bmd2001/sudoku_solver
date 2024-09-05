#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
#include <set>
#include "generator.hpp"


Generator<std::pair<std::pair<int, int>, int>> findUniqueElements(Generator<std::pair<std::pair<int, int>, std::set<int>>>& constraints) {
    std::map<int, std::pair<int, int>> candidates;
    std::set<int> duplicates;

    for (const auto& [pair, cons] : constraints) {
        std::map<int, std::pair<int, int>> temp_candidates = candidates;
        for (int num : cons) {
            if (candidates.count(num) == 0 && duplicates.count(num) == 0){
                temp_candidates[num] = pair;
            }
            else
            {
                temp_candidates.erase(num);
                duplicates.insert(num);
            }   
        }
        candidates = std::move(temp_candidates);
    }

    for (const auto& [num, pair] : candidates){
        co_yield {pair, num};
    }
}

#endif