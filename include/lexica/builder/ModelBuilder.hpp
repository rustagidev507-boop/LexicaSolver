#pragma once

#include <initializer_list>
#include <string_view>

#include <lexica/core/Model.hpp>

#include <lexica/builder/ExpressionHandle.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Model Builder
    |--------------------------------------------------------------------------
    |
    | Primary entry point for constructing equation-based models
    | within Lexica.
    |
    | The builder provides a high-level interface for creating
    | variables, mathematical expressions, and equations while
    | hiding the underlying model representation.
    |
    | Typical Flow:
    |
    |     Create Variables
    |             ↓
    |     Build Expressions
    |             ↓
    |     Define Equations
    |             ↓
    |     Build Model
    |
    | The resulting model becomes the input to structural
    | analysis, execution planning, and numerical solving.
    |
    | IMPORTANT:
    |
    | ModelBuilder is responsible for model construction only.
    |
    | It does NOT perform:
    |
    |     - Structural Analysis
    |     - Dependency Discovery
    |     - Solver Selection
    |     - Numerical Execution
    |
    | Those responsibilities belong to later stages of the
    | Lexica pipeline.
    |
    */

    class ModelBuilder
    {
    public:

        //==================================================
        // Variables
        //==================================================

        // Create an unknown variable.
        VariableId variable(
            std::string_view name);

        // Create a variable with an initial value.
        VariableId variable(
            std::string_view name,
            Scalar value);

        //==================================================
        // Expression Construction
        //==================================================

        // Variable reference.
        ExpressionHandle var(
            VariableId variable);

        // Constant value.
        ExpressionHandle constant(
            Scalar value);

        // Binary Operations

        ExpressionHandle add(
            ExpressionHandle lhs,
            ExpressionHandle rhs);

        ExpressionHandle subtract(
            ExpressionHandle lhs,
            ExpressionHandle rhs);

        ExpressionHandle multiply(
            ExpressionHandle lhs,
            ExpressionHandle rhs);

        ExpressionHandle divide(
            ExpressionHandle lhs,
            ExpressionHandle rhs);

        ExpressionHandle power(
            ExpressionHandle lhs,
            ExpressionHandle rhs);

        // Unary Operations

        ExpressionHandle negate(
            ExpressionHandle operand);

        ExpressionHandle sin(
            ExpressionHandle operand);

        ExpressionHandle cos(
            ExpressionHandle operand);

        ExpressionHandle exp(
            ExpressionHandle operand);

        ExpressionHandle log(
            ExpressionHandle operand);

        ExpressionHandle sqrt(
            ExpressionHandle operand);

        //==================================================
        // Equations
        //==================================================

        // Register a model equation.
        EquationId equation(
            std::string_view name,
            ExpressionHandle residual,
            std::initializer_list<VariableId> variables);

        //==================================================
        // Final Model
        //==================================================

        // Finalize and return the constructed model.
        Model build();

    private:

        // Model currently under construction.
        Model model_;
    };
}