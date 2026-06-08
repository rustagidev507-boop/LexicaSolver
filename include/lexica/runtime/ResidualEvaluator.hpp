#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/runtime/EvaluationContext.hpp>
#include <lexica/runtime/ResidualVector.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Residual Evaluator
    |--------------------------------------------------------------------------
    |
    | Computes equation residuals for a model or structural block
    | using the current variable state.
    |
    | Residuals measure how far the current solution is from
    | satisfying the mathematical constraints of the system.
    |
    | A perfectly solved system produces residuals approaching
    | zero, making residual evaluation the primary mechanism for
    | assessing solution quality during numerical execution.
    |
    | This component plays a central role in nonlinear solving
    | and convergence monitoring.
    |
    | Typical Uses:
    |
    |     - Newton-Raphson Solvers
    |     - Convergence Checks
    |     - Model Validation
    |     - Numerical Diagnostics
    |
    | Typical Flow:
    |
    |     Model State
    |            ↓
    |    Residual Evaluator
    |            ↓
    |      Residual Vector
    |            ↓
    |    Jacobian / Solver
    |
    | IMPORTANT:
    |
    | This component evaluates residuals only.
    |
    | It does NOT compute Jacobians, perform linear solves,
    | update variables, or execute solver iterations.
    |
    */

    class ResidualEvaluator
    {
    public:

        // Evaluate residuals for the entire model.
        static ResidualVector evaluateModel(
            const Model& model,
            const EvaluationContext& context);

        // Evaluate residuals for a specific block.
        static ResidualVector evaluateBlock(
            const Model& model,
            const std::vector<EquationId>& equations,
            const EvaluationContext& context);
    };
}