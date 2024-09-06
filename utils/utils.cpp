#include "utils.hpp"
#include <sstream>

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

std::string setToString(const std::set<int>& mySet) {
    std::ostringstream oss;
    
    // Start with an opening brace
    oss << "{";
    
    // Iterate through the set and build the string
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        oss << *it;
        
        // Print a comma between elements, but not after the last element
        if (std::next(it) != mySet.end()) {
            oss << ", ";
        }
    }
    
    // End with a closing brace
    oss << "}";
    
    return oss.str();
}
