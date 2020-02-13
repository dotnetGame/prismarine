#ifndef PRISMARINE_GRAIN_GRAIN_H_
#define PRISMARINE_GRAIN_GRAIN_H_

#include <vector>

#include <pplx/pplxtasks.h>

namespace prismarine
{
    class Grain
    {
        virtual pplx::task<void> OnActivated() = 0;
        virtual pplx::task<void> OnDeactivated() = 0;
        virtual pplx::task<void> Tell() = 0;
    };
}

#endif // PRISMARINE_GRAIN_GRAIN_H_