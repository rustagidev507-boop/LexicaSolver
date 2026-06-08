#include <lexica/analysis/StructuralGraphBuilder.hpp>

namespace lexica
{
    StructuralGraph
    StructuralGraphBuilder::build(
        const Model& model)
    {
        //------------------------------------------------------
        // Allocate graph storage
        //
        // Only unknown variables participate in structural
        // matching, so the graph stores equation-to-unknown
        // relationships.
        //------------------------------------------------------

        StructuralGraph graph;

        graph.equationVariables.resize(
            model.equations.size());

        //------------------------------------------------------
        // Extract structural relationships
        //
        // Known variables are treated as available inputs.
        // Only unknown variables contribute to the solvability
        // structure of the system.
        //------------------------------------------------------

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

        //------------------------------------------------------
        // Return structural representation
        //
        // This graph becomes the input to equation matching.
        //------------------------------------------------------

        return graph;
    }
}