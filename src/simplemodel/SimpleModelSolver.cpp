#include <lexica/simplemodel/SimpleModelSolver.hpp>

#include <lexica/solver/NewtonSolver.hpp>

namespace lexica
{
    SolveResult
    SimpleModelSolver::solve(
        const Model& model,
        const BlockResult& blocks,
        VariableVector initialGuess)
    {
        SolveResult result;

        VariableVector state =
            std::move(initialGuess);

        //--------------------------------------------------
        // Solve every nonlinear block
        //--------------------------------------------------

        for (const auto& block :
             blocks.blocks)
        {
            //--------------------------------------------------
            // Skip blocks that do not contain
            // equations
            //--------------------------------------------------

            if (block.equations.empty())
            {
                continue;
            }

            auto newtonResult =
                NewtonSolver::solve(
                    model,
                    block.equations,
                    block.variables,
                    state);

            if (!newtonResult.converged)
            {
                result.values =
                    std::move(state);

                result.success =
                    false;

                return result;
            }

            state =
                std::move(
                    newtonResult.solution);
        }

        result.values =
            std::move(state);

        result.success =
            true;

        return result;
    }
}