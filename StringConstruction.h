#ifndef STRING_CONSTRUCTION_H
#define STRING_CONSTRUCTION_H

#include <string>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::unordered_map;


unordered_map<int, int> cost_cache;
string target;
int append_cost;
int clone_cost;

// Finds the largest possible prefix of target starting at `index` that matches any prefix of `target`
int findLargestClone(int index) {
    int max_length = 1;
    int current_length = 0;
    int right_index = 0;
    string right_substr = target.substr(index);

    for (int i = 0; i < index; i++) {
        if (target[i] == right_substr[right_index]) {
            current_length++;
            right_index++;
            max_length = std::max(current_length, max_length);
        } else {
            if (max_length > index - i) {
                break;
            }
            right_index = 0;
            current_length = 0;
            if (target[i] == right_substr[right_index]) {
                current_length++;
                right_index++;
            }
        }
    }
    return max_length;
}

// Recursively calculates the minimum cost to construct `target` from `index`
int calculateMinCost(int index) {
    if (index == target.size()) {
        return 0;
    }

    if (cost_cache.count(index)) {
        return cost_cache[index];
    }

    int clone_cost_at_index = clone_cost + calculateMinCost(index + findLargestClone(index));
    int append_cost_at_index = append_cost + calculateMinCost(index + 1);
    int min_cost = std::min(clone_cost_at_index, append_cost_at_index);
    
    cost_cache[index] = min_cost;
    return min_cost;
}

// Initializes the function parameters and starts the cost calculation
int stringConstruction(const string& targetString, int clone, int append) {
    cost_cache.clear();
    target = targetString;
    clone_cost = clone;
    append_cost = append;
    return calculateMinCost(0);
}

#endif // STRING_CONSTRUCTION_H
