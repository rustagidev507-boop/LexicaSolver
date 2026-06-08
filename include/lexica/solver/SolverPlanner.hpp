#pragma once

#include <lexica/planning/ExecutionPlan.hpp>

#include <lexica/solver/ClassificationResult.hpp>

#include <lexica/solver/SolverPlan.hpp>

namespace lexica
{
    class SolverPlanner
    {
    public:

        static SolverPlan build(
            const ExecutionPlan& executionPlan,
            const ClassificationResult& classification);
    };
}