#pragma once

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Expression Handle
    |--------------------------------------------------------------------------
    |
    | Lightweight reference to a mathematical expression stored
    | inside an ExpressionArena.
    |
    | Expression handles provide a safe and convenient way to
    | pass expressions between modeling APIs without exposing
    | internal storage details.
    |
    | During model construction, expressions are incrementally
    | assembled and represented by handles rather than raw node
    | identifiers.
    |
    | IMPORTANT:
    |
    | This object does not own expression data.
    |
    | It simply references the root node of an expression tree
    | managed by the ExpressionArena.
    |
    */

    struct ExpressionHandle
    {
        // Root node of the expression tree.
        NodeId root{};
    };
}