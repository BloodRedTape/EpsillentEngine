#ifndef GUID_H
#define GUID_H

#include <array>
#include <string>
#include "core/typedefs.hpp"

class GUID{
private:
    std::array<unsigned char,16> guid;
public:
    GUID();
    GUID(const GUID &other) = default;
    GUID &operator=(const GUID &other) = default;
    GUID(GUID &&other) = default;
    GUID &operator=(GUID &other)=default;
    
    bool operator==(const GUID &other) const;
    bool operator!=(const GUID &other) const;

    operator std::string()const;

    const std::array<unsigned char, 16>& bytes() const;

    void clear();

};


namespace std
{

	template <>
	struct hash<GUID>
	{
		std::size_t operator()(GUID const &guid) const
		{
			std::size_t hash = 0;
            auto bytes = guid.bytes();
            for(int i = 0; i< sizeof(GUID); i++){
                hash += (long((bytes[i] << 4) | (bytes[i] >> 4)) | bytes[i]<<9)*0x934632;
            }
            return hash;
		}
	};
}

#endif