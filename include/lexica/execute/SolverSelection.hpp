#pragma once

#include <cstddef>

#include <lexica/solver/BlockType.hpp>
#include <lexica/execute/SolverType.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Solver Selection
    |--------------------------------------------------------------------------
    |
    | Represents the execution strategy chosen for a structural
    | block during solver planning.
    |
    | After block decomposition, each block is analyzed and
    | assigned the most appropriate numerical solver based on
    | its structural characteristics.
    |
    | Examples:
    |
    |     Direct Solve Block
    |         → Direct Solver
    |
    |     Nonlinear Coupled Block
    |         → Newton Solver
    |
    |     Unsupported Block
    |         → No Solver
    |
    | The resulting selections guide the execution engine and
    | determine how each block will be processed during model
    | execution.
    |
    | IMPORTANT:
    |
    | This object describes a planning decision.
    |
    | It does NOT contain solver state, numerical results,
    | convergence information, or execution data.
    |
    */

    struct SolverSelection
    {
        // Target block within the execution plan.
        std::size_t blockId{};

        // Structural classification of the block.
        BlockType blockType =
            BlockType::Unknown;

        // Solver assigned to execute the block.
        SolverType solverType =
            SolverType::None;
    };
}