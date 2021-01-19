#pragma once
#include<string>


struct ImageData;

// IMPORTANT
// IMPORTANT
// IMPORTANT
// IMPORTANT

// The file reading system is implemented in c++ std file io.
// Thats slow man, so just change it to c std file io.

namespace PX {

	namespace IO {
		// File Reading
		std::string Read_from_file(const char* path);

		ImageData Read_Image(const char* path);
		void FreeImage(unsigned char* pixels);




		// File Writing
		bool AppendToFile(const char* filePath, const char* string);
		bool WriteToFile(const char* filePath, const char* string);
	}


}