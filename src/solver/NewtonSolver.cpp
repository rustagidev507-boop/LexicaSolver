#include <cmath>

#include <lexica/solver/NewtonSolver.hpp>

#include <lexica/runtime/EvaluationContext.hpp>

#include <lexica/runtime/ResidualEvaluator.hpp>
#include <lexica/runtime/JacobianEvaluator.hpp>

#include <lexica/solver/LinearSystemSolver.hpp>

namespace lexica
{
    NewtonResult
    NewtonSolver::solve(
        const Model& model,
        const std::vector<EquationId>& equations,
        const std::vector<VariableId>& variables,
        VariableVector guess)
    {
        constexpr std::size_t
            maxIterations = 25;

        constexpr double
            tolerance = 1e-8;

        NewtonResult result;

        for (std::size_t iteration = 0;
             iteration < maxIterations;
             ++iteration)
        {
            //--------------------------------------------------
            // Build Context
            //--------------------------------------------------

            EvaluationContext context;

            context.variableValues =
                guess.values;

            //--------------------------------------------------
            // Residuals
            //--------------------------------------------------

            auto residuals =
                ResidualEvaluator::evaluateBlock(
                    model,
                    equations,
                    context);

            //--------------------------------------------------
            // Infinity Norm
            //--------------------------------------------------

            double maxResidual = 0.0;

            for (double value :
                 residuals.values)
            {
                maxResidual =
                    std::max(
                        maxResidual,
                        std::abs(value));
            }

            if (maxResidual < tolerance)
            {
                result.solution =
                    guess;

                result.converged =
                    true;

                result.iterations =
                    iteration;

                return result;
            }

            //--------------------------------------------------
            // Jacobian
            //--------------------------------------------------

            auto jacobian =
                JacobianEvaluator::evaluateBlock(
                    model,
                    equations,
                    variables,
                    context);

            //--------------------------------------------------
            // Newton Step
            //--------------------------------------------------

            auto linearResult =
                LinearSystemSolver::solve(
                    jacobian,
                    residuals);

            if (!linearResult.success)
            {
                return result;
            }

            //--------------------------------------------------
            // Update Variables
            //--------------------------------------------------

            for (std::size_t i = 0;
                 i < variables.size();
                 ++i)
            {
                guess.values[
                    variables[i]]
                    +=
                    linearResult.solution[i];
            }
        }

        result.solution =
            guess;

        return result;
    }
}