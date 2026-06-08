#pragma once

#include <vector>

#include <lexica/solver/ExecutionStep.hpp>

namespace lexica
{
    struct SolverPlan
    {
        std::vector<
            ExecutionStep
        > steps;
    };
}