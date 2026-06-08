#include <lexica/runtime/JacobianEvaluator.hpp>

#include <lexica/runtime/ResidualEvaluator.hpp>

namespace lexica
{
    JacobianMatrix
    JacobianEvaluator::evaluateBlock(
        const Model& model,
        const std::vector<EquationId>& equations,
        const std::vector<VariableId>& variables,
        const EvaluationContext& context)
    {
        constexpr double h = 1e-8;

        JacobianMatrix jacobian;

        //--------------------------------------------------
        // Evaluate base residuals
        //--------------------------------------------------

        const auto baseResiduals =
            ResidualEvaluator::evaluateBlock(
                model,
                equations,
                context);

        const std::size_t equationCount =
            equations.size();

        const std::size_t variableCount =
            variables.size();

        jacobian.values.resize(
            equationCount,
            std::vector<double>(
                variableCount,
                0.0));

        //--------------------------------------------------
        // Working copy of context
        //--------------------------------------------------

        EvaluationContext perturbedContext =
            context;

        //--------------------------------------------------
        // Finite Difference Columns
        //--------------------------------------------------

        for (std::size_t column = 0;
             column < variableCount;
             ++column)
        {
            const VariableId variable =
                variables[column];

            const double originalValue =
                perturbedContext
                    .variableValues[variable];

            //--------------------------------------------------
            // Perturb variable
            //--------------------------------------------------

            perturbedContext
                .variableValues[variable]
                    += h;

            const auto perturbedResiduals =
                ResidualEvaluator::evaluateBlock(
                    model,
                    equations,
                    perturbedContext);

            //--------------------------------------------------
            // Fill Jacobian column
            //--------------------------------------------------

            for (std::size_t row = 0;
                 row < equationCount;
                 ++row)
            {
                jacobian.values[row][column] =
                    (
                        perturbedResiduals
                            .values[row]
                        -
                        baseResiduals
                            .values[row]
                    ) / h;
            }

            //--------------------------------------------------
            // Restore variable
            //--------------------------------------------------

            perturbedContext
                .variableValues[variable] =
                    originalValue;
        }

        return jacobian;
    }
}