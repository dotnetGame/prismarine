#ifndef PRISMARINE_GRAIN_GRAIN_H_
#define PRISMARINE_GRAIN_GRAIN_H_

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <memory>

#include <pplx/pplxtasks.h>
#include <msgpack.hpp>

namespace prismarine
{
    class PersistentState
    {
    public:
        msgpack::object State;
        std::string Etag;
        pplx::task<void> ClearStateAsync() {}
        pplx::task<void> WriteStateAsync() {}
        pplx::task<void> ReadStateAsync() {}
    };

    class Grain : public PersistentState
    {
    public:
        using adaptor_type = std::function<std::unique_ptr<msgpack::object_handle>(msgpack::object const&)>;
    private:
        std::string identity_;
        std::string sub_identity_;
        std::string type_;

        std::unordered_map<std::string, adaptor_type> funcs_;
    public:
        template<typename F>
        void RegisterMethod(const std::string& name, F func)
        {
            funcs_.insert(
                std::make_pair(name, [func, name](msgpack::object const& args) {
                    
                    }
                )
            );
        }
    };

    class GrainRef
    {
    private:
        std::string identity_;
        std::string sub_identity_;
        std::string type_;
    public:
        template <typename... Args>
        msgpack::object_handle Call(const std::string& func_name, Args... args)
        {
            auto arg_tuple = std::make_tuple(args...);
            msgpack::sbuffer sbuf;
            msgpack::pack(sbuf, arg_tuple);
            
        }
    };


    class MembershipItem
    {

    };

    class Membership : public Grain
    {
    public:
        Membership()
        {
            this->RegisterMethod("GetMembers", [this]() { return this->GetMembers(); });
        }

        pplx::task<std::vector<MembershipItem>> GetMembers()
        {

        }
    };
}

#endif // PRISMARINE_GRAIN_GRAIN_H_