#include <lexica/result/NewtonBlockSolver.hpp>

#include <lexica/solver/NewtonSolver.hpp>

namespace lexica
{
    BlockSolveResult
    NewtonBlockSolver::solve(
        const Model& model,
        const StructuralBlock& block,
        VariableVector currentValues)
    {
        BlockSolveResult result;

        auto newtonResult =
            NewtonSolver::solve(
                model,
                block.equations,
                block.variables,
                currentValues);

        result.solution =
            newtonResult.solution;

        result.success =
            newtonResult.converged;

        return result;
    }
}