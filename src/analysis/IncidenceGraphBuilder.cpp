#include <lexica/analysis/IncidenceGraphBuilder.hpp>

namespace lexica
{
    IncidenceGraph
    IncidenceGraphBuilder::build(
        const Model& model)
    {
        //------------------------------------------------------
        // Allocate graph storage
        //
        // One adjacency list is maintained from equations
        // to variables and another from variables to
        // equations.
        //------------------------------------------------------

        IncidenceGraph graph;

        graph.equationVariables.resize(
            model.equations.size());

        graph.variableEquations.resize(
            model.variables.size());

        //------------------------------------------------------
        // Build incidence relationships
        //
        // Record every participation relationship between
        // equations and variables.
        //
        // Equation -> Variables
        // Variable -> Equations
        //------------------------------------------------------

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

        //------------------------------------------------------
        // Return structural connectivity graph
        //------------------------------------------------------

        return graph;
    }
}