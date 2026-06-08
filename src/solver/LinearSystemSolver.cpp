#include <cmath>

#include <lexica/solver/LinearSystemSolver.hpp>

namespace lexica
{
    LinearSolveResult
    LinearSystemSolver::solve(
        const JacobianMatrix& jacobian,
        const ResidualVector& residuals)
    {
        LinearSolveResult result;

        const std::size_t n =
            jacobian.values.size();

        if (n == 0)
        {
            result.success = true;
            return result;
        }

        //--------------------------------------------------
        // Build Augmented Matrix
        //
        // [ J | -F ]
        //--------------------------------------------------

        std::vector<
            std::vector<double>
        > matrix(
            n,
            std::vector<double>(
                n + 1,
                0.0));

        for (std::size_t row = 0;
             row < n;
             ++row)
        {
            for (std::size_t col = 0;
                 col < n;
                 ++col)
            {
                matrix[row][col] =
                    jacobian.values[row][col];
            }

            matrix[row][n] =
                -residuals.values[row];
        }

        //--------------------------------------------------
        // Forward Elimination
        //--------------------------------------------------

        for (std::size_t pivot = 0;
             pivot < n;
             ++pivot)
        {
            //--------------------------------------------------
            // Partial Pivoting
            //--------------------------------------------------

            std::size_t bestRow =
                pivot;

            double bestValue =
                std::abs(
                    matrix[pivot][pivot]);

            for (std::size_t row =
                     pivot + 1;
                 row < n;
                 ++row)
            {
                const double value =
                    std::abs(
                        matrix[row][pivot]);

                if (value > bestValue)
                {
                    bestValue =
                        value;

                    bestRow =
                        row;
                }
            }

            if (bestValue < 1e-12)
            {
                result.success =
                    false;

                return result;
            }

            if (bestRow != pivot)
            {
                std::swap(
                    matrix[pivot],
                    matrix[bestRow]);
            }

            //--------------------------------------------------
            // Eliminate
            //--------------------------------------------------

            for (std::size_t row =
                     pivot + 1;
                 row < n;
                 ++row)
            {
                const double factor =
                    matrix[row][pivot]
                    /
                    matrix[pivot][pivot];

                for (std::size_t col =
                         pivot;
                     col <= n;
                     ++col)
                {
                    matrix[row][col]
                        -=
                        factor
                        *
                        matrix[pivot][col];
                }
            }
        }

        //--------------------------------------------------
        // Back Substitution
        //--------------------------------------------------

        result.solution.resize(
            n,
            0.0);

        for (int row =
                 static_cast<int>(n) - 1;
             row >= 0;
             --row)
        {
            double value =
                matrix[row][n];

            for (std::size_t col =
                     row + 1;
                 col < n;
                 ++col)
            {
                value -=
                    matrix[row][col]
                    *
                    result.solution[col];
            }

            result.solution[row] =
                value
                /
                matrix[row][row];
        }

        result.success = true;

        return result;
    }
}