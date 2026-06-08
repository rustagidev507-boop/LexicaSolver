#pragma once

#include <lexica/planning/StructuralBlock.hpp>

#include <lexica/solver/BlockType.hpp>

namespace lexica
{
    struct ClassifiedBlock
    {
        StructuralBlock block;

        BlockType type =
            BlockType::Unknown;
    };
}