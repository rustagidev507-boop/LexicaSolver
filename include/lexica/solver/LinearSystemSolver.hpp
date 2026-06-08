#pragma once

#include <lexica/runtime/JacobianMatrix.hpp>
#include <lexica/runtime/ResidualVector.hpp>

#include <lexica/solver/LinearSolveResult.hpp>

namespace lexica
{
    class LinearSystemSolver
    {
    public:

        static LinearSolveResult solve(
            const JacobianMatrix& jacobian,
            const ResidualVector& residuals);
    };
}