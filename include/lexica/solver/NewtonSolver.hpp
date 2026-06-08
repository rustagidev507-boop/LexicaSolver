#pragma once

#include <vector>

#include <lexica/core/Model.hpp>

#include <lexica/runtime/VariableVector.hpp>

#include <lexica/solver/NewtonResult.hpp>

namespace lexica
{
    class NewtonSolver
    {
    public:

        static NewtonResult solve(
            const Model& model,

            const std::vector<EquationId>& equations,

            const std::vector<VariableId>& variables,

            VariableVector initialGuess);
    };
}