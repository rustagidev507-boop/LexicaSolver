#include <iostream>

#include <lexica/builder/ModelBuilder.hpp>
#include <lexica/analysis/EquationAnalyser.hpp> 
#include <lexica/analysis/StructuralGraphBuilder.hpp>

#include <lexica/analysis/StructuralGraphBuilder.hpp>

#include <lexica/matching/BipartiteMatcher.hpp>

#include <lexica/graph/DependencyGraphBuilder.hpp>
#include <lexica/graph/TarjanSCC.hpp>

#include <lexica/planning/BlockBuilder.hpp>

#include <lexica/runtime/EvaluationContext.hpp>
#include <lexica/runtime/ResidualEvaluator.hpp>

#include <lexica/runtime/VariableVector.hpp>

#include <lexica/simplemodel/SimpleModelSolver.hpp>

int main()
{
    using namespace lexica;

    ModelBuilder builder;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------

auto MassFlow           = builder.variable("MassFlow");
auto InjectorVelocity   = builder.variable("InjectorVelocity");
auto ChamberPressure    = builder.variable("ChamberPressure");

auto Density            = builder.variable("Density");
auto Temperature        = builder.variable("Temperature");

auto SpecificImpulse    = builder.variable("SpecificImpulse");
auto Efficiency         = builder.variable("Efficiency");

auto FuelFlow           = builder.variable("FuelFlow");
auto OxidizerFlow       = builder.variable("OxidizerFlow");
auto MixtureRatio       = builder.variable("MixtureRatio");

auto PumpPower          = builder.variable("PumpPower");
auto TurbinePower       = builder.variable("TurbinePower");

auto NozzleVelocity     = builder.variable("NozzleVelocity");
auto Thrust             = builder.variable("Thrust");

auto HeatLoss           = builder.variable("HeatLoss");

//--------------------------------------------------
// FEED SYSTEM LOOP
//--------------------------------------------------

//
// Eq0
// MassFlow - Density*InjectorVelocity/2 = 0
//

auto eq0 =
    builder.subtract(
        builder.var(MassFlow),

        builder.divide(
            builder.multiply(
                builder.var(Density),
                builder.var(InjectorVelocity)),
            builder.constant(2.0)));

builder.equation(
    "Eq0",
    eq0,
    {
        MassFlow,
        Density,
        InjectorVelocity
    });

//
// Eq1
// ChamberPressure - InjectorVelocity² = 0
//

auto eq1 =
    builder.subtract(
        builder.var(ChamberPressure),

        builder.power(
            builder.var(InjectorVelocity),
            builder.constant(2.0)));

builder.equation(
    "Eq1",
    eq1,
    {
        ChamberPressure,
        InjectorVelocity
    });

//
// Eq2
// MassFlow + ChamberPressure - 104 = 0
//

auto eq2 =
    builder.subtract(

        builder.add(
            builder.var(MassFlow),
            builder.var(ChamberPressure)),

        builder.constant(104.0));

builder.equation(
    "Eq2",
    eq2,
    {
        MassFlow,
        ChamberPressure
    });


//--------------------------------------------------
// THERMAL LOOP
//--------------------------------------------------

//
// Eq3
// Density*Temperature - 300 = 0
//

auto eq3 =
    builder.subtract(

        builder.multiply(
            builder.var(Density),
            builder.var(Temperature)),

        builder.constant(300.0));

builder.equation(
    "Eq3",
    eq3,
    {
        Density,
        Temperature
    });

//
// Eq4
// Density + Temperature - 40 = 0
//

auto eq4 =
    builder.subtract(

        builder.add(
            builder.var(Density),
            builder.var(Temperature)),

        builder.constant(40.0));

builder.equation(
    "Eq4",
    eq4,
    {
        Density,
        Temperature
    });


//--------------------------------------------------
// COMBUSTION LOOP
//--------------------------------------------------

//
// Eq5
// SpecificImpulse*10 - Temperature = 0
//

auto eq5 =
    builder.subtract(

        builder.multiply(
            builder.var(SpecificImpulse),
            builder.constant(10.0)),

        builder.var(Temperature));

builder.equation(
    "Eq5",
    eq5,
    {
        SpecificImpulse,
        Temperature
    });

//
// Eq6
// Efficiency*Temperature - 15 = 0
//

auto eq6 =
    builder.subtract(

        builder.multiply(
            builder.var(Efficiency),
            builder.var(Temperature)),

        builder.constant(15.0));

builder.equation(
    "Eq6",
    eq6,
    {
        Efficiency,
        Temperature
    });

//
// Eq7
// SpecificImpulse + Efficiency - 3.5 = 0
//

auto eq7 =
    builder.subtract(

        builder.add(
            builder.var(SpecificImpulse),
            builder.var(Efficiency)),

        builder.constant(3.5));

builder.equation(
    "Eq7",
    eq7,
    {
        SpecificImpulse,
        Efficiency
    });


//--------------------------------------------------
// PROPELLANT LOOP
//--------------------------------------------------

//
// Eq8
// FuelFlow + OxidizerFlow - MassFlow = 0
//

auto eq8 =
    builder.subtract(

        builder.add(
            builder.var(FuelFlow),
            builder.var(OxidizerFlow)),

        builder.var(MassFlow));

builder.equation(
    "Eq8",
    eq8,
    {
        FuelFlow,
        OxidizerFlow,
        MassFlow
    });

//
// Eq9
// OxidizerFlow - 3*FuelFlow = 0
//

auto eq9 =
    builder.subtract(

        builder.var(OxidizerFlow),

        builder.multiply(
            builder.constant(3.0),
            builder.var(FuelFlow)));

builder.equation(
    "Eq9",
    eq9,
    {
        OxidizerFlow,
        FuelFlow
    });

//
// Eq10
// MixtureRatio*FuelFlow - OxidizerFlow = 0
//

auto eq10 =
    builder.subtract(

        builder.multiply(
            builder.var(MixtureRatio),
            builder.var(FuelFlow)),

        builder.var(OxidizerFlow));

builder.equation(
    "Eq10",
    eq10,
    {
        MixtureRatio,
        FuelFlow,
        OxidizerFlow
    });


//--------------------------------------------------
// POWER SYSTEM
//--------------------------------------------------

//
// Eq11
// PumpPower - MassFlow*ChamberPressure = 0
//

auto eq11 =
    builder.subtract(

        builder.var(PumpPower),

        builder.multiply(
            builder.var(MassFlow),
            builder.var(ChamberPressure)));

builder.equation(
    "Eq11",
    eq11,
    {
        PumpPower,
        MassFlow,
        ChamberPressure
    });

//
// Eq12
// TurbinePower - PumpPower*Efficiency = 0
//

auto eq12 =
    builder.subtract(

        builder.var(TurbinePower),

        builder.multiply(
            builder.var(PumpPower),
            builder.var(Efficiency)));

builder.equation(
    "Eq12",
    eq12,
    {
        TurbinePower,
        PumpPower,
        Efficiency
    });


//--------------------------------------------------
// NOZZLE SYSTEM
//--------------------------------------------------

//
// Eq13
// NozzleVelocity - SpecificImpulse = 0
//

auto eq13 =
    builder.subtract(

        builder.var(NozzleVelocity),

        builder.var(SpecificImpulse));

builder.equation(
    "Eq13",
    eq13,
    {
        NozzleVelocity,
        SpecificImpulse
    });

//
// Eq14
// Thrust - MassFlow*NozzleVelocity = 0
//

auto eq14 =
    builder.subtract(

        builder.var(Thrust),

        builder.multiply(
            builder.var(MassFlow),
            builder.var(NozzleVelocity)));

builder.equation(
    "Eq14",
    eq14,
    {
        Thrust,
        MassFlow,
        NozzleVelocity
    });


//--------------------------------------------------
// THERMAL LOSSES
//--------------------------------------------------

//
// Eq15
// HeatLoss - Temperature*(1-Efficiency) = 0
//

auto eq15 =
    builder.subtract(

        builder.var(HeatLoss),

        builder.multiply(
            builder.var(Temperature),

            builder.subtract(
                builder.constant(1.0),
                builder.var(Efficiency))));

builder.equation(
    "Eq15",
    eq15,
    {
        HeatLoss,
        Temperature,
        Efficiency
    });

    //--------------------------------------------------
    // Build model
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
    // Structural pipeline
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

    auto dependencyGraph =
        DependencyGraphBuilder::build(
            model,
            matching);
    std::cout
    << "\n===== DEPENDENCY GRAPH =====\n";

for (std::size_t variable = 0;
     variable <
     dependencyGraph.dependencies.size();
     ++variable)
{
    const auto& deps =
        dependencyGraph.dependencies[
            variable];

    if (deps.empty())
    {
        continue;
    }

    std::cout
        << model.variables[variable].name
        << " -> ";

    for (auto dependency :
         deps)
    {
        std::cout
            << model.variables[
                   dependency].name
            << " ";
    }

    std::cout << '\n';
}


    auto scc =
        TarjanSCC::find(
            dependencyGraph);

    std::cout
        << "\n===== SCCs =====\n";

    for (std::size_t i = 0;
         i < scc.components.size();
         ++i)
    {
        std::cout
            << "SCC "
            << i
            << " : ";

        for (auto variable :
             scc.components[i].variables)
        {
            std::cout
                << model.variables[
                       variable].name
                << " ";
        }

        std::cout<<'\n';
    }

    auto blocks =
        BlockBuilder::build(
            model,
            matching,
            scc);

    //--------------------------------------------------
    // Print blocks
    //--------------------------------------------------

    std::cout
        << "\n===== BLOCKS =====\n";

    for (std::size_t i = 0;
         i < blocks.blocks.size();
         ++i)
    {
        const auto& block =
            blocks.blocks[i];

        std::cout
            << "\nBlock "
            << i
            << '\n';

        std::cout
            << "Variables : ";

        for (auto variable :
             block.variables)
        {
            std::cout
                << model.variables[
                       variable].name
                << " ";
        }

        std::cout
            << "\nEquations : ";

        for (auto equation :
             block.equations)
        {
            std::cout
                << model.equations[
                       equation].name
                << " ";
        }

        std::cout
            << '\n';
    }

    //--------------------------------------------------
    // Initial guess
    //--------------------------------------------------

    VariableVector guess;

guess.values.resize(
    model.variables.size());

guess.values[MassFlow] = 30.0;
guess.values[InjectorVelocity] = 6.0;
guess.values[ChamberPressure] = 50.0;

guess.values[Density] = 8.0;
guess.values[Temperature] = 25.0;

guess.values[SpecificImpulse] = 2.0;
guess.values[Efficiency] = 0.7;

guess.values[FuelFlow] = 12.0;
guess.values[OxidizerFlow] = 28.0;
guess.values[MixtureRatio] = 2.0;

guess.values[PumpPower] = 2000.0;
guess.values[TurbinePower] = 1000.0;

guess.values[NozzleVelocity] = 2.0;
guess.values[Thrust] = 100.0;

guess.values[HeatLoss] = 20.0;

    //--------------------------------------------------
    // Solve
    //--------------------------------------------------

    auto result =
        SimpleModelSolver::solve(
            model,
            blocks,
            guess);

    //--------------------------------------------------
    // Solution
    //--------------------------------------------------

    std::cout
        << "\n===== SOLUTION =====\n";

    std::cout
        << "Success : "
        << std::boolalpha
        << result.success
        << '\n';

    for (std::size_t i = 0;
         i < model.variables.size();
         ++i)
    {
        std::cout
            << model.variables[i].name
            << " = "
            << result.values.values[i]
            << '\n';
    }

    //--------------------------------------------------
    // Residuals
    //--------------------------------------------------

    EvaluationContext context;

    context.variableValues =
        result.values.values;

    auto residuals =
        ResidualEvaluator::evaluateModel(
            model,
            context);

    std::cout
        << "\n===== FINAL RESIDUALS =====\n";

    for (double residual :
         residuals.values)
    {
        std::cout
            << residual
            << '\n';
    }

    return 0;
}