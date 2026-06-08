#pragma once

#include <vector>

#include <lexica/planning/StructuralBlock.hpp>

namespace lexica
{
    struct BlockResult
    {
        std::vector<StructuralBlock>
            blocks;
    };
}