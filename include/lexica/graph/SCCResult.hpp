#pragma once

#include <vector>

#include <lexica/graph/SCC.hpp>

namespace lexica
{
    struct SCCResult
    {
        std::vector<SCC>
            components;

        std::vector<std::size_t>
            componentOfVariable;
    };
}