#pragma once

#include <vector>

#include <lexica/solver/ClassifiedBlock.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Classification Result
    |--------------------------------------------------------------------------
    |
    | Represents the outcome of block classification across an
    | entire model.
    |
    | After structural blocks have been analyzed, the resulting
    | classifications are collected into a single object that
    | can be consumed by later planning stages.
    |
    | This structure serves as the handoff between block
    | analysis and solver selection.
    |
    | Typical Flow:
    |
    |     Structural Blocks
    |             ↓
    |      Block Classifier
    |             ↓
    |    Classification Result
    |             ↓
    |      Solver Selector
    |
    | IMPORTANT:
    |
    | This object stores classification information only.
    |
    | It does NOT contain solver assignments, execution order,
    | numerical state, or solution data.
    |
    */

    struct ClassificationResult
    {
        // Classification for each structural block.
        std::vector<
            ClassifiedBlock
        > blocks;
    };
}