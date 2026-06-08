#include <queue>

#include <lexica/planning/TopologicalSorter.hpp>

namespace lexica
{
    ExecutionPlan
    TopologicalSorter::sort(
        const BlockDependencyGraph& graph)
    {
        ExecutionPlan plan;

        const std::size_t blockCount =
            graph.adjacency.size();

        std::vector<std::size_t>
            inDegree(
                blockCount,
                0);

        //--------------------------------------------------
        // Compute In-Degree
        //--------------------------------------------------

        for (const auto& neighbours :
             graph.adjacency)
        {
            for (auto neighbour :
                 neighbours)
            {
                ++inDegree[neighbour];
            }
        }

        //--------------------------------------------------
        // Find Sources
        //--------------------------------------------------

        std::queue<std::size_t> queue;

        for (std::size_t block = 0;
             block < blockCount;
             ++block)
        {
            if (inDegree[block] == 0)
            {
                queue.push(block);
            }
        }

        //--------------------------------------------------
        // Kahn
        //--------------------------------------------------

        while (!queue.empty())
        {
            auto block =
                queue.front();

            queue.pop();

            plan.orderedBlocks.push_back(
                block);

            for (auto neighbour :
                 graph.adjacency[block])
            {
                --inDegree[neighbour];

                if (inDegree[neighbour] == 0)
                {
                    queue.push(
                        neighbour);
                }
            }
        }

        return plan;
    }
}