#include <lexica/analysis/IncidenceGraphBuilder.hpp>

namespace lexica
{
    IncidenceGraph
    IncidenceGraphBuilder::build(
        const Model& model)
    {
        IncidenceGraph graph;

        graph.equationVariables.resize(
            model.equations.size());

        graph.variableEquations.resize(
            model.variables.size());

        for (const auto& equation :
             model.equations)
        {
            for (auto variableId :
                 equation.variables)
            {
                graph.equationVariables[
                    equation.id]
                        .push_back(
                            variableId);

                graph.variableEquations[
                    variableId]
                        .push_back(
                            equation.id);
            }
        }

        return graph;
    }
}