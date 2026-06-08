#pragma once

#include <lexica/expression/ExpressionArena.hpp>

#include <lexica/runtime/EvaluationContext.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Expression Evaluator
    |--------------------------------------------------------------------------
    |
    | Evaluates mathematical expression trees and produces
    | numerical results.
    |
    | Given an expression root and the current variable state,
    | the evaluator traverses the expression tree and computes
    | its value.
    |
    | This component serves as the execution layer of Lexica's
    | expression system and is heavily used throughout the
    | numerical solving pipeline.
    |
    | Typical Uses:
    |
    |     - Residual Evaluation
    |     - Jacobian Construction
    |     - Direct Computation
    |     - Newton Iterations
    |
    | Typical Flow:
    |
    |     Expression Tree
    |             ↓
    |     Expression Evaluator
    |             ↓
    |      Numerical Value
    |
    | IMPORTANT:
    |
    | This component evaluates mathematical expressions only.
    |
    | It does NOT perform residual generation, dependency
    | analysis, solver selection, or numerical solving.
    |
    */

    class ExpressionEvaluator
    {
    public:

        // Evaluate an expression tree.
        static double evaluate(
            const ExpressionArena& arena,
            NodeId root,
            const EvaluationContext& context);
    };
}