#include <algorithm>

#include <lexica/core/Types.hpp>

#include <lexica/matching/BipartiteMatcher.hpp>

namespace lexica
{
    bool BipartiteMatcher::augment(
        EquationId equation,
        const StructuralGraph& graph,
        std::vector<bool>& visited,
        MatchingResult& result)
    {
        for (auto variable :
             graph.equationVariables[equation])
        {
            if (visited[variable])
            {
                continue;
            }

            visited[variable] = true;

            auto matchedEquation =
                result.variableMatch[variable];

            if (matchedEquation ==
                InvalidEquationId)
            {
                result.variableMatch[variable] =
                    equation;

                result.equationMatch[equation] =
                    variable;

                return true;
            }

            if (augment(
                    matchedEquation,
                    graph,
                    visited,
                    result))
            {
                result.variableMatch[variable] =
                    equation;

                result.equationMatch[equation] =
                    variable;

                return true;
            }
        }

        return false;
    }

    MatchingResult
    BipartiteMatcher::match(
        const StructuralGraph& graph)
    {
        MatchingResult result;

        //--------------------------------------------------
        // Determine largest VariableId
        //--------------------------------------------------

        std::size_t maxVariableId = 0;

        for (const auto& equation :
             graph.equationVariables)
        {
            for (auto variable :
                 equation)
            {
                maxVariableId =
                    std::max(
                        maxVariableId,
                        static_cast<std::size_t>(
                            variable));
            }
        }

        //--------------------------------------------------
        // Initialize matching tables
        //--------------------------------------------------

        result.equationMatch.resize(
            graph.equationVariables.size(),
            InvalidVariableId);

        result.variableMatch.resize(
            maxVariableId + 1,
            InvalidEquationId);

        //--------------------------------------------------
        // Maximum Bipartite Matching
        //--------------------------------------------------

        for (EquationId equation = 0;
             equation <
             graph.equationVariables.size();
             ++equation)
        {
            std::vector<bool> visited(
                result.variableMatch.size(),
                false);

            if (augment(
                    equation,
                    graph,
                    visited,
                    result))
            {
                ++result.matchedCount;
            }
        }

        return result;
    }
}