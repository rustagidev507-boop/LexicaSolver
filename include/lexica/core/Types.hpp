#pragma once

#include <cstdint>
#include <limits>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Core Type System
    |--------------------------------------------------------------------------
    |
    | Defines the fundamental identifier and scalar types used
    | throughout the Lexica platform.
    |
    | These types form the common language shared by all layers:
    |
    |     Knowledge Layer
    |     Modeling Layer
    |     Structural Analysis
    |     Planning
    |     Numerical Solvers
    |     Execution Engine
    |
    | The goal is to establish stable, strongly-typed identifiers
    | that remain consistent across the entire pipeline.
    |
    | IMPORTANT:
    |
    | Identifiers are not numerical values.
    |
    | They are lightweight references used to locate entities
    | inside model-owned storage containers.
    |
    */

    /*
    |--------------------------------------------------------------------------
    | Entity Identifiers
    |--------------------------------------------------------------------------
    |
    | Stable handles used to reference model entities.
    |
    | Examples:
    |
    |     VariableId  -> Pressure
    |     EquationId  -> Momentum Equation
    |     NodeId      -> Expression Tree Node
    |
    | Using explicit identifier types improves readability and
    | prevents accidental mixing of unrelated entities.
    |
    */

    using VariableId = std::uint32_t;

    using EquationId = std::uint32_t;

    using NodeId = std::uint32_t;

    /*
    |--------------------------------------------------------------------------
    | Scalar Type
    |--------------------------------------------------------------------------
    |
    | Primary floating-point type used throughout numerical
    | evaluation and solving.
    |
    | Examples:
    |
    |     Variable Values
    |     Residual Values
    |     Jacobian Entries
    |     Solver Updates
    |
    */

    using Scalar = double;

    /*
    |--------------------------------------------------------------------------
    | Invalid Identifiers
    |--------------------------------------------------------------------------
    |
    | Sentinel values representing the absence of a valid entity.
    |
    | These values are commonly used during:
    |
    |     Graph Construction
    |     Matching
    |     Planning
    |     Solver Initialization
    |
    | A valid identifier must never equal its corresponding
    | invalid sentinel value.
    |
    */

    constexpr VariableId
        InvalidVariableId =
            std::numeric_limits<
                VariableId>::max();

    constexpr EquationId
        InvalidEquationId =
            std::numeric_limits<
                EquationId>::max();

    constexpr NodeId
        InvalidNodeId =
            std::numeric_limits<
                NodeId>::max();

    /*
    |--------------------------------------------------------------------------
    | Variable Status
    |--------------------------------------------------------------------------
    |
    | Describes the current state of a variable during model
    | analysis and execution.
    |
    | Unknown
    |
    |     Variable value is not yet available and must be
    |     determined by the solving process.
    |
    | Known
    |
    |     Variable value is provided externally through model
    |     inputs, parameters, or boundary conditions.
    |
    | Solved
    |
    |     Variable value has been successfully computed by the
    |     execution engine.
    |
    */

    enum class VariableStatus
    {
        Unknown,
        Known,
        Solved
    };
}