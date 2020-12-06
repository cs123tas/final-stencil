﻿#include "L_System/turtle.h"
#include "glm/gtx/transform.hpp"

Turtle::Turtle() {
    m_loc = glm::vec4(0.);
    m_direction = glm::vec4(0., 1., 0., 0.);
    m_loc[3] = 1.;
    m_depth = 0;
}

Turtle::~Turtle(){
}

void Turtle::setUpRules() {

    createBranchTypes(m_charToBranch);
    createProductionRules(m_successors);
    m_initial = "";

    for (int i = 0; i < l_t; i++) {
        if (i % 3) {
            m_initial.append("b");
        } else {
           m_initial.append("a");
        }
    }
}

string Turtle::createTreePattern(string predecessor) {

    string newPattern = "";

    // replaced based on probability
    for (int i = 0; i < l_t; i++) {

        char curr = predecessor[i];
        vector<char> options = m_successors[curr];
        int index = rand() % options.size();
        char next = options[index];

        newPattern.push_back(next);
    }

    // return changed string
    return newPattern;
}

vector<pair<string, float>> interpretString(string pattern) {
    vector<pair<string, float>> output;

    return output;
}

/**
 * @brief Turtle::parse parse the given "string" (vector of commands and parameters)
 *        generated by the L system
 * @param str
 */
void Turtle::parse(const std::vector<std::pair<std::string, float>>& str) {
    // clear the cache
    m_loc = glm::vec4(0., 0., 0., 1.); // start from the origin in world space
    m_direction = glm::vec4(0., 1., 0., 0.); // along with the Y axis
    m_matrix = glm::mat4(1.); // identity matrix
    m_depth = 0;

    while(!m_stack.empty())
        m_stack.pop();
    m_segments.clear();

    for (auto pair : str) {
        std::string command = pair.first;
        if (command == F) {
            // move forward
            // new segment, need to put in the list
            SegmentData data;
            data.startLoc = m_loc;
            data.length = pair.second;
            data.matrix = m_matrix;
            data.direction = m_direction;
            data.depth = m_depth;
            m_segments.push_back(data);

            // no need to change direction
            // change the location
            m_loc += pair.second * m_direction;
            // update the matrix
            glm::mat4 translateMatrix = glm::translate(glm::vec3(pair.second * m_direction[0],
                                                       pair.second * m_direction[1],
                                                       pair.second * m_direction[2]));
            m_matrix = translateMatrix * m_matrix;
            // update depth
            m_depth += 1;

        } else if (command == f) {
            // move forward
            // no need to draw a segment

            // no need to change direction
            // change the location
            m_loc += pair.second * m_direction;
            // update the matrix
            glm::mat4 translateMatrix = glm::translate(glm::vec3(pair.second * m_direction[0],
                                                       pair.second * m_direction[1],
                                                       pair.second * m_direction[2]));
            m_matrix = translateMatrix * m_matrix;
            // update depth
            m_depth += 1;

        } else if (command == plus) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, 1, 0));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == minus) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, -1, 0));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == down) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(1, 0, 0));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == up) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(-1, 0, 0));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == left) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, 0, 1));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == right) {
            // no need to change location and depth
            glm::mat4 rotator = glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, 0, -1));
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == lbracket) {
            // Push the current state of the turtle to stack
            StackData stackData;
            stackData.loc = m_loc;
            stackData.depth = m_depth;
            stackData.matrix = m_matrix;
            stackData.direction = m_direction;
            m_stack.push(stackData);

        } else if (command == rbracket) {
            // Pop the current state of the turtle from stack
            StackData stackData = m_stack.top();
            m_stack.pop();

            m_loc = stackData.loc;
            m_depth = stackData.depth;
            m_matrix = stackData.matrix;
            m_direction = stackData.direction;
        }
    }

    // branch information is in m_segments, which can be used to draw cylinders
    return;
}

std::vector<SegmentData> Turtle::getSegmentData() {
    return m_segments;
}

