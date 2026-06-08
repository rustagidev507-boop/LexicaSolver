#include <iostream>

#include <lexica/builder/ModelBuilder.hpp>

#include <lexica/analysis/EquationAnalyser.hpp>
#include <lexica/analysis/IncidenceGraphBuilder.hpp>
#include <lexica/analysis/StructuralGraphBuilder.hpp>
#include <lexica/matching/BipartiteMatcher.hpp>

int main()
{
    using namespace lexica;

    ModelBuilder builder;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------

    auto D =
        builder.variable(
            "Diameter",
            0.5);

    auto rho =
        builder.variable(
            "Density",
            1000.0);

    auto mu =
        builder.variable(
            "Viscosity",
            0.001);

    auto A =
        builder.variable(
            "Area");

    auto V =
        builder.variable(
            "Velocity");

    auto Q =
        builder.variable(
            "FlowRate");

    auto Re =
        builder.variable(
            "Reynolds");

    //--------------------------------------------------
    // Eq1
    // A - pi*D²/4 = 0
    //--------------------------------------------------

    auto pi =
        builder.constant(
            3.141592653589793);

    auto four =
        builder.constant(
            4.0);

    auto areaResidual =
        builder.subtract(
            builder.var(A),
            builder.divide(
                builder.multiply(
                    pi,
                    builder.power(
                        builder.var(D),
                        builder.constant(2.0))),
                four));

    builder.equation(
        "AreaEquation",
        areaResidual,
        { A, D });

    //--------------------------------------------------
    // Eq2
    // Q - A*V = 0
    //--------------------------------------------------

    auto flowResidual =
        builder.subtract(
            builder.var(Q),
            builder.multiply(
                builder.var(A),
                builder.var(V)));

    builder.equation(
        "FlowEquation",
        flowResidual,
        { Q, A, V });

    //--------------------------------------------------
    // Eq3
    // Re - rho*V*D/mu = 0
    //--------------------------------------------------

    auto reynoldsResidual =
        builder.subtract(
            builder.var(Re),
            builder.divide(
                builder.multiply(
                    builder.multiply(
                        builder.var(rho),
                        builder.var(V)),
                    builder.var(D)),
                builder.var(mu)));

    builder.equation(
        "ReynoldsEquation",
        reynoldsResidual,
        { Re, rho, V, D, mu });

    //--------------------------------------------------
    // Eq4
    // V - 2 = 0
    //--------------------------------------------------

    auto velocityResidual =
        builder.subtract(
            builder.var(V),
            builder.constant(2.0));

    builder.equation(
        "VelocityTarget",
        velocityResidual,
        { V });

    //--------------------------------------------------
    // Eq5
    // Q - 1 = 0
    //--------------------------------------------------

    auto flowTargetResidual =
        builder.subtract(
            builder.var(Q),
            builder.constant(1.0));

    builder.equation(
        "FlowTarget",
        flowTargetResidual,
        { Q });

    //--------------------------------------------------
    // Build Model
    //--------------------------------------------------

    auto model =
        builder.build();

    //--------------------------------------------------
    // Model Summary
    //--------------------------------------------------

    std::cout
        << "\n===== MODEL =====\n";

    std::cout
        << "Variables : "
        << model.variables.size()
        << '\n';

    std::cout
        << "Equations : "
        << model.equations.size()
        << '\n';

    std::cout
        << "Nodes     : "
        << model.expressions.size()
        << '\n';

    //--------------------------------------------------
    // Equation Analysis
    //--------------------------------------------------

    std::cout
        << "\n===== EQUATION ANALYSIS =====\n";

    for (const auto& equation :
         model.equations)
    {
        auto info =
            EquationAnalyzer::analyze(
                model,
                equation);

        std::cout
            << equation.name
            << '\n';

        std::cout
            << "Unknown Count : "
            << info.unknownCount
            << '\n';

        std::cout
            << "Unknown Variables : ";

        for (auto variableId :
             info.unknownVariables)
        {
            std::cout
                << model.variables[variableId].name
                << " ";
        }

        std::cout
            << "\n\n";
    }

    //--------------------------------------------------
    // Incidence Graph
    //--------------------------------------------------

    auto graph =
        IncidenceGraphBuilder::build(
            model);

    std::cout
        << "===== EQUATION -> VARIABLES =====\n";

    for (std::size_t equation = 0;
         equation <
         graph.equationVariables.size();
         ++equation)
    {
        std::cout
            << "Eq"
            << equation
            << " -> ";

        for (auto variable :
             graph.equationVariables[equation])
        {
            std::cout
                << model.variables[variable].name
                << " ";
        }

        std::cout
            << '\n';
    }

    std::cout
        << "\n===== VARIABLE -> EQUATIONS =====\n";

    for (std::size_t variable = 0;
         variable <
         graph.variableEquations.size();
         ++variable)
    {
        std::cout
            << model.variables[variable].name
            << " -> ";

        for (auto equation :
             graph.variableEquations[variable])
        {
            std::cout
                << "Eq"
                << equation
                << " ";
        }

        std::cout
            << '\n';
    }

    //--------------------------------------------------
    // Incidence Graph
    //--------------------------------------------------

    auto structuralGraph =
    StructuralGraphBuilder::build(
            model);

    std::cout
        << "\n===== STRUCTURAL GRAPH =====\n";

    for (std::size_t equation = 0;
        equation <
        structuralGraph.equationVariables.size();
        ++equation)
    {
        std::cout
            << "Eq"
            << equation
            << " -> ";

        for (auto variable :
            structuralGraph
                .equationVariables[equation])
        {
            std::cout
                << model.variables[variable].name
                << " ";
        }

        std::cout << '\n';
    }

    // Matching

    auto matching =
    BipartiteMatcher::match(
        structuralGraph);

std::cout
    << "\n===== MATCHING =====\n";

for (std::size_t equation = 0;
     equation <
     matching.equationMatch.size();
     ++equation)
{
    std::cout
        << "Eq"
        << equation
        << " -> ";

    auto variable =
        matching.equationMatch[equation];

    if (variable ==
        InvalidVariableId)
    {
        std::cout
            << "UNMATCHED";
    }
    else
    {
        std::cout
            << model.variables[
                   variable].name;
    }

    std::cout << '\n';
}

std::cout
    << "\nMatched Count : "
    << matching.matchedCount
    << '\n';
    return 0;
}