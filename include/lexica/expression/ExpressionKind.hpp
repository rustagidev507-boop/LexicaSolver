#pragma once

namespace lexica
{
    enum class ExpressionKind
    {
        Constant,
        Variable,

        Add,
        Subtract,
        Multiply,
        Divide,
        Power,

        Negate,

        Sin,
        Cos,
        Tan,

        Exp,
        Log,
        Sqrt
    };
}