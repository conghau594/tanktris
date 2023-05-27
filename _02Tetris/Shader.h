#ifndef SHADER_H
#define SHADER_H

#include "common_lib.h"

/* class definition in OpenGLMode */
namespace OpenGLMode {
	class Shader {
	public:
		// contructors, destructor, assigment operator
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator= (const Shader&) = delete;

		explicit Shader(GLenum _glEnumOfType, const char* _path);

		inline ~Shader() {
			delete source;
			glDeleteShader(shader_id);
		}

		//public method
		inline GLuint GetID() const { return shader_id; }

		//public class
		class Program;

	private:
		GLchar* source;			// the source code of shader
		GLuint  shader_id;		// the id of shader, i.e the return of glCreateShader function
		GLenum  type;			// the type of shader enumerated by OpenGLMode, for example: GL_VERTEX_SHADER... 

		//private method
		void compile_shader();
		void print_source();
		std::string get_shader_name();

	};
}

/* class definition in ConsoleMode */
// no need the class in this mode
namespace ConsoleMode {

	class Shader {
	public:
		// contructors, destructor, assigment operator
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator= (const Shader&) = delete;
		~Shader() = default;

		inline Shader(GLenum _glEnumOfType, const char* _path) { return; };

		//public method
		inline GLuint GetID(void) const { return 0; };

		//public class
		class Program;

	private:
		/* no need the properties */
		/*
		GLchar* source;			// the source code of shader
		GLuint  shader_id;		// the id of shader, i.e the return of glCreateShader function
		GLenum  type;			// the type of shader enumerated by OpenGLMode, for example: GL_VERTEX_SHADER... 
		//*/

		//private method
		void compile_shader(void) { return; };
		void print_source(void) { return; };
		std::string get_shader_name(void) { return "\0"; };
	};
}

#endif
