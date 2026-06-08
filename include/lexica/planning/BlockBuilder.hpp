#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/matching/MatchingResult.hpp>

#include <lexica/graph/SCCResult.hpp>

#include <lexica/planning/BlockResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Block Builder
    |--------------------------------------------------------------------------
    |
    | Transforms strongly connected components into executable
    | computational blocks.
    |
    | After feedback loops have been identified, the block
    | builder groups related equations and variables into
    | subsystems that can be analyzed, classified, and solved
    | independently.
    |
    | This stage marks the transition from structural analysis
    | to execution planning.
    |
    | The resulting blocks become the primary execution units
    | throughout the remainder of the Lexica pipeline.
    |
    | Typical Flow:
    |
    |     Matching + SCCs
    |             ↓
    |       Block Builder
    |             ↓
    |      Computational Blocks
    |             ↓
    |     Block Classification
    |             ↓
    |      Execution Planning
    |
    | IMPORTANT:
    |
    | This component performs structural decomposition only.
    |
    | It does NOT classify blocks, assign solvers, generate
    | execution order, or perform numerical solving.
    |
    */

    class BlockBuilder
    {
    public:

        // Build computational blocks from structural components.
        static BlockResult build(
            const Model& model,
            const MatchingResult& matching,
            const SCCResult& sccResult);
    };
}