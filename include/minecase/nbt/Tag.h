#pragma once

#include <cstddef>
#include <cstdint>

#include <string>

#include <minecase/nbt/TagType.h>

namespace minecase
{

    class Tag
    {
    protected:
        const static std::int32_t OBJECT_HEADER;
        const static std::int32_t ARRAY_HEADER;
        const static std::int32_t OBJECT_REFERENCE;
        const static std::int32_t STRING_SIZE;
        const static std::uint8_t TAG_END;
        const static std::uint8_t TAG_BYTE;
        const static std::uint8_t TAG_SHORT;
        const static std::uint8_t TAG_INT;
        const static std::uint8_t TAG_LONG;
        const static std::uint8_t TAG_FLOAT;
        const static std::uint8_t TAG_DOUBLE;
        const static std::uint8_t TAG_BYTE_ARRAY;
        const static std::uint8_t TAG_STRING;
        const static std::uint8_t TAG_LIST;
        const static std::uint8_t TAG_COMPOUND;
        const static std::uint8_t TAG_INT_ARRAY;
        const static std::uint8_t TAG_LONG_ARRAY;
        const static std::uint8_t TAG_ANY_NUMERIC;
        const static std::int32_t MAX_DEPTH;

        virtual std::string toString() = 0;

        virtual std::uint8_t getId() = 0;
    };
}