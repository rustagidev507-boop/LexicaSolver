#include <lexica/analysis/StructuralGraphBuilder.hpp>

namespace lexica
{
    StructuralGraph
    StructuralGraphBuilder::build(
        const Model& model)
    {
        StructuralGraph graph;

        graph.equationVariables.resize(
            model.equations.size());

        for (const auto& equation :
             model.equations)
        {
            auto& unknowns =
                graph.equationVariables[
                    equation.id];

            for (auto variableId :
                 equation.variables)
            {
                const auto& variable =
                    model.variables[
                        variableId];

                if (variable.status ==
                    VariableStatus::Unknown)
                {
                    unknowns.push_back(
                        variableId);
                }
            }
        }

        return graph;
    }
}