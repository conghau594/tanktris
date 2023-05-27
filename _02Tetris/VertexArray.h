#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffer.h"

/* class definition in OpenGLMode */
namespace OpenGLMode {
	class VertexArray {
	public:
		//the unique contructor and destructor
		explicit VertexArray() { glGenVertexArrays(1, &vertex_arr_id); }
		~VertexArray() {
			//glBindVertexArray(0);
			glDeleteVertexArrays(1, &vertex_arr_id);
		}

		//delete other contructors and assignment operator
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator= (const VertexArray&) = delete;

		//public methods
		GLuint GetID(void) const { return vertex_arr_id; }
		void Bind(void) { glBindVertexArray(vertex_arr_id); }

		void SetVertexAttribute(const Buffer& _fromBuffer, GLuint _toLocation, GLint _numComponents,
			GLenum _glEnumOfAttribType, GLboolean _normalized, GLsizei _strideInByte, void* _offsetInByte) {

			glBindVertexArray(vertex_arr_id);
			glBindBuffer(_fromBuffer.GetType(), _fromBuffer.GetID());
			glVertexAttribPointer(_toLocation, _numComponents, _glEnumOfAttribType, _normalized, _strideInByte, (void*)_offsetInByte);
		}

		//public static methods
		static void EnableVertexAttribute(const VertexArray& _vao, GLuint _location) {
			glEnableVertexArrayAttrib(_vao.GetID(), _location);
		}
		static void DisableVertexAttribute(const VertexArray& _vao, GLuint _location) {
			glDisableVertexArrayAttrib(_vao.GetID(), _location);
		}
	private:
		GLuint vertex_arr_id;
	};
}


/* class definition in ConsoleMode*/
//no need the class
namespace ConsoleMode {
	class VertexArray {
	public:
		//the contructors and destructor
		VertexArray() = default;
		~VertexArray() = default;

		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator= (const VertexArray&) = delete;

		//the public methods
		GLuint GetID(void) const { return 0; }
		void Bind(void) { return; }

		void SetVertexAttribute(const Buffer& _fromBuffer, GLuint _toLocation, GLint _numComponents,
			GLenum _glEnumOfAttribType, GLboolean _normalized, GLsizei _strideInByte, void* _offsetInByte) { return; }

		//the public static methods
		static void EnableVertexAttribute(const VertexArray& _vao, GLuint _location) { return; }
		static void DisableVertexAttribute(const VertexArray& _vao, GLuint _location) { return; }

	private:
		/* no need the property */
		//GLuint vertex_arr_id;
	};
}


#endif

