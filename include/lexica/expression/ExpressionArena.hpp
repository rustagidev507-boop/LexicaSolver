#pragma once

#include <vector>

#include <lexica/expression/ExpressionNode.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Expression Arena
    |--------------------------------------------------------------------------
    |
    | Central storage for all expression nodes belonging to a
    | model.
    |
    | Rather than allocating individual expression trees,
    | Lexica stores every mathematical operation inside a
    | contiguous arena and references nodes through NodeId
    | handles.
    |
    | This approach provides:
    |
    |     - Stable node references
    |     - Compact memory layout
    |     - Efficient traversal
    |     - Low allocation overhead
    |
    | Expression arenas form the mathematical backbone of a
    | model and are consumed by evaluators, structural analysis,
    | residual generation, Jacobian construction, and numerical
    | solvers.
    |
    | IMPORTANT:
    |
    | The arena owns expression nodes but does not perform
    | evaluation or solving. Its responsibility is limited to
    | storing and providing access to mathematical structure.
    |
    */

    class ExpressionArena
    {
    public:

        // Create a constant expression node.
        NodeId createConstant(
            Scalar value);

        // Create a variable reference node.
        NodeId createVariable(
            VariableId variableId);

        // Create a unary operation node.
        NodeId createUnary(
            ExpressionKind kind,
            NodeId operand);

        // Create a binary operation node.
        NodeId createBinary(
            ExpressionKind kind,
            NodeId left,
            NodeId right);

        // Mutable node access.
        ExpressionNode& get(
            NodeId id);

        // Read-only node access.
        const ExpressionNode& get(
            NodeId id) const;

        // Total number of stored nodes.
        std::size_t size() const;

    private:

        // Contiguous expression storage.
        std::vector<ExpressionNode> nodes_;
    };
}