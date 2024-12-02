#include "test_interface.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

TestInterface::TestInterface(const std::string& testFile, const std::string& logPath) 
    : passedTests(0), totalTests(0) {
    logFile.open(logPath);
    loadTestCases(testFile);
    writeTestHeader();
}

TestInterface::~TestInterface() {
    writeSummary();
    if(logFile.is_open()) logFile.close();
}

void TestInterface::writeTestHeader() {
    logFile << "=================================================\n";
    logFile << "SCHMOO GAME AUTOMATED TEST SUITE\n";
    logFile << "Started at: " << getCurrentTimestamp() << "\n";
    logFile << "=================================================\n\n";
}

std::string TestInterface::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void TestInterface::loadTestCases(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open test file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        GameDialog dialog;
        std::stringstream ss(line);
        ss >> dialog.testId 
           >> dialog.elevation >> dialog.angle 
           >> dialog.expectedPosition.first >> dialog.expectedPosition.second
           >> dialog.expectedHit.first >> dialog.expectedHit.second
           >> dialog.expectedResult;
        testCases.push_back(dialog);
    }
}

void TestInterface::writeTestResult(const GameDialog& dialog, 
                                  const std::pair<double,double>& actualHit,
                                  bool result,
                                  const std::string& testResult) {
    logFile << "TEST #" << dialog.testId << "\n";
    logFile << "----------------------------------------\n";
    logFile << "Target Position: (" << dialog.expectedPosition.first 
            << "," << dialog.expectedPosition.second << ")\n";
    
    logFile << "Input Parameters:\n";
    logFile << "  Elevation: " << std::fixed << std::setprecision(2) << dialog.elevation << "°\n";
    logFile << "  Angle: " << std::fixed << std::setprecision(2) << dialog.angle << "°\n";
    
    logFile << "Expected Result:\n";
    logFile << "  Hit Position: (" << dialog.expectedHit.first 
            << "," << dialog.expectedHit.second << ")\n";
    logFile << "  Should Hit: " << (dialog.expectedResult ? "Yes" : "No") << "\n";
    
    logFile << "Actual Result:\n";
    logFile << "  Hit Position: (" << actualHit.first 
            << "," << actualHit.second << ")\n";
    logFile << "  Did Hit: " << (result ? "Yes" : "No") << "\n";
    
    logFile << "Test Result: " << testResult << "\n\n";
}

void TestInterface::writeSummary() {
    logFile << "=================================================\n";
    logFile << "TEST SUMMARY\n";
    logFile << "Finished at: " << getCurrentTimestamp() << "\n";
    logFile << "-------------------------------------------------\n";
    logFile << "Total Tests: " << totalTests << "\n";
    logFile << "Passed: " << passedTests << "\n";
    logFile << "Failed: " << (totalTests - passedTests) << "\n";
    logFile << "Success Rate: " << std::fixed << std::setprecision(2)
            << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%\n";
    logFile << "=================================================\n";
}

bool TestInterface::compareResults(const GameDialog& dialog, 
                                 double hitX, double hitY, 
                                 bool result,
                                 std::string& errorMessage) {
    const double EPSILON = 0.1;
    
    if (result != dialog.expectedResult) {
        errorMessage = "Hit result mismatch";
        return false;
    }
    
    if (std::abs(hitX - dialog.expectedHit.first) > EPSILON || 
        std::abs(hitY - dialog.expectedHit.second) > EPSILON) {
        std::stringstream ss;
        ss << "Position mismatch - Difference: ("
           << std::abs(hitX - dialog.expectedHit.first) << ", "
           << std::abs(hitY - dialog.expectedHit.second) << ")";
        errorMessage = ss.str();
        return false;
    }
    
    return true;
}

bool TestInterface::runTests() {
    totalTests = testCases.size();
    bool allPassed = true;
    
    for (const auto& dialog : testCases) {
        double hitX, hitY;
        bool result = game.makeShot(dialog.elevation, dialog.angle, hitX, hitY);
        
        std::string errorMessage;
        bool testPassed = compareResults(dialog, hitX, hitY, result, errorMessage);
        
        if (testPassed) {
            passedTests++;
            writeTestResult(dialog, {hitX, hitY}, result, "PASSED");
        } else {
            allPassed = false;
            writeTestResult(dialog, {hitX, hitY}, result, 
                          "FAILED - " + errorMessage);
        }
    }
    
    return allPassed;
}