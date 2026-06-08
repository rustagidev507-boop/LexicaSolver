#include <lexica/execute/SolverSelector.hpp>

namespace lexica
{
    std::vector<SolverSelection>
    SolverSelector::select(
        const ClassificationResult&
            classification)
    {
        std::vector<SolverSelection>
            result;

        result.reserve(
            classification.blocks.size());

        for (const auto& block :
             classification.blocks)
        {
            SolverSelection selection;

            selection.blockId =
                block.block.id;

            selection.blockType =
                block.type;

            switch (block.type)
            {
                case BlockType::DirectSolve:
                {
                    selection.solverType =
                        SolverType::
                            DirectSubstitution;

                    break;
                }

                case BlockType::AlgebraicLoop:
                {
                    selection.solverType =
                        SolverType::
                            NewtonRaphson;

                    break;
                }

                default:
                {
                    selection.solverType =
                        SolverType::None;
                }
            }

            result.push_back(
                std::move(selection));
        }

        return result;
    }
}