#pragma once


#include <minecase/nbt/Tag.h>
#include <minecase/nbt/TagType.h>
#include <minecase/nbt/NBTAccounter.h>

namespace minecase
{
    class EndTag;
    
    class EndTagType: TagType<EndTag>
    {
        public:
        /*
        EndTag load(DataInput p_128550_, int p_128551_, NbtAccounter p_128552_) {
            p_128552_.accountBits(64L);
            return EndTag::INSTANCE;
        }*/

        std::string getName() {
            return "END";
        }

        std::string getPrettyName() {
            return "TAG_End";
        }

        bool isValue() {
            return true;
        }
    };

    class EndTag: Tag
    {
    private:
        static const int SELF_SIZE_IN_BITS = 64;

    public:
        static const EndTagType TYPE;
    };
}