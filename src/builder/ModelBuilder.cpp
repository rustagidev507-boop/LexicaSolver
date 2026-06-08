#include <utility>

#include <lexica/builder/ModelBuilder.hpp>

namespace lexica
{
    VariableId
    ModelBuilder::variable(
        std::string_view name)
    {
        VariableId id =
            static_cast<VariableId>(
                model_.variables.size());

        model_.variables.push_back(
        {
            .id = id,
            .name = std::string(name),
            .status =
                VariableStatus::Unknown
        });

        return id;
    }

    VariableId
    ModelBuilder::variable(
        std::string_view name,
        Scalar value)
    {
        VariableId id =
            static_cast<VariableId>(
                model_.variables.size());

        model_.variables.push_back(
        {
            .id = id,
            .name = std::string(name),
            .value = value,
            .status =
                VariableStatus::Known
        });

        return id;
    }

    ExpressionHandle
    ModelBuilder::var(
        VariableId variable)
    {
        return
        {
            model_.expressions
                .createVariable(variable)
        };
    }

    ExpressionHandle
    ModelBuilder::constant(
        Scalar value)
    {
        return
        {
            model_.expressions
                .createConstant(value)
        };
    }

    ExpressionHandle
    ModelBuilder::add(
        ExpressionHandle lhs,
        ExpressionHandle rhs)
    {
        return
        {
            model_.expressions
                .createBinary(
                    ExpressionKind::Add,
                    lhs.root,
                    rhs.root)
        };
    }

    ExpressionHandle
    ModelBuilder::subtract(
        ExpressionHandle lhs,
        ExpressionHandle rhs)
    {
        return
        {
            model_.expressions
                .createBinary(
                    ExpressionKind::Subtract,
                    lhs.root,
                    rhs.root)
        };
    }

    ExpressionHandle
    ModelBuilder::multiply(
        ExpressionHandle lhs,
        ExpressionHandle rhs)
    {
        return
        {
            model_.expressions
                .createBinary(
                    ExpressionKind::Multiply,
                    lhs.root,
                    rhs.root)
        };
    }

    ExpressionHandle
    ModelBuilder::divide(
        ExpressionHandle lhs,
        ExpressionHandle rhs)
    {
        return
        {
            model_.expressions
                .createBinary(
                    ExpressionKind::Divide,
                    lhs.root,
                    rhs.root)
        };
    }

    ExpressionHandle
    ModelBuilder::power(
        ExpressionHandle lhs,
        ExpressionHandle rhs)
    {
        return
        {
            model_.expressions
                .createBinary(
                    ExpressionKind::Power,
                    lhs.root,
                    rhs.root)
        };
    }

    ExpressionHandle
    ModelBuilder::negate(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Negate,
                    operand.root)
        };
    }

    ExpressionHandle
    ModelBuilder::sin(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Sin,
                    operand.root)
        };
    }

    ExpressionHandle
    ModelBuilder::cos(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Cos,
                    operand.root)
        };
    }

    ExpressionHandle
    ModelBuilder::exp(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Exp,
                    operand.root)
        };
    }

    ExpressionHandle
    ModelBuilder::log(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Log,
                    operand.root)
        };
    }

    ExpressionHandle
    ModelBuilder::sqrt(
        ExpressionHandle operand)
    {
        return
        {
            model_.expressions
                .createUnary(
                    ExpressionKind::Sqrt,
                    operand.root)
        };
    }

    EquationId
    ModelBuilder::equation(
        std::string_view name,
        ExpressionHandle residual,
        std::initializer_list<VariableId> variables)
    {
        EquationId id =
            static_cast<EquationId>(
                model_.equations.size());

        model_.equations.push_back(
        {
            .id = id,
            .name = std::string(name),
            .rootNode = residual.root,
            .variables = variables
        });

        return id;
    }

    Model
    ModelBuilder::build()
    {
        return std::move(model_);
    }
}