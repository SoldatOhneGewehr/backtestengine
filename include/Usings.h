#pragma once

#include <vector>
#include <chrono>
#include <string>

using Price = double;
using Cash = double;
using Time = std::chrono::year_month_day;
using Volume = double;

struct ParameterInstance
{
    std::optional<int> var1;
    std::optional<int> var2;
    std::optional<int> var3;
    std::optional<int> var4;
    std::optional<int> var5;
};

using ParameterList = std::vector<ParameterInstance>;

void PrintParameterInstance(const ParameterInstance& parameter) {
    if (parameter.var1) std::cout << "var1: " << *parameter.var1 << std::endl;
    if (parameter.var2) std::cout << "var2: " << *parameter.var2 << std::endl;
    if (parameter.var3) std::cout << "var3: " << *parameter.var3 << std::endl;
    if (parameter.var4) std::cout << "var4: " << *parameter.var4 << std::endl;
    if (parameter.var5) std::cout << "var5: " << *parameter.var5 << std::endl;
}

std::string parameter_to_string(const ParameterInstance& parameter) {
    std::string result;
    if (parameter.var1) result += "var1: " + std::to_string(*parameter.var1) + ", ";
    if (parameter.var2) result += "var2: " + std::to_string(*parameter.var2) + ", ";
    if (parameter.var3) result += "var3: " + std::to_string(*parameter.var3) + ", ";
    if (parameter.var4) result += "var4: " + std::to_string(*parameter.var4) + ", ";
    if (parameter.var5) result += "var5: " + std::to_string(*parameter.var5);
    return result;
}