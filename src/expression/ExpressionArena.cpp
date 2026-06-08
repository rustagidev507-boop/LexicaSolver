#include <lexica/expression/ExpressionArena.hpp>

namespace lexica
{
    NodeId ExpressionArena::createConstant(
        Scalar value)
    {
        NodeId id =
            static_cast<NodeId>(
                nodes_.size());

        nodes_.push_back(
            ExpressionNode{
                .kind = ExpressionKind::Constant,
                .constantValue = value
            });

        return id;
    }

    NodeId ExpressionArena::createVariable(
        VariableId variableId)
    {
        NodeId id =
            static_cast<NodeId>(
                nodes_.size());

        nodes_.push_back(
            ExpressionNode{
                .kind = ExpressionKind::Variable,
                .variableId = variableId
            });

        return id;
    }

    NodeId ExpressionArena::createUnary(
        ExpressionKind kind,
        NodeId operand)
    {
        NodeId id =
            static_cast<NodeId>(
                nodes_.size());

        nodes_.push_back(
            ExpressionNode{
                .kind = kind,
                .left = operand
            });

        return id;
    }

    NodeId ExpressionArena::createBinary(
        ExpressionKind kind,
        NodeId left,
        NodeId right)
    {
        NodeId id =
            static_cast<NodeId>(
                nodes_.size());

        nodes_.push_back(
            ExpressionNode{
                .kind = kind,
                .left = left,
                .right = right
            });

        return id;
    }

    ExpressionNode&
    ExpressionArena::get(
        NodeId id)
    {
        return nodes_[id];
    }

    const ExpressionNode&
    ExpressionArena::get(
        NodeId id) const
    {
        return nodes_[id];
    }

    std::size_t
    ExpressionArena::size() const
    {
        return nodes_.size();
    }
}