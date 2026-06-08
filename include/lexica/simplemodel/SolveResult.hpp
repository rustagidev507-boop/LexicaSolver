#pragma once

#include <lexica/runtime/VariableVector.hpp>

namespace lexica
{
    struct SolveResult
    {
        VariableVector values;

        bool success = false;
    };
}