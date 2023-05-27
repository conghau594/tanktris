#include "Shader.h"

namespace OpenGLMode {
	/*
	- inline Shader::~Shader();
	- inline GLuint Shader::GetID() const;
	*/

	/* contructor */
	Shader::Shader(GLenum _glEnumOfType, const char* _path) :
		type(_glEnumOfType),
		shader_id(glCreateShader(_glEnumOfType))
	{
		std::ifstream shaderFile(_path);

		if (!shaderFile.good())
			std::cerr << "ERROR!... Failed to open " << _path << std::endl;

		std::stringstream shaderBuffer;
		shaderBuffer << shaderFile.rdbuf();
		shaderFile.close();

		size_t sourceLen = shaderBuffer.str().length() + 1;
		source = new GLchar[sourceLen];

		memcpy(source, shaderBuffer.str().c_str(), sourceLen);
		compile_shader();
		//print_source();
	}

	/* private methods */
	void Shader::print_source() {
		std::cout
			<< "------------------------------------------------------------------\n"
			<< "                 " << get_shader_name() << " SOURCE\n"
			<< "..................................................................\n"
			<< source << "\n"
			<< "..................................................................\n";
	}

	void Shader::compile_shader() {
		glShaderSource(shader_id, 1, &source, NULL);
		glCompileShader(shader_id);

		GLint success = 0;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
			std::cerr << "ERROR!... Failed to compile "
				<< get_shader_name() << std::endl;
		}
	}

	std::string Shader::get_shader_name() {
		switch (type) {
		case GL_VERTEX_SHADER:
			return "VERTEX SHADER";
		case GL_FRAGMENT_SHADER:
			return "FRAGMENT SHADER";
		case GL_GEOMETRY_SHADER:
			return "GEOMETRY SHADER";
		case GL_TESS_CONTROL_SHADER:
			return "TESS CONTROL SHADER";
		case GL_TESS_EVALUATION_SHADER:
			return "TESS EVALUATION SHADER";
		default:
			return "ERROR!... The type specified for this instance does not represent a shader";
		}
	}
}