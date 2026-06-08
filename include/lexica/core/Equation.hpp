#pragma once

#include <string>
#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Equation
    |--------------------------------------------------------------------------
    |
    | Structural representation of a mathematical constraint within
    | a model.
    |
    | Equations define relationships that must be satisfied
    | simultaneously for the system to be considered solved.
    |
    | Examples:
    |
    |     Pressure - Density * Temperature = 0
    |
    |     MassFlow - Area * Velocity = 0
    |
    |     Thrust - MassFlow * ExitVelocity = 0
    |
    | An Equation does not store the mathematical expression
    | directly. Instead, it references an expression tree stored
    | inside the model's ExpressionArena.
    |
    | During execution, equations become the source of:
    |
    |     - Residual Evaluation
    |     - Dependency Analysis
    |     - Structural Matching
    |     - Jacobian Construction
    |     - Numerical Solving
    |
    | Together, the collection of equations defines the constraint
    | system that Lexica must satisfy.
    |
    */

    struct Equation
    {
        /*
        |--------------------------------------------------------------------------
        | Equation Identifier
        |--------------------------------------------------------------------------
        |
        | Stable identifier assigned when the equation is added
        | to a model.
        |
        | Used throughout structural analysis, planning, and
        | numerical execution.
        |
        */

        EquationId id{};

        /*
        |--------------------------------------------------------------------------
        | Equation Name
        |--------------------------------------------------------------------------
        |
        | Human-readable label used for diagnostics, debugging,
        | visualization, and reporting.
        |
        | Examples:
        |
        |     MassBalance
        |     MomentumEquation
        |     ChamberPressureConstraint
        |
        */

        std::string name;

        /*
        |--------------------------------------------------------------------------
        | Expression Root
        |--------------------------------------------------------------------------
        |
        | Root node of the equation's expression tree.
        |
        | The complete mathematical constraint can be reached by
        | traversing the expression graph starting from this node.
        |
        | Ownership remains with the model's ExpressionArena.
        |
        */

        NodeId rootNode{};

        /*
        |--------------------------------------------------------------------------
        | Participating Variables
        |--------------------------------------------------------------------------
        |
        | Variables referenced by this equation.
        |
        | This information is used heavily during structural
        | analysis and allows the engine to construct equation-
        | variable incidence relationships without repeatedly
        | traversing expression trees.
        |
        | Examples:
        |
        |     Pressure Equation
        |
        |         Pressure
        |         Density
        |         Temperature
        |
        */

        std::vector<VariableId> variables;
    };
}