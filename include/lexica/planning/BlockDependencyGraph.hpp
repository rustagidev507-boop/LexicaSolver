#pragma once

#include <vector>

namespace lexica
{
    struct BlockDependencyGraph
    {
        std::vector<
            std::vector<std::size_t>
        > adjacency;
    };
}