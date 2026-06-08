#pragma once

#include <vector>

namespace lexica
{
    struct LinearSolveResult
    {
        std::vector<double>
            solution;

        bool success = false;
    };
}