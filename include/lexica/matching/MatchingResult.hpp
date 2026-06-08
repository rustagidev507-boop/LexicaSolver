#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    struct MatchingResult
    {
        std::vector<VariableId>
            equationMatch;

        std::vector<EquationId>
            variableMatch;

        std::size_t matchedCount{};
    };
}