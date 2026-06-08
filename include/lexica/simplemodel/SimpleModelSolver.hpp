#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/runtime/VariableVector.hpp>

#include <lexica/planning/BlockResult.hpp>

#include <lexica/simplemodel/SolveResult.hpp>

namespace lexica
{
    class SimpleModelSolver
    {
    public:

        static SolveResult solve(
            const Model& model,
            const BlockResult& blocks,
            VariableVector initialGuess);
    };
}