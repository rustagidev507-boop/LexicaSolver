#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/analysis/StructuralGraph.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Structural Graph Builder
    |--------------------------------------------------------------------------
    |
    | Generates the structural representation of a model used by
    | Lexica's analysis pipeline.
    |
    | During this phase, equations are transformed into a graph
    | describing their relationship with participating variables,
    | allowing the system to reason about solvability without
    | considering numerical values.
    |
    | The resulting graph serves as the foundation for:
    |
    |     - Equation Matching
    |     - Dependency Discovery
    |     - Cycle Detection
    |     - Block Decomposition
    |
    | Typical Flow:
    |
    |     Model
    |        ↓
    |     Structural Graph Builder
    |        ↓
    |     Structural Graph
    |        ↓
    |     Matching & Planning
    |
    | IMPORTANT:
    |
    | This component extracts structural relationships only.
    |
    | It does NOT perform numerical evaluation, solving,
    | dependency analysis, or execution planning.
    |
    */

    class StructuralGraphBuilder
    {
    public:

        // Build the structural graph for a model.
        static StructuralGraph build(
            const Model& model);
    };
}