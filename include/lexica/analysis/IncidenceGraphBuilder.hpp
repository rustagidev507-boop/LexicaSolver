#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/analysis/IncidenceGraph.hpp>

namespace lexica
{
    class IncidenceGraphBuilder
    {
    public:

        static IncidenceGraph build(
            const Model& model);
    };
}