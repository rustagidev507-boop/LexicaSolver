#pragma once

#include <cstddef>

#include <lexica/runtime/VariableVector.hpp>

namespace lexica
{
    struct NewtonResult
    {
        VariableVector solution;

        bool converged = false;

        std::size_t iterations = 0;
    };
}