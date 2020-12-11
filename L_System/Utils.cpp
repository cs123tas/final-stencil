#include "L_System/Utils.h"
#include <iostream>

void addBranchChar(char character, BranchFeats characteristics, unordered_map<char, BranchFeats>& charToBranch) {
    if (charToBranch.count(character) > 0) {
        string str = "overriding previous branch characteristics for character ";
        std::cout << str.append(&character) << std::endl;
    }
    charToBranch[character] = characteristics;
}

void addProductionRule(char predecessor, vector<char> succs, unordered_map<char, vector<char>>& successors) {
    if (successors.count(predecessor) > 0) {
        string str = "overriding previous production rule for character ";
        std::cout << str.append(&predecessor) << std::endl;
    }

    successors[predecessor] = succs;
}

float randomLen() {
    return fmod((float) rand(), (l_max - l_min)) + l_min;
}

float randomAngle() {
    float abs_val = fmod((float) rand(), (alpha_max - alpha_min)) + alpha_min;

    bool pos = rand() % 2;

    if (pos) {
       return abs_val;
    } else {
        return -abs_val;
    }

}


unordered_map<char, BranchFeats> createBranchTypes() {
    unordered_map<char, BranchFeats> charToBranch;

    float len1 = randomLen();
    float wid = 2.f;
    addBranchChar('a', BranchFeats(len1, wid, 0, 0, 0), charToBranch);

    float len2 = randomLen();
    float angle2X = randomAngle();
    float angle2Y = randomAngle();
    float angle2Z = randomAngle();
    addBranchChar('b', BranchFeats(len2, START_DIAMETER, angle2X, angle2Y, angle2Z), charToBranch);

    return charToBranch;
}

unordered_map<char, vector<char>> createProductionRules() {
    unordered_map<char, vector<char>> successors;

    addProductionRule('a', {'a', 'b', 'a'}, successors);
    addProductionRule('b', {'b', 'a'}, successors);

    return successors;
}
