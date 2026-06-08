#pragma once

#include <limits>

#include <lexica/core/Types.hpp>
#include <lexica/expression/ExpressionKind.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Expression Node
    |--------------------------------------------------------------------------
    |
    | Fundamental building block of Lexica's mathematical
    | expression system.
    |
    | Expression nodes are assembled into trees that represent
    | equations, constraints, and mathematical relationships
    | throughout a model.
    |
    | Examples:
    |
    |     Pressure + Temperature
    |
    |     MassFlow * Velocity
    |
    |     sin(Angle)
    |
    | The complete mathematical structure of a model is stored
    | as a collection of interconnected expression nodes inside
    | the ExpressionArena.
    |
    | IMPORTANT:
    |
    | This object represents a single node in an expression tree.
    |
    | It does NOT perform evaluation, differentiation, or
    | numerical solving. Those responsibilities belong to later
    | stages of the execution pipeline.
    |
    */

    struct ExpressionNode
    {
        // Type of mathematical operation.
        ExpressionKind kind{};

        // Left child node.
        NodeId left{ InvalidNodeId };

        // Right child node.
        NodeId right{ InvalidNodeId };

        // Constant value for constant nodes.
        Scalar constantValue{};

        // Referenced variable for variable nodes.
        VariableId variableId{};
    };
}