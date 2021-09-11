#pragma once

#include <stdexcept>

#include <fmt/core.h>

namespace minecase
{

    class NbtAccounter
    {
    public:
        static const NbtAccounter UNLIMITED;

    private:
        long quota;
        long usage;

    public:
        NbtAccounter(long p_128922_)
        {
            this->quota = p_128922_;
        }

        void accountBits(long p_128923_)
        {
            this->usage += p_128923_ / 8L;
            if (this->usage > this->quota)
            {
                throw std::runtime_error(fmt::format("Tried to read NBT tag that was too big; tried to allocate: {} bytes where max allowed: {}", this->usage, this->quota));
            }
        }

        std::string readUTF(std::string data)
        {
            accountBits(16); //Header length

            int len = data.length();
            int utflen = 0;

            for (int i = 0; i < len; i++)
            {
                std::size_t c = data.find(i);
                if ((c >= 0x0001) && (c <= 0x007F))
                    utflen += 1;
                else if (c > 0x07FF)
                    utflen += 3;
                else
                    utflen += 2;
            }
            accountBits(8 * utflen);

            return data;
        }
    };

}