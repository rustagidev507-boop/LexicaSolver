#pragma once

#include <vector>

#include <lexica/core/Model.hpp>

#include <lexica/runtime/EvaluationContext.hpp>
#include <lexica/runtime/JacobianMatrix.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Jacobian Evaluator
    |--------------------------------------------------------------------------
    |
    | Computes the Jacobian matrix for a set of equations and
    | variables at the current evaluation state.
    |
    | The Jacobian captures how equation residuals change with
    | respect to variable values and provides the sensitivity
    | information required by nonlinear solvers.
    |
    | This component is a critical part of Lexica's numerical
    | solving pipeline and enables efficient solution of tightly
    | coupled systems.
    |
    | Typical Uses:
    |
    |     - Newton-Raphson Solvers
    |     - Nonlinear Block Solving
    |     - Sensitivity Analysis
    |     - Convergence Computation
    |
    | Typical Flow:
    |
    |     Equations + Variables
    |               ↓
    |      Jacobian Evaluator
    |               ↓
    |         Jacobian Matrix
    |               ↓
    |         Linear Solver
    |
    | IMPORTANT:
    |
    | This component computes sensitivities only.
    |
    | It does NOT perform residual evaluation, linear solves,
    | convergence checks, or numerical iterations.
    |
    */

    class JacobianEvaluator
    {
    public:

        // Evaluate the Jacobian for a block of equations.
        static JacobianMatrix evaluateBlock(
            const Model& model,
            const std::vector<EquationId>& equations,
            const std::vector<VariableId>& variables,
            const EvaluationContext& context);
    };
}