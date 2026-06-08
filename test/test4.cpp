#include <iostream>
#include <vector>

#include <lexica/builder/ModelBuilder.hpp>

#include <lexica/runtime/EvaluationContext.hpp>
#include <lexica/runtime/ResidualEvaluator.hpp>
#include <lexica/runtime/JacobianEvaluator.hpp>
#include <lexica/runtime/VariableVector.hpp>

#include <lexica/solver/LinearSystemSolver.hpp>
#include <lexica/solver/NewtonSolver.hpp>

int main()
{
    using namespace lexica;

    ModelBuilder builder;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------

    auto x =
        builder.variable("x");

    auto y =
        builder.variable("y");

    //--------------------------------------------------
    // Eq0:
    // x² + y - 25 = 0
    //--------------------------------------------------

    auto eq0 =
        builder.subtract(
            builder.add(
                builder.power(
                    builder.var(x),
                    builder.constant(2.0)),
                builder.var(y)),
            builder.constant(25.0));

    auto eq0Id =
        builder.equation(
            "Eq0",
            eq0,
            {x, y});

    //--------------------------------------------------
    // Eq1:
    // x + y² - 20 = 0
    //--------------------------------------------------

    auto eq1 =
        builder.subtract(
            builder.add(
                builder.var(x),
                builder.power(
                    builder.var(y),
                    builder.constant(2.0))),
            builder.constant(20.0));

    auto eq1Id =
        builder.equation(
            "Eq1",
            eq1,
            {x, y});

    //--------------------------------------------------
    // Build Model
    //--------------------------------------------------

    auto model =
        builder.build();

    //--------------------------------------------------
    // Initial Guess
    //--------------------------------------------------

    VariableVector guess;

    guess.values.resize(
        model.variables.size());

    guess.values[x] = 3.0;
    guess.values[y] = 4.0;

    //--------------------------------------------------
    // Residual Test
    //--------------------------------------------------

    EvaluationContext context;

    context.variableValues =
        guess.values;

    auto residuals =
        ResidualEvaluator::evaluateModel(
            model,
            context);

    std::cout
        << "===== RESIDUALS =====\n";

    for (double value :
         residuals.values)
    {
        std::cout
            << value
            << '\n';
    }

    //--------------------------------------------------
    // Jacobian Test
    //--------------------------------------------------

    std::vector<EquationId>
        equations =
        {
            eq0Id,
            eq1Id
        };

    std::vector<VariableId>
        variables =
        {
            x,
            y
        };

    auto jacobian =
        JacobianEvaluator::evaluateBlock(
            model,
            equations,
            variables,
            context);

    std::cout
        << "\n===== JACOBIAN =====\n";

    for (const auto& row :
         jacobian.values)
    {
        for (double value :
             row)
        {
            std::cout
                << value
                << " ";
        }

        std::cout
            << '\n';
    }

    //--------------------------------------------------
    // Linear Solver Test
    //--------------------------------------------------

    auto linearResult =
        LinearSystemSolver::solve(
            jacobian,
            residuals);

    std::cout
        << "\n===== LINEAR SOLUTION =====\n";

    for (double value :
         linearResult.solution)
    {
        std::cout
            << value
            << '\n';
    }

    //--------------------------------------------------
    // Newton Solver Test
    //--------------------------------------------------

    auto result =
        NewtonSolver::solve(
            model,
            equations,
            variables,
            guess);

    std::cout
        << "\n===== NEWTON RESULT =====\n";

    std::cout
        << "Converged : "
        << std::boolalpha
        << result.converged
        << '\n';

    std::cout
        << "Iterations : "
        << result.iterations
        << '\n';

    std::cout
        << "x = "
        << result.solution.values[x]
        << '\n';

    std::cout
        << "y = "
        << result.solution.values[y]
        << '\n';

    return 0;
}