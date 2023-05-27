#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"

/* class definition in OpenGLMode */
namespace OpenGLMode {
	class Shader::Program {
	public:
		//contructor, destructor, assignment operator
		Program(const Program&) = delete;
		Program(Program&&) = delete;
		//Program& operator= (const Program&) = delete;

		//public methods
		inline explicit Program() { program_id = glCreateProgram(); }
		inline GLuint GetID() const { return program_id; }
		inline void Use() { glUseProgram(program_id); }


		//method template
		template <typename... Ts>
		void AttachShaders(const Shader& _firstShader, const Ts&... _Shaders);

	private:
		GLuint program_id;			// the id of program, i.e the return of glCreateProgram function
		void link_program();
		
		inline void AttachShaders(void) { link_program(); }	//just for stopping recursion
	};

	/* function template definition */
	template <typename... Ts>
	void Shader::Program::AttachShaders(const Shader& _firstShader, const Ts&... _Shaders) {
		GLuint _firstShaderID = _firstShader.GetID();
		glAttachShader(program_id, _firstShaderID);
		AttachShaders(_Shaders...);
		glDetachShader(program_id, _firstShaderID);
	}

	/* qualify template instantiations with extern */
	extern template void Shader::Program::AttachShaders<>(
		const Shader&
	);

	extern template void Shader::Program::AttachShaders<Shader>(
		const Shader&, 
		const Shader&
	);

	extern template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&, 
		const Shader&
	);
	
	extern template void Shader::Program::AttachShaders<Shader>(
		const Shader&, 
		const Shader&, 
		const Shader&, 
		const Shader&
	);

	extern template void Shader::Program::AttachShaders<Shader>(
		const Shader&,
		const Shader&, 
		const Shader&, 
		const Shader&, 
		const Shader&
	);
}


/* class definition in ConsoleMode */
//no need the class
namespace ConsoleMode {
	class Shader::Program {
	public:
		//contructor, destructor, assignment operator
		Program(const Program&) = delete;
		Program(Program&&) = delete;
		//Program& operator= (const Program&) = delete;

		//public methods
		inline Program() = default;
		inline GLuint GetID(void) const { return 0; }
		inline void Use(void) { return; }

		inline void AttachShaders(const Shader& _firstShader) { return; }

		//method template
		template <typename... Ts>
		void AttachShaders(const Shader& _firstShader, const Ts&... _Shaders) { return; };

	private:
		/* no need the property */
		//GLuint program_id;			// the id of program, i.e the return of glCreateProgram function
		void link_program(void) { return; }
	};
}

#endif