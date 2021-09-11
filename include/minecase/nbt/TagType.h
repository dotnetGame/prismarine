#pragma once
#include <string>

namespace minecase
{

    template <typename T>
    class TagType
    {
        // T load(DataInput p_129379_, int p_129380_, NbtAccounter p_129381_);

        bool isValue()
        {
            return false;
        }

        virtual std::string getName() = 0;

        virtual std::string getPrettyName() = 0;
    };
}