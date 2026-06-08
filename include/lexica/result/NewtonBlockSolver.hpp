#pragma once

#include <lexica/result/IBlockSolver.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Newton Block Solver
    |--------------------------------------------------------------------------
    |
    | Solver implementation for structural blocks containing
    | tightly coupled nonlinear relationships.
    |
    | Unlike direct computation blocks, these subsystems cannot
    | be solved sequentially because multiple variables depend
    | on one another simultaneously.
    |
    | This solver applies Newton-Raphson iterations to drive
    | equation residuals toward zero and obtain a consistent
    | solution for the entire block.
    |
    | The Newton solver forms the primary numerical engine for
    | coupled systems within the Lexica execution pipeline.
    |
    | Typical Flow:
    |
    |     Residual Evaluation
    |             ↓
    |     Jacobian Construction
    |             ↓
    |       Linear Solve
    |             ↓
    |      Variable Update
    |             ↓
    |     Convergence Check
    |
    | IMPORTANT:
    |
    | This solver is intended for nonlinear coupled subsystems.
    |
    | Directly solvable blocks should be executed using simpler
    | and more efficient solver strategies.
    |
    */

    class NewtonBlockSolver :
        public IBlockSolver
    {
    public:

        // Solve a nonlinear coupled block.
        BlockSolveResult solve(
            const Model& model,
            const StructuralBlock& block,
            VariableVector currentValues) override;
    };
}