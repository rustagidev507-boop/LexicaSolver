#include <iostream>

#include <lexica/builder/ModelBuilder.hpp>

#include <lexica/analysis/StructuralGraphBuilder.hpp>

#include <lexica/matching/BipartiteMatcher.hpp>

#include <lexica/graph/DependencyGraphBuilder.hpp>

#include <lexica/graph/TarjanSCC.hpp>

#include <lexica/planning/BlockBuilder.hpp>

#include <lexica/planning/BlockDependencyBuilder.hpp>

#include <lexica/planning/TopologicalSorter.hpp>

#include <lexica/solver/BlockClassifier.hpp>
#include<lexica/solver/SolverPlanner.hpp>

int main()
{
    using namespace lexica;

    ModelBuilder builder;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------

    auto Diameter    = builder.variable(
        "Diameter",
        1000);

    auto Area        = builder.variable("Area");

    auto Velocity    = builder.variable("Velocity");
    auto FlowRate    = builder.variable("FlowRate");
    auto Pressure    = builder.variable("Pressure");

    auto Temperature = builder.variable("Temperature");
    auto Density     = builder.variable("Density");

    auto Power       = builder.variable("Power");
    auto Loss        = builder.variable("Loss");

    auto Efficiency  = builder.variable("Efficiency");

    //--------------------------------------------------
    // Eq0
    // Area = f(Diameter)
    //--------------------------------------------------

    auto eq0 =
        builder.subtract(
            builder.var(Area),
            builder.var(Diameter));

    builder.equation(
        "AreaEquation",
        eq0,
        {Area, Diameter});

    //--------------------------------------------------
    // Eq1
    // FlowRate = Area * Velocity
    //--------------------------------------------------

    auto eq1 =
        builder.subtract(
            builder.var(FlowRate),
            builder.var(Area));

    builder.equation(
        "FlowEquation",
        eq1,
        {FlowRate, Area, Velocity});

    //--------------------------------------------------
    // Eq2
    // Velocity = f(Pressure)
    //--------------------------------------------------

    auto eq2 =
        builder.subtract(
            builder.var(Velocity),
            builder.var(Pressure));

    builder.equation(
        "VelocityEquation",
        eq2,
        {Velocity, Pressure});

    //--------------------------------------------------
    // Eq3
    // Pressure = f(FlowRate)
    //--------------------------------------------------

    auto eq3 =
        builder.subtract(
            builder.var(Pressure),
            builder.var(FlowRate));

    builder.equation(
        "PressureEquation",
        eq3,
        {Pressure, FlowRate});

    //--------------------------------------------------
    // Eq4
    // Density = f(Temperature)
    //--------------------------------------------------

    auto eq4 =
        builder.subtract(
            builder.var(Density),
            builder.var(Temperature));

    builder.equation(
        "DensityEquation",
        eq4,
        {Density, Temperature});

    //--------------------------------------------------
    // Eq5
    // Temperature = f(Density)
    //--------------------------------------------------

    auto eq5 =
        builder.subtract(
            builder.var(Temperature),
            builder.var(Density));

    builder.equation(
        "TemperatureEquation",
        eq5,
        {Temperature, Density});

    //--------------------------------------------------
    // Eq6
    // Power = f(FlowRate, Pressure)
    //--------------------------------------------------

    auto eq6 =
        builder.subtract(
            builder.var(Power),
            builder.var(FlowRate));

    builder.equation(
        "PowerEquation",
        eq6,
        {Power, FlowRate, Pressure});

    //--------------------------------------------------
    // Eq7
    // Loss = f(Density, Velocity)
    //--------------------------------------------------

    auto eq7 =
        builder.subtract(
            builder.var(Loss),
            builder.var(Density));

    builder.equation(
        "LossEquation",
        eq7,
        {Loss, Density, Velocity});

    //--------------------------------------------------
    // Eq8
    // Efficiency = f(Power, Loss)
    //--------------------------------------------------

    auto eq8 =
        builder.subtract(
            builder.var(Efficiency),
            builder.var(Power));

    builder.equation(
        "EfficiencyEquation",
        eq8,
        {Efficiency, Power, Loss});

    //--------------------------------------------------
    // Eq9
    // Efficiency = constant
    //--------------------------------------------------

    auto eq9 =
        builder.subtract(
            builder.var(Efficiency),
            builder.constant(0.85));

    builder.equation(
        "EfficiencyTarget",
        eq9,
        {Efficiency});

    //--------------------------------------------------
    // Build Model
    //--------------------------------------------------

    auto model = builder.build();

    //--------------------------------------------------
    // Structural Graph
    //--------------------------------------------------

    auto graph =
        StructuralGraphBuilder::build(model);

    std::cout
        << "\n===== STRUCTURAL GRAPH =====\n";

    for (std::size_t equation = 0;
         equation < graph.equationVariables.size();
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

        std::cout << '\n';
    }

    //--------------------------------------------------
    // Matching
    //--------------------------------------------------

    auto matching =
        BipartiteMatcher::match(graph);

    std::cout
        << "\n===== MATCHING =====\n";

    for (std::size_t equation = 0;
         equation < matching.equationMatch.size();
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


    //--------------------------------------------------
    // Dependency Graph
    //--------------------------------------------------

    auto dependencyGraph =
        DependencyGraphBuilder::build(
            model,
            matching);

    std::cout
        << "\n===== DEPENDENCY GRAPH =====\n";

    for (std::size_t variable = 0;
         variable < dependencyGraph.dependencies.size();
         ++variable)
    {
        const auto& deps =
            dependencyGraph.dependencies[variable];

        if (deps.empty())
        {
            continue;
        }

        std::cout
            << model.variables[variable].name
            << " -> ";

        for (auto dependency : deps)
        {
            std::cout
                << model.variables[dependency].name
                << " ";
        }

        std::cout << '\n';
    }

    //--------------------------------------------------
    // Tarjan SCC
    //--------------------------------------------------

    auto sccResult =
        TarjanSCC::find(
            dependencyGraph);

    std::cout
        << "\n===== SCCs =====\n";

    for (std::size_t i = 0;
         i < sccResult.components.size();
         ++i)
    {
        std::cout
            << "SCC "
            << i
            << " : ";

        for (auto variable :
             sccResult.components[i].variables)
        {
            std::cout
                << model.variables[
                       variable].name
                << " ";
        }

        std::cout << '\n';
    }


    // Structural Block formation

    auto blockResult =
    BlockBuilder::build(
        model,
        matching,
        sccResult);

    std::cout
    << "\n===== STRUCTURAL BLOCKS =====\n";

for (const auto& block :
     blockResult.blocks)
{
    std::cout
        << "\nBlock "
        << block.id
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

    std::cout << '\n';

    std::cout
        << "Equations : ";

    for (auto equation :
         block.equations)
    {
        std::cout
            << model.equations[
                   equation].name
            << " ";
    }

    std::cout << '\n';
}

// -------------------------------
//  Block dependency Graph
// -------------------------------

auto blockGraph =
    BlockDependencyBuilder::build(
        dependencyGraph,
        sccResult,
        blockResult);

std::cout
    << "\n===== BLOCK GRAPH =====\n";

for (std::size_t block = 0;
     block <
     blockGraph.adjacency.size();
     ++block)
{
    std::cout
        << "Block "
        << block
        << " -> ";

    for (auto dependency :
         blockGraph.adjacency[block])
    {
        std::cout
            << dependency
            << " ";
    }

    std::cout
        << '\n';
}

// -----------------------------------------
// Execution Plan
// -----------------------------------------

auto executionPlan =
    TopologicalSorter::sort(
        blockGraph);

std::cout
    << "\n===== EXECUTION PLAN =====\n";

for (auto block :
     executionPlan.orderedBlocks)
{
    std::cout
        << "Block "
        << block
        << '\n';
}

// ----------------------------------
// Classification
// ----------------------------------

auto classification =
    BlockClassifier::classify(
        blockResult);
std::cout
    << "\n===== BLOCK CLASSIFICATION =====\n";

for (const auto& block :
     classification.blocks)
{
    std::cout
        << "Block "
        << block.block.id
        << " : ";

    switch (block.type)
    {
        case BlockType::DirectSolve:
            std::cout
                << "DirectSolve";
            break;

        case BlockType::AlgebraicLoop:
            std::cout
                << "AlgebraicLoop";
            break;

        default:
            std::cout
                << "Unknown";
    }

    std::cout << '\n';
}

// -------------------------------------
//  Execution Plan
//--------------------------------------

auto solverPlan =
    SolverPlanner::build(
        executionPlan,
        classification);

std::cout
    << "\n===== SOLVER PLAN =====\n";

for (const auto& step :
     solverPlan.steps)
{
    std::cout
        << "Block "
        << step.blockId
        << " : ";

    switch (step.blockType)
    {
        case BlockType::DirectSolve:
            std::cout
                << "DirectSolve";
            break;

        case BlockType::AlgebraicLoop:
            std::cout
                << "AlgebraicLoop";
            break;

        default:
            std::cout
                << "Unknown";
    }

    std::cout << '\n';
}
    return 0;
}