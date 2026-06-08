#pragma once

#include <vector>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Jacobian Matrix
    |--------------------------------------------------------------------------
    |
    | Represents the sensitivity matrix of a system of equations
    | with respect to a set of variables.
    |
    | Each entry describes how a residual changes in response to
    | a change in a particular variable, providing the numerical
    | information required by iterative solvers.
    |
    | Jacobian matrices are generated during nonlinear solving
    | and serve as the primary input to the linear system solver.
    |
    | Typical Flow:
    |
    |     Residual Equations
    |              ↓
    |     Jacobian Evaluator
    |              ↓
    |      Jacobian Matrix
    |              ↓
    |      Linear Solver
    |
    | IMPORTANT:
    |
    | This object stores numerical sensitivities only.
    |
    | It does NOT contain equations, variable metadata,
    | convergence information, or solver state.
    |
    */

    struct JacobianMatrix
    {
        // Jacobian coefficients.
        std::vector<
            std::vector<double>
        > values;
    };
}