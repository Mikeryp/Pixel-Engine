#pragma once
#define MAX_SHADERS 10
#define Log(x) std::cout << x << '\n'
 
#include"GL\glew.h"
#include"Shader.h"
				   
#include"../../Utils/IO/FileReader.h"

#include<iostream>
#include<string>

namespace PX {

namespace graphics {



		Shader::Shader(const char* shaderFile)
			:
			programID(glCreateProgram()),
			vertexID(glCreateShader(GL_VERTEX_SHADER)),
			fragmentID(glCreateShader(GL_FRAGMENT_SHADER))
		{
			if (strlen(shaderFile) > 0) {
				this->InitShaders(shaderFile);
				this->Build();
			}
		}


		Shader::Shader(const Shader& shader)
			:
			programID(glCreateProgram()),
			vertexID(glCreateShader(GL_VERTEX_SHADER)),
			fragmentID(glCreateShader(GL_FRAGMENT_SHADER))
		{
			this->source.vertex = shader.source.vertex;
			this->source.fragment = shader.source.fragment;

			this->Build();
		}

		Shader::~Shader()
		{
			if (this->vertexID != 0)
				glDeleteShader(this->vertexID);

			if (this->fragmentID != 0)
				glDeleteShader(this->fragmentID);

			if (this->programID != 0)
				glDeleteProgram(this->programID);

			this->source.vertex.clear();
			this->source.fragment.clear();
		}



		void Shader::InitShaders(const char* shaderFile)
		{
			std::string code = IO::Read_from_file(shaderFile);
			this->ParseShader(code);

			const char* vertexSource = this->source.vertex.c_str();
			const char* fragmentSource = this->source.fragment.c_str();

			glShaderSource(this->vertexID, 1, &vertexSource, 0);
			glShaderSource(this->fragmentID, 1, &fragmentSource, 0);
		}



		void Shader::Reset(const char* shaderFile)
		{
			this->InitShaders(shaderFile);
			this->Build();
		}

		void Shader::Build()
		{
			this->Compile();
			this->Link();
		}

		void Shader::Compile()
		{
			glCompileShader(this->vertexID);
			this->HandleCompileErrors(this->vertexID);
			glCompileShader(this->fragmentID);
			this->HandleCompileErrors(this->fragmentID);
		}

		void Shader::Link()
		{
			glAttachShader(this->programID, this->vertexID);
			glAttachShader(this->programID, this->fragmentID);

			glLinkProgram(this->programID);
			this->HandleLinkErrors();
		}




		void Shader::HandleCompileErrors(unsigned int& shader) {
			int result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
#if SHADER_DEBUG == 1
				int length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				char* info = new char[length];
				memset(info, 0, length);
				glGetShaderInfoLog(shader, length, &length, info);

				if (shader == this->vertexID)
std::cout << "Vertex Shader:- \n";
				else
					std::cout << "Fragment Shader:- \n";

					std::cout << info << std::endl;
					delete[] info;
#endif

					glDeleteShader(shader);
					shader = 0;
			}
		}


		void Shader::HandleLinkErrors()
		{
			int result;
			glGetProgramiv(this->programID, GL_LINK_STATUS, &result);

			if (result == GL_FALSE) {
#if SHADER_DEBUG == 1
				int length;
				glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &length);

				char* info = new char[length];
				glGetProgramInfoLog(this->programID, length, &length, info);

				std::cout << "Linking issue:- ";
				std::cout << info << '\n';

				delete[] info;

#endif

				glDetachShader(this->programID, this->vertexID);
				glDetachShader(this->programID, this->fragmentID);

				glDeleteProgram(this->programID);
			}
		}


		void Shader::ParseShader(std::string& code)
		{
			std::string line;
			std::string *shader = nullptr;

			int length = code.length();
			int index = 0;

			while (index < length) {

				line = "";

				while (index < length && code.at(index) != '\n') {
					line.push_back(code.at(index++));
				}
				line.push_back('\n');
				index++;

				if (line.at(0) == '#') {
					shader = this->ParsePreprocessors(shader, line);
				}

				else 
					if (shader != nullptr)
					  *shader = *shader + line;


			}



			Log(this->source.vertex);
			Log(this->source.fragment);

		}


		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		// Not Completed
		std::string* Shader::ParsePreprocessors(std::string* shader, std::string& line) {
		
			bool write = false;

			if (line.find("shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					shader = &this->source.vertex;

				else if (line.find("fragment") != std::string::npos)
					shader = &this->source.fragment;
			}

			else if (line.find("include") != std::string::npos) {
				bool start = false;
				int size = 0;
				std::string fileName;

				for (int i = 0; i < line.length(); i++) {
					if (line.at(i) == '\"')
						start = !start;

					if (start)
						fileName.push_back(line.at(i));
				}

				if (start == true) {
					Log("Shader Error:- incomplete include directive");
					return nullptr;
				}

				std::string info = IO::Read_from_file(fileName.c_str());
				Log(info);
				line.replace(line.find("#include"), line.length() - 1, info);

				write = true;
			}

			else
				write = true;





			if (write)
				if (shader != nullptr)
					*shader = *shader + line;

			return shader;

        }





		void Shader::Activate() const { glUseProgram(this->programID); }
		void Shader::Deactivate() const { glUseProgram(0); }





		void Shader::Uniform1i(const char* var, const int& x) {
			GLuint loc = glGetUniformLocation(this->programID, var);

            if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1 == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif 
				return;
			}

			glUseProgram(this->programID);
			glUniform1i(loc, x);
			glUseProgram(0);
		}
		void Shader::Uniform2i(const char* var, const int& x, const int& y)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1 == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADERSHADER_DEBUG == 1 == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform2i(loc, x, y);
			glUseProgram(0);
		}
		void Shader::Uniform3i(const char* var, const int& x, const int& y, const int& z) {
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1 == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADERSHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform3i(loc, x, y, z);
			glUseProgram(0);
		}
		void Shader::Uniform4i(const char* var, const int& x, const int& y, const int& z, const int& w) {
			GLuint loc = glGetUniformLocation(this->programID, var);


			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1 == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif
				return;
			}

			glUseProgram(this->programID);
			glUniform4i(loc, x, y, z, w);
			glUseProgram(0);
		}












		void Shader::Uniform1iv(const char* var, const int* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform1iv(loc, count, valPtr);
			glUseProgram(0);
		}
		void Shader::Uniform2iv(const char* var, const int* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cerr << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform2iv(loc, count, valPtr);
			glUseProgram(0);
		}
		void Shader::Uniform3iv(const char* var, const int* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform3iv(loc, count, valPtr);
			glUseProgram(0);
		}
		void Shader::Uniform4iv(const char* var, const int* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform4iv(loc, count, valPtr);
			glUseProgram(0);
		}











		void Shader::Uniform1f(const char* var, const float& x)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform1f(loc, x);
			glUseProgram(0);
		}
		void Shader::Uniform2f(const char* var, const float& x, const float& y)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform2f(loc, x, y);
			glUseProgram(0);
		}
		void Shader::Uniform3f(const char* var, const float& x, const float& y, const float& z)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform3f(loc, x, y, z);
			glUseProgram(0);
		}
		void Shader::Uniform4f(const char* var, const float& x, const float& y, const float& z, const float& w)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform4f(loc, x, y, z, w);
			glUseProgram(0);
		}


		void Shader::Uniform2f(const char* var, const Math::Vector2& v)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
#if UNIFORM_DEBUG == 1
				std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform2f(loc, v.x, v.y);
			glUseProgram(0);
		}
		void Shader::Uniform3f(const char* var, const Math::Vector3& v)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
	#if UNIFORM_DEBUG == 1
			std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform3f(loc, v.x, v.y, v.z);
			glUseProgram(0);
		}

		void Shader::Uniform4f(const char* var, const Math::Vector4& v)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
	#if UNIFORM_DEBUG == 1
			std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform4f(loc, v.x, v.y, v.z, v.w);
			glUseProgram(0);
		}











		void Shader::Uniform1fv(const char* var, const float* valPtr, const int &count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform1fv(loc, count, valPtr);
			glUseProgram(0);
		}
		void Shader::Uniform2fv(const char* var, const float* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
		#if UNIFORM_DEBUG == 1
		std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform2fv(loc, count, valPtr);
			glUseProgram(0);
		}
		void Shader::Uniform3fv(const char* var, const float* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
		#if UNIFORM_DEBUG == 1
		std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform3fv(loc, count, valPtr);
			glUseProgram(0);

		}
		void Shader::Uniform4fv(const char* var, const float* valPtr, const int& count)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
		#if UNIFORM_DEBUG == 1
		std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniform4fv(loc, count, valPtr);
			glUseProgram(0);
		}

		void Shader::UniformMat2(const char* var, const Math::mat2& mat)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
		#if UNIFORM_DEBUG == 1
		std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix2fv(loc, 1, GL_FALSE, mat.elements);
			glUseProgram(0);
		}

		void Shader::UniformMat3(const char* var, const Math::mat3& mat)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
	#if UNIFORM_DEBUG == 1
			std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix3fv(loc, 1, GL_FALSE, mat.elements);
			glUseProgram(0);
		}

		void Shader::UniformMat4(const char* var, const Math::mat4& mat)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix4fv(loc, 1, GL_FALSE, mat.elements);
			glUseProgram(0);
		}

		void Shader::UniformMat2v(const char* var, const int& count, const float* data)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix2fv(loc, count, GL_FALSE, data);
			glUseProgram(0);
		}

		void Shader::UniformMat3v(const char* var, const int& count, const float* data)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix3fv(loc, count, GL_FALSE, data);
			glUseProgram(0);
		}

		void Shader::UniformMat4v(const char* var, const int& count, const float* data)
		{
			GLuint loc = glGetUniformLocation(this->programID, var);

			if (loc == INVALID_UNIFORM) {
				#if UNIFORM_DEBUG == 1
std::cout << "Uniform variable" + std::string(var) + " does not exist!\n";
#endif // SHADER_DEBUG == 1
				return;
			}

			glUseProgram(this->programID);
			glUniformMatrix4fv(loc, count, GL_FALSE, data);
			glUseProgram(0);
		}

} }