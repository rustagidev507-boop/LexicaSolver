#pragma once

#include <cstddef>

#include <lexica/solver/BlockType.hpp>

namespace lexica
{
    struct ExecutionStep
    {
        std::size_t blockId{};

        BlockType blockType =
            BlockType::Unknown;
    };
}