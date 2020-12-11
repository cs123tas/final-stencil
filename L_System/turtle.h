#ifndef TURTLE_H
#define TURTLE_H

#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <glm.hpp>
#include <unordered_map>
#include "ParticleGenerator/particlegenerator.h"

#include "L_System/Utils.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;

struct SegmentData {
    glm::vec4 startLoc;     // start location of the segment
    float length;           // length of the segment
    float width;            // width of segment
    glm::vec4 direction;    // direction of the segment
    glm::mat4 matrix;       // the matrix to transfer the original primitive
    int depth;              // depth of the branch
    ParticleGenerator *particleGenerator; // particle generator for this segment of the tree

    SegmentData() : particleGenerator(nullptr)
    {

    }
};

struct StackData {
    glm::vec4 loc;          // location of the turtle
    glm::vec4 direction;    // direction of the segment
    glm::mat4 matrix;       // the transform matrix to this segment
    int depth;              // depth of the branch
};

class Turtle {
public:
    Turtle();
    ~Turtle();

    void setParameters(int s, float ang, float len, float stem, float branch);

    void setUpRules();
    string createTreePattern();

    vector<pair<string, float>> interpretChar(char pred, vector<char> succs);
    vector<pair<string, float>> interpretString();

    // input is a "string" (vector of constants and parameters)
    void parse(const vector<pair<string, float>>& str);
    std::vector<SegmentData> getSegmentData();

private:
    glm::vec4 m_loc;        // location of the turtle
    glm::vec4 m_direction;  // direction of the turtle, a normalized vector
    glm::mat4 m_matrix;     // the transform matrix to this step
    float m_width;          // current width
    int m_depth;            // depth of the branch

    string m_initial;

    bool random = true;

    int size;
    float branchingAngle;
    float branchingLen;
    float stemWidth;
    float branchWidth;

    // map of character to branch characteristics
    unordered_map<char, BranchFeats> m_charToBranch;

    // production rules
    unordered_map<char, vector<char>> m_successors;

    // the stack used for branching e.g. [ ]
    // store location, direction and current matrix of the turtle
    std::stack<StackData> m_stack;

    // the list of the segments that we need to draw corresponding branches
    std::vector<SegmentData> m_segments;

};

#endif // TURTLE_H
