#include <lexica/solver/SolverPlanner.hpp>

namespace lexica
{
    SolverPlan
    SolverPlanner::build(
        const ExecutionPlan& executionPlan,
        const ClassificationResult& classification)
    {
        SolverPlan plan;

        plan.steps.reserve(
            executionPlan.orderedBlocks.size());

        for (auto blockId :
             executionPlan.orderedBlocks)
        {
            ExecutionStep step;

            step.blockId =
                blockId;

            step.blockType =
                classification.blocks[
                    blockId].type;

            plan.steps.push_back(
                std::move(step));
        }

        return plan;
    }
}