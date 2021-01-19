#include<fstream>
#include<SOIL2/SOIL2.h>
#include<iostream>


#include"FileReader.h"

#include"../../Graphics/ImageData.h"


namespace PX {
	namespace IO {


		// // // // // // // //
		// // // // // // // //
		//
		// File Reading
		//
		// // // // // // // //
		// // // // // // // //

		std::string Read_from_file(const char *const path) {
			FILE* file = fopen(path, "rt");

			if (!file) {
				std::cerr << "Could not find the file " << path << '\n';
				return "";
			}

			fseek(file, 0, SEEK_END);
			unsigned int length = ftell(file);
			char *source = new char[length + 1];
			memset(source, 0, length + 1);

			fseek(file, 0, SEEK_SET);
			fread(source, sizeof(char), length, file);

			std::string ret(source);
			delete[] source;
			return ret;
		}












		ImageData Read_Image(const char* path)
		{
			ImageData image;
			image.pixels = SOIL_load_image(path, &image.width, &image.height, &image.BPP, SOIL_LOAD_RGBA);

			return image;
		}

		void FreeImage(unsigned char* pixels)
		{
			SOIL_free_image_data(pixels);
		}

		// // // // // // // //
		// // // // // // // //
		//
		// File Writing
		//
		// // // // // // // //
		// // // // // // // //

		bool AppendToFile(const char* const filePath, const char* const string) {
			FILE* file = fopen(filePath, "ab");

			if (!file)
				return false;

			fwrite(string, sizeof(char), strlen(string), file);
			fclose(file);

			return true;
		}

		bool WriteToFile(const char* filePath, const char* string)
		{
			FILE* file = fopen(filePath, "wb");

			if (!file)
				return false;

			fwrite(string, sizeof(char), strlen(string), file);
			fclose(file);

			return true;
		}

	}

}