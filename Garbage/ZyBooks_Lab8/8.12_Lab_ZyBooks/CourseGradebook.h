#ifndef COURSEGRADEBOOK_H
#define COURSEGRADEBOOK_H

#include <algorithm>
#include <tuple>
#include "Gradebook.h"


class CourseGradebook : public Gradebook 
{

protected:
    std::unordered_map<std::string, std::unordered_map<int, double>> scoresByAssignment;
    std::unordered_map<int, std::unordered_map<std::string, double>> scoresByStudent;


public:
    virtual ~CourseGradebook() 
    {
       // Your code here, if needed
    }

    std::unordered_map<int, double> GetAssignmentScores(std::string assignmentName) override 
    {
        auto it = scoresByAssignment.find(assignmentName);
        if (it == scoresByAssignment.end())
            return std::unordered_map<int, double>();

        return it->second;
    }

    double GetScore(std::string assignmentName, int studentID) override 
    {
        auto ait = scoresByAssignment.find(assignmentName);
        if (ait == scoresByAssignment.end())
            return NAN;
        auto sit = ait->second.find(studentID);
        if (sit == ait->second.end())
            return NAN;

        return sit->second;
    }

    std::vector<std::string> GetSortedAssignmentNames() override 
    {
        std::vector<std::string> names;
        names.reserve(scoresByAssignment.size());
        for (auto &p : scoresByAssignment)
            names.push_back(p.first);

        std::sort(names.begin(), names.end());
        return names;
    }

    // GetSortedStudentIDs() returns a vector with all distinct student IDs,
    // sorted in ascending order.
    std::vector<int> GetSortedStudentIDs() override 
    {
        std::vector<int> ids;
        ids.reserve(scoresByStudent.size());
        for (auto &p : scoresByStudent)
            ids.push_back(p.first);

        std::sort(ids.begin(), ids.end());
        return ids;
    }

    // GetStudentScores() gets all scores that exist in the gradebook for the
    // student whose ID equals the studentID parameter. Scores are returned as
    // an unordered_map that maps an assignment name to the student's
    // corresponding score for that assignment.
    std::unordered_map<std::string, double> GetStudentScores(int studentID) override 
    {
        auto it = scoresByStudent.find(studentID);
        if (it == scoresByStudent.end())
            return std::unordered_map<std::string, double>();

        return it->second;
    }

    void SetScore(std::string assignmentName, int studentID, double score) override {
        scoresByAssignment[assignmentName][studentID] = score;
        scoresByStudent[studentID][assignmentName] = score;
    }
};

#endif
