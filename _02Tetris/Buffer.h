#ifndef BUFFER_H
#define BUFFER_H
#include "common_lib.h"

/* class definition in OpenGLMode */
namespace OpenGLMode {
	class Buffer {
	public:
		//contructors and destructor
		explicit Buffer(GLenum _type) : buffer_type(_type) {
			glGenBuffers(1, &buffer_id);
		}

		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(const Buffer&) = delete;

		~Buffer() { glDeleteBuffers(1, &buffer_id); }

		//the public method
		void SetData(GLsizeiptr _sizeInByte, const void* _dataArray, GLenum _drawMode);

		GLuint GetID(void) const { return buffer_id; }
		GLenum GetType(void) const { return buffer_type; }
		void Bind(void) { glBindBuffer(buffer_type, buffer_id); }
		void SubstituteData(GLintptr _fromByte, GLsizeiptr _sizeInByte, const void* _dataArray) {
			glNamedBufferSubData(buffer_id, _fromByte, _sizeInByte, _dataArray);
		}

	private:
		GLuint buffer_id;
		GLenum buffer_type;
	};
}


/* class definition in ConsoleMode */
//no need this class
namespace ConsoleMode {
	class Buffer {
	public:
		//contructors and destructor
		Buffer(GLenum _type) { return; }

		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		~Buffer() = default;

		//public method
		void SetData(GLsizeiptr _sizeInByte, const void* _dataArray, GLenum _drawMode) { return; }

		GLuint GetID(void) const { return 0; }
		GLenum GetType(void) const { return 0; }
		void Bind(void) { return; }
		void SubstituteData(GLintptr _fromByte, GLsizeiptr _sizeInByte, const void* _dataArray) { return; }

	private:
		/* no need the properties */
		/*
		GLuint buffer_id;
		GLenum buffer_type;
		*/
	};
}

#endif