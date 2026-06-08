#include <cmath>
#include <stdexcept>

#include <lexica/runtime/ExpressionEvaluator.hpp>

namespace lexica
{
    double
    ExpressionEvaluator::evaluate(
        const ExpressionArena& arena,
        NodeId root,
        const EvaluationContext& context)
    {
        const auto& node =
            arena.get(root);

        switch (node.kind)
        {
            //--------------------------------------------------
            // Constants
            //--------------------------------------------------

            case ExpressionKind::Constant:
            {
                return node.constantValue;
            }

            //--------------------------------------------------
            // Variables
            //--------------------------------------------------

            case ExpressionKind::Variable:
            {
                return context.variableValues[
                    node.variableId];
            }

            //--------------------------------------------------
            // Binary Operators
            //--------------------------------------------------

            case ExpressionKind::Add:
            {
                return
                    evaluate(
                        arena,
                        node.left,
                        context)
                    +
                    evaluate(
                        arena,
                        node.right,
                        context);
            }

            case ExpressionKind::Subtract:
            {
                return
                    evaluate(
                        arena,
                        node.left,
                        context)
                    -
                    evaluate(
                        arena,
                        node.right,
                        context);
            }

            case ExpressionKind::Multiply:
            {
                return
                    evaluate(
                        arena,
                        node.left,
                        context)
                    *
                    evaluate(
                        arena,
                        node.right,
                        context);
            }

            case ExpressionKind::Divide:
            {
                return
                    evaluate(
                        arena,
                        node.left,
                        context)
                    /
                    evaluate(
                        arena,
                        node.right,
                        context);
            }

            case ExpressionKind::Power:
            {
                return std::pow(
                    evaluate(
                        arena,
                        node.left,
                        context),

                    evaluate(
                        arena,
                        node.right,
                        context));
            }

            //--------------------------------------------------
            // Unary Operators
            //--------------------------------------------------

            case ExpressionKind::Negate:
            {
                return
                    -evaluate(
                        arena,
                        node.left,
                        context);
            }

            //--------------------------------------------------
            // Trigonometric
            //--------------------------------------------------

            case ExpressionKind::Sin:
            {
                return std::sin(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }

            case ExpressionKind::Cos:
            {
                return std::cos(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }

            case ExpressionKind::Tan:
            {
                return std::tan(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }

            //--------------------------------------------------
            // Functions
            //--------------------------------------------------

            case ExpressionKind::Exp:
            {
                return std::exp(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }

            case ExpressionKind::Log:
            {
                return std::log(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }

            case ExpressionKind::Sqrt:
            {
                return std::sqrt(
                    evaluate(
                        arena,
                        node.left,
                        context));
            }
        }

        throw std::runtime_error(
            "Unknown ExpressionKind");
    }
}