#include <lexica/graph/DependencyGraphBuilder.hpp>

namespace lexica
{
    DependencyGraph
    DependencyGraphBuilder::build(
        const Model& model,
        const MatchingResult& matching)
    {
        DependencyGraph graph;

        graph.dependencies.resize(
            model.variables.size());

        for (const auto& equation :
             model.equations)
        {
            const auto solvedVariable =
                matching.equationMatch[
                    equation.id];

            if (solvedVariable ==
                InvalidVariableId)
            {
                continue;
            }

            auto& dependencies =
                graph.dependencies[
                    solvedVariable];

            for (auto variableId :
                 equation.variables)
            {
                if (variableId ==
                    solvedVariable)
                {
                    continue;
                }

                const auto& variable =
                    model.variables[
                        variableId];

                if (variable.status !=
                    VariableStatus::Unknown)
                {
                    continue;
                }

                dependencies.push_back(
                    variableId);
            }
        }

        return graph;
    }
}