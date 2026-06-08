#pragma once

#include <lexica/planning/BlockResult.hpp>

#include <lexica/solver/ClassificationResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Block Classifier
    |--------------------------------------------------------------------------
    |
    | Analyzes structural blocks and determines their numerical
    | characteristics.
    |
    | After block decomposition, each subsystem is inspected to
    | understand the complexity of the solve it requires. This
    | information is later used to select the most appropriate
    | execution strategy.
    |
    | Typical Classifications:
    |
    |     - Direct Solve Block
    |     - Coupled Nonlinear Block
    |     - Unsupported Block
    |
    | The resulting classifications form the bridge between
    | structural analysis and solver planning.
    |
    | Typical Flow:
    |
    |     Structural Blocks
    |             ↓
    |      Block Classifier
    |             ↓
    |      Block Types
    |             ↓
    |      Solver Selection
    |
    | IMPORTANT:
    |
    | This component performs structural classification only.
    |
    | It does NOT assign solvers, generate execution plans, or
    | perform numerical solving.
    |
    */

    class BlockClassifier
    {
    public:

        // Classify all structural blocks.
        static ClassificationResult classify(
            const BlockResult& blockResult);
    };
}