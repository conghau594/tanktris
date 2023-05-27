#include "Buffer.h"

/* */
/*
- Buffer(GLenum _type)
- ~Buffer()
- GLuint GetID() const
- GLenum GetType() const
- void Bind()
- void SubstituteData(GLintptr _fromByte, GLsizeiptr _sizeInByte, const void* _dataArray)
*/

/* public method definition */
namespace OpenGLMode {
	void Buffer::SetData(GLsizeiptr _sizeInByte, const void* _dataArray, GLenum _drawMode) {
		glBindBuffer(buffer_type, buffer_id);
		glBufferData(buffer_type, _sizeInByte, _dataArray, _drawMode);

		GLint bufferSize;
		glGetBufferParameteriv(buffer_type, GL_BUFFER_SIZE, &bufferSize);
		if (bufferSize != _sizeInByte)
			std::cerr << "ERROR!... Something wrong while setting data for the buffer with ID: "
			<< buffer_id << std::endl;
	}
}