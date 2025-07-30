#include <iostream>
#include <string_view>
#include "Portfolio.h"
#include "Trade.h"
#include "SelectBestParameters.h"
#pragma once

class Report{

    public:
    Report(Trades trades, Trades history, Portfolio portfolio, Strategy strategy, ParameterInstance parameterSet)
        : trades_(trades)
        , history_(history)
        , portfolio_(portfolio)
        , strategy_(strategy)
        , parameterSet_(parameterSet)
    { }

    Report(Trades trades, Trades history, Portfolio portfolio, Strategy strategy)
        : trades_(trades)
        , history_(history)
        , portfolio_(portfolio)
        , strategy_(strategy)
    { }

    // Method to generate a report of trades made during the moving average strategy
    void CreateReport()
    {
        //LogToCSV(trades_, "Trade");
        //LogToCSV(history_, "History");
        ReportOnTerminal();
    }

    void CreateReport(ParameterInstance parameters)
    {
        LogToCSV(trades_, "Trade ", parameters);
        LogToCSV(history_, "History ", parameters);
        ReportOnTerminal(parameters);
    }

    private:
        Trades trades_;
        Trades history_;
        Portfolio portfolio_;
        Strategy strategy_;
        ParameterList paramlist_;
        ParameterInstance parameterSet_;
        std::string strategyName = std::string(to_string(strategy_));
        ParameterDeque bestParams_;
        std::string reportDirectory_ = "./reports/";  // default to current directory


        void LogToCSV(Trades trades_, std::string reportType)
        {
            std::ofstream file(reportDirectory_ + strategyName + " " + reportType + " Report.csv");
            if (!file.is_open()) {
                std::cerr << "Failed to open trades_report.csv for writing." << std::endl;
                return;
            }

            file << "Timestamp,Side,Price,Quantity,Cash\n";

            for (const auto& trade : trades_) {
                file << trade.GetTimeStamp() << ","
                    << (trade.GetSide() == Side::Buy ? "Buy" : (trade.GetSide() == Side::Sell ? "Sell" : "None")) << ","
                    << trade.GetPrice() << ","
                    << trade.GetShares() << ","
                    << portfolio_.GetCash() << "\n";
            }

            file.close();
        }

        void LogToCSV(Trades trades_, std::string reportType, ParameterInstance parameters)
        {
            std::ofstream file(reportDirectory_ + strategyName + " " + reportType + " Parameters: " + parameter_to_string(parameters) + " Report.csv");
            if (!file.is_open()) {
                std::cerr << "Failed to open trades_report.csv for writing." << std::endl;
                return;
            }

            file << "Timestamp,Side,Price,Quantity,Cash\n";

            for (const auto& trade : trades_) {
                file << trade.GetTimeStamp() << ","
                    << (trade.GetSide() == Side::Buy ? "Buy" : (trade.GetSide() == Side::Sell ? "Sell" : "None")) << ","
                    << trade.GetPrice() << ","
                    << trade.GetShares() << ","
                    << portfolio_.GetCash() << "\n";
            }

            file.close();
        }

        void ReportOnTerminal()
        {
            std::cout << "Strategy: " << strategyName << std::endl;
            std::cout << "Total Trades Made: " << trades_.size() << std::endl;
            std::cout << "Amount of Sell Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::Sell;
            }) << std::endl;
            std::cout << "Amount of Buy Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::Buy;
            }) << std::endl;
            std::cout << "Amount of None Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::None;
            }) << std::endl;
            std::cout << "Final Shares in Portfolio: " << portfolio_.GetShares() << std::endl;
            std::cout << "Final Cash in Portfolio: " << portfolio_.GetCash()<< std::endl;
            std::cout << "Final Net Worth: " << portfolio_.GetCash() + (portfolio_.GetShares() * trades_.back().GetPrice()) << std::endl;
            std::cout << "--------------------------------" << std::endl;
            printf("\n");
        }

        void ReportOnTerminal(ParameterInstance parameters)
        {
            std::cout << "Strategy: " << strategyName << std::endl;
            PrintParameterInstance(parameterSet_);
            std::cout << "Total Trades Made: " << trades_.size() << std::endl;
            std::cout << "Amount of Sell Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::Sell;
            }) << std::endl;
            std::cout << "Amount of Buy Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::Buy;
            }) << std::endl;
            std::cout << "Amount of None Trades: " << std::count_if(trades_.begin(), trades_.end(), [](const Trade& trade) {
                return trade.GetSide() == Side::None;
            }) << std::endl;
            std::cout << "Final Shares in Portfolio: " << portfolio_.GetShares() << std::endl;
            std::cout << "Final Cash in Portfolio: " << portfolio_.GetCash() << std::endl;
            std::cout << "Final Net Worth: " << portfolio_.GetCash() + (portfolio_.GetShares() * trades_.back().GetPrice()) << std::endl;
            std::cout << "--------------------------------" << std::endl;
            printf("\n");
        }


        
};