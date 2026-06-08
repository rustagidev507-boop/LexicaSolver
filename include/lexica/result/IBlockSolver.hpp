#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/planning/StructuralBlock.hpp>

#include <lexica/runtime/VariableVector.hpp>

#include <lexica/result/BlockSolveResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Block Solver Interface
    |--------------------------------------------------------------------------
    |
    | Common contract implemented by all block-level solver
    | strategies within Lexica.
    |
    | Once execution planning is complete, each structural block
    | is assigned a solver capable of computing the variables
    | belonging to that subsystem.
    |
    | This interface provides a uniform execution model while
    | allowing different numerical techniques to be applied to
    | different block types.
    |
    | Example Implementations:
    |
    |     DirectSolveBlockSolver
    |     NewtonSolver
    |     Future Nonlinear Solvers
    |
    | The execution engine interacts exclusively through this
    | abstraction and remains independent of specific solver
    | implementations.
    |
    | IMPORTANT:
    |
    | Implementations are responsible for solving a single
    | structural block.
    |
    | Model decomposition, solver selection, and execution
    | planning are performed by earlier stages of the pipeline.
    |
    */

    class IBlockSolver
    {
    public:

        virtual ~IBlockSolver() = default;

        // Solve a structural block using the current model state.
        virtual BlockSolveResult solve(
            const Model& model,
            const StructuralBlock& block,
            VariableVector currentValues) = 0;
    };
}