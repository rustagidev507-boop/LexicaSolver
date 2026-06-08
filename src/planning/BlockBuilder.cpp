#include <lexica/planning/BlockBuilder.hpp>

namespace lexica
{
    BlockResult
    BlockBuilder::build(
        const Model& model,
        const MatchingResult& matching,
        const SCCResult& sccResult)
    {
        BlockResult result;

        result.blocks.reserve(
            sccResult.components.size());

        for (std::size_t blockId = 0;
             blockId < sccResult.components.size();
             ++blockId)
        {
            const auto& component =
                sccResult.components[blockId];

            StructuralBlock block;

            block.id = blockId;

            //--------------------------------------------------
            // Variables
            //--------------------------------------------------

            block.variables =
                component.variables;

            //--------------------------------------------------
            // Equations
            //--------------------------------------------------

            for (auto variable :
                 component.variables)
            {
                auto equation =
                    matching.variableMatch[
                        variable];

                if (equation ==
                    InvalidEquationId)
                {
                    continue;
                }

                block.equations.push_back(
                    equation);
            }

            result.blocks.push_back(
                std::move(block));
        }

        return result;
    }
}