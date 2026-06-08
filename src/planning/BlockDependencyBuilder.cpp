#include <unordered_set>

#include <lexica/planning/BlockDependencyBuilder.hpp>

namespace lexica
{
    BlockDependencyGraph
    BlockDependencyBuilder::build(
        const DependencyGraph& dependencyGraph,
        const SCCResult& sccResult,
        const BlockResult& blockResult)
    {
        (void)blockResult;

        BlockDependencyGraph graph;

        graph.adjacency.resize(
            sccResult.components.size());

        std::vector<
            std::unordered_set<std::size_t>
        > uniqueEdges(
            sccResult.components.size());

        //--------------------------------------------------
        // Variable Dependency
        //     ↓
        // Block Dependency
        //--------------------------------------------------

        for (std::size_t variable = 0;
             variable <
             dependencyGraph.dependencies.size();
             ++variable)
        {
            const auto sourceBlock =
                sccResult.componentOfVariable[
                    variable];

            for (auto dependency :
                 dependencyGraph.dependencies[
                     variable])
            {
                const auto targetBlock =
                    sccResult.componentOfVariable[
                        dependency];

                if (sourceBlock ==
                    targetBlock)
                {
                    continue;
                }

                //--------------------------------------------------
                // dependency -> variable
                //
                // provider -> consumer
                //--------------------------------------------------

                uniqueEdges[targetBlock]
                    .insert(sourceBlock);
            }
        }

        //--------------------------------------------------
        // Convert Sets → Adjacency
        //--------------------------------------------------

        for (std::size_t block = 0;
             block < uniqueEdges.size();
             ++block)
        {
            graph.adjacency[block].assign(
                uniqueEdges[block].begin(),
                uniqueEdges[block].end());
        }

        return graph;
    }
}