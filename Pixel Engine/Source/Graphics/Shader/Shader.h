#pragma once

#define INVALID_UNIFORM	4294967295
#define SHADER_DEBUG 1
#define UNIFORM_DEBUG 0
#define LOG_SHADERS 0

#include"Vector.h"
#include"Matrix.h"
#include"Shader_Code.h"

namespace PX {

	namespace graphics {

		class Shader {

			unsigned int programID;
			unsigned int vertexID;
			unsigned int fragmentID;

			Shader_Code source;

		public:
			Shader(const char* shaderFile = "");
			Shader(const Shader& shader);
			~Shader();

			void Reset(const char* shaderFile);

			void Build();
			void Activate() const;
			void Deactivate() const;

			void Uniform1i(const char* var, const int& x);
			void Uniform2i(const char* var, const int& x, const int& y);
			void Uniform3i(const char* var, const int& x, const int& y, const int& z);
			void Uniform4i(const char* var, const int& x, const int& y, const int& z, const int& w);

			void Uniform1iv(const char* var, const int* valPtr, const int& count);
			void Uniform2iv(const char* var, const int* valPtr, const int& count);
			void Uniform3iv(const char* var, const int* valPtr, const int& count);
			void Uniform4iv(const char* var, const int* valPtr, const int& count);

			void Uniform1f(const char* var, const float& x);
			void Uniform2f(const char* var, const float& x, const float& y);
			void Uniform3f(const char* var, const float& x, const float& y, const float& z);
			void Uniform4f(const char* var, const float& x, const float& y, const float& z, const float& w);

			void Uniform2f(const char* var, const Math::Vector2& v);
			void Uniform3f(const char* var, const Math::Vector3& v);
			void Uniform4f(const char* var, const Math::Vector4& v);

			void Uniform1fv(const char* var, const float* valPtr, const int& count);
			void Uniform2fv(const char* var, const float* valPtr, const int& count);
			void Uniform3fv(const char* var, const float* valPtr, const int& count);
			void Uniform4fv(const char* var, const float* valPtr, const int& count);



			// UniforMat2 and UniforMat3 are not robust right now. Only
			// the use of UniformMat4 is recommended.
			void UniformMat2(const char* var, const Math::mat2& mat);
			void UniformMat3(const char* var, const Math::mat3& mat);
			void UniformMat4(const char* var, const Math::mat4& mat);

			void UniformMat2v(const char* var, const int& count, const float* data);
			void UniformMat3v(const char* var, const int& count, const float* data);
			void UniformMat4v(const char* var, const int& count, const float* data);


			unsigned int GetProgramID() const { return this->programID; }

		private:
			void Compile();
			void Link();

			void InitShaders(const char* shaderFile);

			inline void HandleCompileErrors(unsigned int& id);
			inline void HandleLinkErrors();
			inline void ParseShader(std::string& source);
			std::string* ParsePreprocessors(std::string* shader, std::string& line);
		};


	}

}