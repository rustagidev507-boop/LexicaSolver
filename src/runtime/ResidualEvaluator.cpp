#include <lexica/runtime/ResidualEvaluator.hpp>

#include <lexica/runtime/ExpressionEvaluator.hpp>

namespace lexica
{
    ResidualVector
    ResidualEvaluator::evaluateModel(
        const Model& model,
        const EvaluationContext& context)
    {
        ResidualVector residuals;

        residuals.values.reserve(
            model.equations.size());

        for (const auto& equation :
             model.equations)
        {
            const double residual =
                ExpressionEvaluator::evaluate(
                    model.expressions,
                    equation.rootNode,
                    context);

            residuals.values.push_back(
                residual);
        }

        return residuals;
    }

    //--------------------------------------------------

    ResidualVector
    ResidualEvaluator::evaluateBlock(
        const Model& model,
        const std::vector<EquationId>& equations,
        const EvaluationContext& context)
    {
        ResidualVector residuals;

        residuals.values.reserve(
            equations.size());

        for (auto equationId :
             equations)
        {
            const auto& equation =
                model.equations[
                    equationId];

            const double residual =
                ExpressionEvaluator::evaluate(
                    model.expressions,
                    equation.rootNode,
                    context);

            residuals.values.push_back(
                residual);
        }

        return residuals;
    }
}