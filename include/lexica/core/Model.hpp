#pragma once

#include <vector>

#include <lexica/core/Variable.hpp>
#include <lexica/core/Equation.hpp>
#include <lexica/expression/ExpressionArena.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Model
    |--------------------------------------------------------------------------
    |
    | Central mathematical representation of a problem inside Lexica.
    |
    | A Model captures the complete equation-based description of a
    | system and serves as the primary artifact exchanged between
    | major pipeline stages.
    |
    | Typical Lifecycle:
    |
    |     User Intent
    |          ↓
    |     Model Construction
    |          ↓
    |     Structural Analysis
    |          ↓
    |     Execution Planning
    |          ↓
    |     Numerical Solving
    |
    | The model itself is intentionally passive.
    |
    | It does not perform:
    |
    |     - Structural Analysis
    |     - Dependency Discovery
    |     - Solver Selection
    |     - Numerical Execution
    |
    | Instead, it acts as the shared source of truth consumed by
    | higher-level systems throughout the solving pipeline.
    |
    */

    struct Model
    {
        /*
        |--------------------------------------------------------------------------
        | Variables
        |--------------------------------------------------------------------------
        |
        | Collection of all variables participating in the model.
        |
        | Variables represent the quantities that define the state
        | of the system.
        |
        | Examples:
        |
        |     Pressure
        |     Temperature
        |     MassFlow
        |     Velocity
        |
        */

        std::vector<Variable> variables;

        /*
        |--------------------------------------------------------------------------
        | Equations
        |--------------------------------------------------------------------------
        |
        | Collection of all equations defining relationships
        | between variables.
        |
        | Equations describe the constraints that must be satisfied
        | simultaneously for the model to be considered solved.
        |
        */

        std::vector<Equation> equations;

        /*
        |--------------------------------------------------------------------------
        | Expression Storage
        |--------------------------------------------------------------------------
        |
        | Centralized storage for all mathematical expression nodes
        | referenced by model equations.
        |
        | Equations reference expression trees through NodeId
        | handles rather than owning expression structures directly.
        |
        | This arena-based design provides:
        |
        |     - Compact storage
        |     - Stable references
        |     - Efficient traversal
        |     - Low allocation overhead
        |
        | The expression arena forms the mathematical backbone of
        | the model and is used by evaluators, residual generation,
        | Jacobian construction, and numerical solvers.
        |
        */

        ExpressionArena expressions;
    };
}