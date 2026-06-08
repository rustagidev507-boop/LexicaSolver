#include <lexica/graph/TarjanSCC.hpp>
#include <algorithm>

namespace lexica
{
    SCCResult
    TarjanSCC::find(
        const DependencyGraph& graph)
    {
        SCCResult result;

        const std::size_t variableCount =
            graph.dependencies.size();

        result.componentOfVariable.resize(
            variableCount,
            static_cast<std::size_t>(-1));

        std::vector<int> indices(
            variableCount,
            -1);

        std::vector<int> lowLinks(
            variableCount,
            -1);

        std::vector<bool> onStack(
            variableCount,
            false);

        std::stack<VariableId> stack;

        int currentIndex = 0;

        for (VariableId variable = 0;
             variable < variableCount;
             ++variable)
        {
            if (indices[variable] == -1)
            {
                strongConnect(
                    variable,
                    graph,
                    result,
                    indices,
                    lowLinks,
                    onStack,
                    stack,
                    currentIndex);
            }
        }

        return result;
    }

    void TarjanSCC::strongConnect(
        VariableId variable,
        const DependencyGraph& graph,
        SCCResult& result,
        std::vector<int>& indices,
        std::vector<int>& lowLinks,
        std::vector<bool>& onStack,
        std::stack<VariableId>& stack,
        int& currentIndex)
    {
        indices[variable] =
            currentIndex;

        lowLinks[variable] =
            currentIndex;

        ++currentIndex;

        stack.push(variable);

        onStack[variable] = true;

        //--------------------------------------------------
        // DFS over neighbours
        //--------------------------------------------------

        for (auto neighbour :
             graph.dependencies[variable])
        {
            if (indices[neighbour] == -1)
            {
                strongConnect(
                    neighbour,
                    graph,
                    result,
                    indices,
                    lowLinks,
                    onStack,
                    stack,
                    currentIndex);

                lowLinks[variable] =
                    std::min(
                        lowLinks[variable],
                        lowLinks[neighbour]);
            }
            else if (onStack[neighbour])
            {
                lowLinks[variable] =
                    std::min(
                        lowLinks[variable],
                        indices[neighbour]);
            }
        }

        //--------------------------------------------------
        // Root of SCC
        //--------------------------------------------------

        if (lowLinks[variable] !=
            indices[variable])
        {
            return;
        }

        SCC component;

        while (true)
        {
            auto member =
                stack.top();

            stack.pop();

            onStack[member] = false;

            component.variables.push_back(
                member);

            if (member == variable)
            {
                break;
            }
        }

        const std::size_t componentIndex =
            result.components.size();

        for (auto member :
             component.variables)
        {
            result.componentOfVariable[
                member] =
                    componentIndex;
        }

        result.components.push_back(
            std::move(component));
    }
}