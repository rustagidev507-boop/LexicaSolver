#pragma once

#include <vector>

#include <lexica/analysis/StructuralGraph.hpp>

#include <lexica/matching/MatchingResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Bipartite Matcher
    |--------------------------------------------------------------------------
    |
    | Performs structural matching between equations and
    | variables.
    |
    | The objective of this stage is to determine which equation
    | is responsible for solving which variable, establishing the
    | structural assignments required for dependency analysis.
    |
    | This is one of the most important phases of the Lexica
    | pipeline because it transforms a collection of equations
    | into a solvable structural system.
    |
    | The resulting matching becomes the foundation for:
    |
    |     - Dependency Discovery
    |     - Cycle Detection
    |     - Block Formation
    |     - Execution Planning
    |
    | Typical Flow:
    |
    |     Structural Graph
    |             ↓
    |      Bipartite Matcher
    |             ↓
    |      Equation Matching
    |             ↓
    |      Dependency Graph
    |
    | IMPORTANT:
    |
    | This component determines structural assignments only.
    |
    | It does NOT perform dependency analysis, block
    | decomposition, solver selection, or numerical solving.
    |
    */

    class BipartiteMatcher
    {
    public:

        // Compute equation-to-variable assignments.
        static MatchingResult match(
            const StructuralGraph& graph);

    private:

        // Augmenting path search used during matching.
        static bool augment(
            EquationId equation,
            const StructuralGraph& graph,
            std::vector<bool>& visited,
            MatchingResult& result);
    };
}