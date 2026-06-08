#include <lexica/analysis/EquationAnalyser.hpp>

namespace lexica
{
    EquationInfo
    EquationAnalyzer::analyze(
        const Model& model,
        const Equation& equation)
    {
        EquationInfo info;

        info.equation = equation.id;

        for (auto variableId : equation.variables)
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

        info.unknownCount =
            info.unknownVariables.size();

        return info;
    }
}