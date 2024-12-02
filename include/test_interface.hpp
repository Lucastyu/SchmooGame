// include/test_interface.hpp
#pragma once
#include "schmoo.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

struct GameDialog {
    int testId;
    double elevation;
    double angle;
    std::pair<int,int> expectedPosition;
    std::pair<double,double> expectedHit;
    bool expectedResult;
};

class TestInterface {
private:
    SchmooGame game;
    std::ofstream logFile;
    std::vector<GameDialog> testCases;
    int passedTests;
    int totalTests;
    
    void writeTestHeader();
    void writeTestResult(const GameDialog& dialog, 
                        const std::pair<double,double>& actualHit,
                        bool result,
                        const std::string& testResult);
    void writeSummary();
    void loadTestCases(const std::string& filename);
    bool compareResults(const GameDialog& dialog, 
                       double hitX, double hitY, 
                       bool result,
                       std::string& errorMessage);
    std::string getCurrentTimestamp();

public:
    TestInterface(const std::string& testFile, const std::string& logPath);
    bool runTests();
    ~TestInterface();
};