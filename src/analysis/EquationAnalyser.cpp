#include <lexica/analysis/EquationAnalyser.hpp>

namespace lexica
{
    EquationInfo
    EquationAnalyzer::analyze(
        const Model& model,
        const Equation& equation)
    {
        //------------------------------------------------------
        // Initialize analysis result
        //------------------------------------------------------

        EquationInfo info;

        info.equation =
            equation.id;

        //------------------------------------------------------
        // Classify participating variables
        //
        // Variables are separated into known and unknown
        // groups so later structural algorithms can reason
        // about solvability and dependency relationships.
        //------------------------------------------------------

        for (auto variableId :
             equation.variables)
        {
            const auto& variable =
                model.variables[variableId];

            if (variable.status ==
                VariableStatus::Unknown)
            {
                info.unknownVariables
                    .push_back(variableId);
            }
            else
            {
                info.knownVariables
                    .push_back(variableId);
            }
        }

        //------------------------------------------------------
        // Compute summary statistics
        //------------------------------------------------------

        info.unknownCount =
            info.unknownVariables.size();

        //------------------------------------------------------
        // Return structural information
        //------------------------------------------------------

        return info;
    }
}