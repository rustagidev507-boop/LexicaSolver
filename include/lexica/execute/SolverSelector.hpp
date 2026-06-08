#pragma once

#include <vector>

#include <lexica/solver/ClassificationResult.hpp>
#include <lexica/execute/SolverSelection.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Solver Selector
    |--------------------------------------------------------------------------
    |
    | Responsible for mapping structural block classifications
    | to concrete numerical solvers.
    |
    | Once blocks have been analyzed and classified, the solver
    | selector determines how each block should be executed by
    | choosing the most appropriate solving strategy.
    |
    | Examples:
    |
    |     DirectSolve Block
    |         → Direct Solver
    |
    |     AlgebraicLoop Block
    |         → Newton Solver
    |
    | The resulting solver assignments become part of the
    | execution plan and are later consumed by the execution
    | engine.
    |
    | Typical Flow:
    |
    |     Block Classification
    |             ↓
    |     Solver Selector
    |             ↓
    |     Solver Assignments
    |             ↓
    |     Execution Engine
    |
    | IMPORTANT:
    |
    | This component performs solver selection only.
    |
    | It does NOT execute solvers, evaluate equations, or
    | perform numerical computations.
    |
    */

    class SolverSelector
    {
    public:

        // Select an execution strategy for each block.
        static std::vector<SolverSelection>
        select(
            const ClassificationResult&
                classification);
    };
}