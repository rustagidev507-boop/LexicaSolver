#include <lexica/solver/BlockClassifier.hpp>

namespace lexica
{
    ClassificationResult
    BlockClassifier::classify(
        const BlockResult& blockResult)
    {
        ClassificationResult result;

        result.blocks.reserve(
            blockResult.blocks.size());

        for (const auto& block :
             blockResult.blocks)
        {
            ClassifiedBlock classified;

            classified.block = block;

            //--------------------------------------------------
            // Classification
            //--------------------------------------------------

            if (block.variables.size() == 1 &&
                block.equations.size() == 1)
            {
                classified.type =
                    BlockType::DirectSolve;
            }
            else
            {
                classified.type =
                    BlockType::AlgebraicLoop;
            }

            result.blocks.push_back(
                std::move(classified));
        }

        return result;
    }
}