#pragma once

#include <vector>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Evaluation Context
    |--------------------------------------------------------------------------
    |
    | Provides the numerical state required during expression
    | evaluation and residual computation.
    |
    | Evaluators operate on mathematical structure stored in the
    | model and obtain variable values through the evaluation
    | context.
    |
    | This separation allows the same model to be evaluated
    | repeatedly using different variable states throughout the
    | solving process.
    |
    | Typical Uses:
    |
    |     - Expression Evaluation
    |     - Residual Generation
    |     - Jacobian Construction
    |     - Newton Iterations
    |
    | IMPORTANT:
    |
    | This object contains runtime values only.
    |
    | It does NOT contain model structure, equations, execution
    | plans, or solver metadata.
    |
    */

    struct EvaluationContext
    {
        // Current values of model variables.
        std::vector<double>
            variableValues;
    };
}