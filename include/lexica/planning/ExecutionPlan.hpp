#pragma once

#include <vector>

namespace lexica
{
    struct ExecutionPlan
    {
        std::vector<std::size_t>
            orderedBlocks;
    };
}