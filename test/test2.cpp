#include <iostream>

#include <lexica/builder/ModelBuilder.hpp>

#include <lexica/analysis/StructuralGraphBuilder.hpp>

#include <lexica/matching/BipartiteMatcher.hpp>

#include <lexica/graph/DependencyGraphBuilder.hpp>

int main()
{
    using namespace lexica;

    ModelBuilder builder;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------

    auto A = builder.variable("A");
    auto B = builder.variable("B");
    auto C = builder.variable("C");
    auto D = builder.variable("D");
    auto E = builder.variable("E");

    //--------------------------------------------------
    // Eq0 -> A B
    //--------------------------------------------------

    auto eq0 =
        builder.subtract(
            builder.var(A),
            builder.var(B));

    builder.equation(
        "Eq0",
        eq0,
        {A, B});

    //--------------------------------------------------
    // Eq1 -> B C
    //--------------------------------------------------

    auto eq1 =
        builder.subtract(
            builder.var(B),
            builder.var(C));

    builder.equation(
        "Eq1",
        eq1,
        {B, C});

    //--------------------------------------------------
    // Eq2 -> C D
    //--------------------------------------------------

    auto eq2 =
        builder.subtract(
            builder.var(C),
            builder.var(D));

    builder.equation(
        "Eq2",
        eq2,
        {C, D});

    //--------------------------------------------------
    // Eq3 -> D E
    //--------------------------------------------------

    auto eq3 =
        builder.subtract(
            builder.var(D),
            builder.var(E));

    builder.equation(
        "Eq3",
        eq3,
        {D, E});

    //--------------------------------------------------
    // Eq4 -> E
    //--------------------------------------------------

    auto eq4 =
        builder.subtract(
            builder.var(E),
            builder.constant(10.0));

    builder.equation(
        "Eq4",
        eq4,
        {E});

    //--------------------------------------------------
    // Eq5 -> A
    //--------------------------------------------------

    auto eq5 =
        builder.subtract(
            builder.var(A),
            builder.constant(5.0));

    builder.equation(
        "Eq5",
        eq5,
        {A});

    //--------------------------------------------------
    // Build Model
    //--------------------------------------------------

    auto model =
        builder.build();

    //--------------------------------------------------
    // Structural Graph
    //--------------------------------------------------

    auto graph =
        StructuralGraphBuilder::build(
            model);

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
        BipartiteMatcher::match(
            graph);

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

    return 0;
}