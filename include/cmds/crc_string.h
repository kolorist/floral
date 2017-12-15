#ifndef __FLORAL_CRCSTRING_H__
#define __FLORAL_CRCSTRING_H__

#include <stdaliases.h>

namespace floral {
	class crc_string {
		public:
			crc_string();
			explicit crc_string(const_cstr nullTerminatedStr);

			// operator overloading
			const bool									operator==(const crc_string& other) const;
			crc_string&									operator=(const crc_string& other);

		public:
			u32											crc32;

			// for debugging purpose
			c8											c_str[256];
	};
}

#endif // __FLORAL_CRCSTRING_H__
