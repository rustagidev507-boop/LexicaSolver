#pragma once

#include <lexica/result/IBlockSolver.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Direct Solve Block Solver
    |--------------------------------------------------------------------------
    |
    | Solver implementation for blocks that can be evaluated
    | directly without iterative numerical methods.
    |
    | These blocks typically contain equations that have a clear
    | structural solution path and do not participate in coupled
    | nonlinear feedback loops.
    |
    | Direct solve blocks are the most efficient execution units
    | within the Lexica pipeline since their solutions can be
    | obtained immediately from available inputs.
    |
    | Typical Examples:
    |
    |     Area * Velocity = FlowRate
    |
    |     MassFlow * Velocity = Thrust
    |
    |     Density * Volume = Mass
    |
    | IMPORTANT:
    |
    | This solver is intended for structurally solvable blocks.
    |
    | Coupled or nonlinear subsystems should be delegated to
    | specialized iterative solvers.
    |
    */

    class DirectSolveBlockSolver :
        public IBlockSolver
    {
    public:

        // Solve a direct computation block.
        BlockSolveResult solve(
            const Model& model,
            const StructuralBlock& block,
            VariableVector currentValues) override;
    };
}