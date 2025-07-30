#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Usings.h"
#include "Bar.h"
#include "BarBuilder.h"
#include "Global.h"




class CsvParser
{
    public:

/*    Time parseDate(const std::string& dateStr)
    {
        unsigned int year, month, day;
        char dash1, dash2;
        std::istringstream dateStream(dateStr);
        dateStream >> year >> dash1 >> month >> dash2 >> day;
        if (dash1 != '-' || dash2 != '-' || dateStream.fail()) {
            throw std::invalid_argument("Invalid date format");
        }
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            throw std::invalid_argument("Invalid month or day value");
        }
        return Time {std::chrono::year{static_cast<int>(year)}, std::chrono::month{static_cast<unsigned int>(month)}, std::chrono::day{static_cast<unsigned int>(day)}};
    }
*/
    void parseCsv(const std::string& filename)
    {
        DeleteFirst3RowsIfHeaderMatches(filename);
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }


        std::string line;
        while (std::getline(file, line)) 
        {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> cells;
    
            // Split the line by commas
            while (std::getline(lineStream, cell, ',')) 
            {
                cells.push_back(cell);
            }
    
            if (cells.size() != 6) 
            {
                throw std::runtime_error("Expected 6 fields per line, got " + std::to_string(cells.size()));
            }

            try {
                BarBuilder barBuilder(
                    parseDate(cells[0]), 
                    std::stof(cells[1]), 
                    std::stof(cells[2]), 
                    std::stof(cells[3]), 
                    std::stof(cells[4]), 
                    std::stof(cells[5])
                );
                // Add the built BarBuilder to the member barVectorPopulator
                Bar bar = barBuilder.Build();
                bars.push_back(bar);
                
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid data: " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range data: " << e.what() << std::endl;
            }

        }

        std::cout << "CSV file parsed successfully. Total bars: " << bars.size() << std::endl;
    }
    
    private:

    Time parseDate(const std::string& dateStr)
    {
        unsigned int year, month, day;
        char dash1, dash2;
        std::istringstream dateStream(dateStr);
        dateStream >> year >> dash1 >> month >> dash2 >> day;
        if (dash1 != '-' || dash2 != '-' || dateStream.fail()) {
            throw std::invalid_argument("Invalid date format");
        }
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            throw std::invalid_argument("Invalid month or day value");
        }
        return Time {std::chrono::year{static_cast<int>(year)}, std::chrono::month{static_cast<unsigned int>(month)}, std::chrono::day{static_cast<unsigned int>(day)}};
    }

    void DeleteFirst3RowsIfHeaderMatches(const std::string& filePath) {
        const std::string tempFilePath = "new " + filePath;

        std::ifstream inFile(filePath);
        std::ofstream outFile(tempFilePath);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "Error opening input or output file.\n";
            return;
        }

        std::string line;
        std::string expectedHeader = "Price,Close,High,Low,Open,Volume";
        bool skipLines = false;
        int lineCount = 0;

        // Peek at the first line
        if (std::getline(inFile, line)) {
            if (line.rfind(expectedHeader, 0) == 0) {
                skipLines = true;
                ++lineCount;
            } else {
                outFile << line << '\n'; // Keep first line
            }
        }

        // Read and process remaining lines
        while (std::getline(inFile, line)) {
            if (skipLines && lineCount < 3) {
                ++lineCount; // Skip next 2 lines
                continue;
            }
            outFile << line << '\n';
        }

        inFile.close();
        outFile.close();

        // Replace original file with temp file
        /*if (std::remove(filePath.c_str()) != 0) {
            std::cerr << "Error deleting original file.\n";
            return;
        }*/

        if (std::rename(tempFilePath.c_str(), filePath.c_str()) != 0) {
            std::cerr << "Error renaming temp file.\n";
        } else {
            std::cout << "First 3 lines removed (if header matched).\n";
        }
    }
    
};