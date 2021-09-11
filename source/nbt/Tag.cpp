
#include <minecase/nbt/Tag.h>
namespace minecase
{
    const std::int32_t Tag::OBJECT_HEADER = 64;
    const std::int32_t Tag::ARRAY_HEADER = 96;
    const std::int32_t Tag::OBJECT_REFERENCE = 32;
    const std::int32_t Tag::STRING_SIZE = 224;
    const std::uint8_t Tag::TAG_END = 0;
    const std::uint8_t Tag::TAG_BYTE = 1;
    const std::uint8_t Tag::TAG_SHORT = 2;
    const std::uint8_t Tag::TAG_INT = 3;
    const std::uint8_t Tag::TAG_LONG = 4;
    const std::uint8_t Tag::TAG_FLOAT = 5;
    const std::uint8_t Tag::TAG_DOUBLE = 6;
    const std::uint8_t Tag::TAG_BYTE_ARRAY = 7;
    const std::uint8_t Tag::TAG_STRING = 8;
    const std::uint8_t Tag::TAG_LIST = 9;
    const std::uint8_t Tag::TAG_COMPOUND = 10;
    const std::uint8_t Tag::TAG_INT_ARRAY = 11;
    const std::uint8_t Tag::TAG_LONG_ARRAY = 12;
    const std::uint8_t Tag::TAG_ANY_NUMERIC = 99;
    const std::int32_t Tag::MAX_DEPTH = 512;
}