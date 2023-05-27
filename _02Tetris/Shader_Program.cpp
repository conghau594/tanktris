#include "Shader_Program.h"

namespace OpenGLMode {
	/* 
	- inline Program()
	- inline GLuint GetID() const
	- inline void Use()
	- inline void AttachShaders(const Shader& _firstShader)
	*/

	/* private method */
	void Shader::Program::link_program() {
		glLinkProgram(program_id);

		GLint success = 0;
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);

		if (!success) {
			GLchar infoLog[1024];
			glGetProgramInfoLog(program_id, 1024, NULL, infoLog);
			std::cerr << "ERORR!... Failed to attach shaders or link program\n" << infoLog << std::endl;
		}
	}

	/* explicit template instantiations */
	template void Shader::Program::AttachShaders<>(
		const Shader&
	);

	template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&
	);

	template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&,
		const Shader&
	);

	template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&,
		const Shader&,
		const Shader&
	);

	template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&,
		const Shader&,
		const Shader&,
		const Shader&
	);
}

