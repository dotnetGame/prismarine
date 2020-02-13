#ifndef PRISMARINE_GRAIN_GRAIN_H_
#define PRISMARINE_GRAIN_GRAIN_H_

#include <vector>
#include <string>

#include <pplx/pplxtasks.h>

namespace prismarine
{
    class Grain
    {
    private:
        std::string identity_;
        std::string sub_identity_;
        std::string type_;
    public:
        virtual pplx::task<void> OnActivated() {}
        virtual pplx::task<void> OnDeactivated() {}
        virtual pplx::task<std::string> OnMessage(const std::string& name, const std::vector<std::string>& params) = 0;
    };

    class GrainRef
    {
    private:
        std::string identity_;
        std::string sub_identity_;
        std::string type_;
    public:
        pplx::task<std::string> Tell(const std::string& name, const std::vector<std::string>& params)
        {

        }
    };

    class GrainRefFactory
    {

    };
}

#endif // PRISMARINE_GRAIN_GRAIN_H_