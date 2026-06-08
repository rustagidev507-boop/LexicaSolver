#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/analysis/EquationInfo.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Equation Analyzer
    |--------------------------------------------------------------------------
    |
    | Performs structural inspection of equations during the
    | analysis phase of the Lexica pipeline.
    |
    | The analyzer extracts information required by later
    | structural algorithms, allowing the system to reason about
    | equation-variable relationships without repeatedly
    | traversing expression trees.
    |
    | Typical Uses:
    |
    |     - Structural Graph Construction
    |     - Dependency Discovery
    |     - Equation Matching
    |     - Model Validation
    |
    | IMPORTANT:
    |
    | This component performs analysis only.
    |
    | It does NOT perform numerical evaluation, solving, or
    | execution planning.
    |
    */

    class EquationAnalyzer
    {
    public:

        // Analyze a single equation and extract structural data.
        static EquationInfo analyze(
            const Model& model,
            const Equation& equation);
    };
}