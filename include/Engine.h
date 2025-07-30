#include "Csv.h"
#include "Portfolio.h"
#include "Global.h"
#include "MovingAverage.h"
#include "DoubleMovingAverage.h"
#include "Hodl.h"
#include "Report.h"
#include "CreateParameters.h"
#include "SelectBestParameters.h"

class Engine
{

private:

    CreateParameters createParameters_;
    ParameterList paramList_;
    ParameterInstance paramInstance_;
    SelectBestParameters selectBestParameters_;
    SelectBestTrades selectBestTrades_;
    std::string csvPath_;

    ParameterDeque ExtractBestParams()
    {
        // Extract the best parameters from the selectBestParameters_ object
        ParameterDeque bestParams = selectBestParameters_.GetBestParameters();
        for (const auto& param : bestParams) {
            PrintParameterInstance(param);
        }
        return bestParams;
    }

    void ClearBestParams()
    {
        // Clear the best parameters in the selectBestParameters_ object
        selectBestParameters_.ClearBestParameters();
    }

    void RunStrategy(const ParameterInstance& paramInstance, Strategy strategy)
    {
        // Run the strategy with the given parameters
        if (strategy == Strategy::MovingAverage) {
            MovingAverage movingAverage(paramInstance.var1.value_or(8));
            movingAverage.Main(bars);
            Report report(movingAverage.GetTrades(), movingAverage.GetHistory(), movingAverage.GetPortfolio(), movingAverage.GetStrategy());
            report.CreateReport(paramInstance);
        } else if (strategy == Strategy::DoubleMovingAverage) {
            DoubleMovingAverage doubleMovingAverage(paramInstance.var1.value_or(8), paramInstance.var2.value_or(21));
            doubleMovingAverage.Main(bars);
            Report report(doubleMovingAverage.GetTrades(), doubleMovingAverage.GetHistory(), doubleMovingAverage.GetPortfolio(), doubleMovingAverage.GetStrategy());
            report.CreateReport(paramInstance);
        }
    }

    void Initialize(const std::string& csvPath)
    {
        printf("Initializing the engine...\n");
        // Initialization code for the engine
        CsvParser csvParser;
        csvParser.parseCsv(csvPath);

    }
    void OnData()
    {
        printf("OnData...\n");

        ParameterList paramList = createParameters_.CreateMAParameterList();
        ParameterDeque bestParams_;
        TradeDeque bestTrades_;

        auto start= std::chrono::high_resolution_clock::now();

        for (auto& parameterInstance : paramList) {
            MovingAverage movingAverage(parameterInstance.var1.value_or(8));
            //printf("Strategy: Moving Average with parameters: var1=%d\n", parameterInstance.var1.value_or(8));
            movingAverage.Main(bars);
            Report movingAverageReport(movingAverage.GetTrades(),movingAverage.GetHistory(), movingAverage.GetPortfolio(), movingAverage.GetStrategy());
            //printf("----------------------------------------------------\n");
            //movingAverageReport.CreateReport();
            selectBestParameters_.IsBestParams(parameterInstance, movingAverage.GetTrades(), movingAverage.GetPortfolio());
            selectBestTrades_.IsBestTrade(movingAverage.GetTrades(), movingAverage.GetPortfolio());
        }


        for (auto& parameterInstance : ExtractBestParams()) {
            MovingAverage movingAverage(parameterInstance.var1.value_or(8));
            printf("Strategy: Moving Average with parameters(Best Parameters): var1=%d\n", parameterInstance.var1.value_or(8));
            movingAverage.Main(bars);
            Report movingAverageReport(movingAverage.GetTrades(),movingAverage.GetHistory(), movingAverage.GetPortfolio(), movingAverage.GetStrategy());
            movingAverageReport.CreateReport(parameterInstance);
            printf("----------------------------------------------------\n");
        }

        ClearBestParams();

        paramList = createParameters_.CreateDoubleMAParameterList();

        for (const auto& parameterInstance : paramList) {
            if(parameterInstance.var1 && parameterInstance.var2) {
            //printf("Strategy: Double Moving Average with parameters: var1=%d, var2=%d\n",
            //parameterInstance.var1.value_or(8), parameterInstance.var2.value_or(21));
            DoubleMovingAverage doubleMovingAverage(parameterInstance.var1.value_or(8),parameterInstance.var2.value_or(21));
            doubleMovingAverage.Main(bars);
            Report doubleMovingAverageReport(doubleMovingAverage.GetTrades(), doubleMovingAverage.GetHistory(), doubleMovingAverage.GetPortfolio(), doubleMovingAverage.GetStrategy());
            //doubleMovingAverageReport.CreateReport();
            //printf("----------------------------------------------------\n");
            selectBestParameters_.IsBestParams(parameterInstance, doubleMovingAverage.GetTrades(), doubleMovingAverage.GetPortfolio());
            selectBestTrades_.IsBestTrade(doubleMovingAverage.GetTrades(), doubleMovingAverage.GetPortfolio());
            }
        }

        for (const auto& parameterInstance : ExtractBestParams()) {
            if(parameterInstance.var1 && parameterInstance.var2) {
            printf("Strategy: Double Moving Average with parameters(Best Parameters): var1=%d, var2=%d\n",
            parameterInstance.var1.value_or(8), parameterInstance.var2.value_or(21));
            DoubleMovingAverage doubleMovingAverage(parameterInstance.var1.value_or(8),parameterInstance.var2.value_or(21));
            doubleMovingAverage.Main(bars);
            Report doubleMovingAverageReport(doubleMovingAverage.GetTrades(), doubleMovingAverage.GetHistory(), doubleMovingAverage.GetPortfolio(), doubleMovingAverage.GetStrategy());
            doubleMovingAverageReport.CreateReport(parameterInstance);
            printf("----------------------------------------------------\n");
            }
        }

        ClearBestParams();

        Hodl hodl;
        hodl.Main(bars);
        Report hodlReport(hodl.GetTrades(), hodl.GetHistory(), hodl.GetPortfolio(), hodl.GetStrategy(), paramList.front());
        hodlReport.CreateReport(paramList.front());

        ClearBestParams();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> totalDuration = end - start;
        std::cout << "Total execution time: " << totalDuration.count() << " milliseconds." << std::endl;
    }

public:

    Engine(const std::string& csvPath)
    : csvPath_(csvPath)
    { }

    void Run()
    {
        Initialize(csvPath_); // Initialize the engine
        OnData(); // Process the data and create trades
    }
};