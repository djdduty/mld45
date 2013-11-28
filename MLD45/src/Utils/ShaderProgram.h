// * http://www.lighthouse3d.com/very-simple-libs


#ifndef __ShaderProgram__
#define __ShaderProgram__

#include <string>
#include <vector>
#include <map>
#include <Core/PlatformIncludes.h>


namespace MLD {

class ShaderProgram
{
public:
	
	/// Types of Vertex Attributes
	enum AttribType {
		VERTEX_COORD_ATTRIB,
		NORMAL_ATTRIB,
		TEXTURE_COORD_ATTRIB,
		TANGENT_ATTRIB,
		BITANGENT_ATTRIB,
		VERTEX_ATTRIB1,
		VERTEX_ATTRIB2,
		VERTEX_ATTRIB3,
		VERTEX_ATTRIB4
	};

	/// Types of Shaders
	enum ShaderType {
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVAL_SHADER,
		FRAGMENT_SHADER,
		COUNT_SHADER_TYPE
	};

	/// Just a helper define
	static const int MAX_TEXTURES = 8;

    ShaderProgram();
	~ShaderProgram();
	void init();
	void loadShader(ShaderProgram::ShaderType st, std::string fileName);
	void setProgramOutput(int index, std::string name);
	GLint getProgramOutput(std::string name);
	void setVertexAttribName(ShaderProgram::AttribType at, std::string name);
	void prepareProgram();
	void setUniform(std::string name, void *value);
	void setUniform(std::string name, int value);
	void setUniform(std::string name, float value);
	static void setBlock(std::string name, void *value);
	static void setBlockUniform(std::string blockName, std::string uniformName, void *value);
	static void setBlockUniformArrayElement(std::string blockName, std::string uniformName, int arrayIndex, void * value);
	GLuint getProgramIndex();
	GLuint getShaderIndex(ShaderProgram::ShaderType);
	std::string getShaderInfoLog(ShaderProgram::ShaderType);
	std::string getProgramInfoLog();
	std::string getAllInfoLogs();
	bool isProgramValid();
	bool isShaderCompiled(ShaderProgram::ShaderType);
	bool isProgramLinked();


protected:

	// AUX STRUCTURES

	/// stores information for uniforms
	typedef struct uniforms {
		GLenum type;
		GLuint location;
		GLuint size;
		GLuint stride;
	}myUniforms;

	/// stores information for block uniforms
	typedef struct blockUniforms {
		GLenum type;
		GLuint offset;
		GLuint size;
		GLuint arrayStride;
	} myBlockUniform;

	/// stores information for a block and its uniforms
	class UniformBlock {

		public:
			/// size of the uniform block
			int size;
			/// buffer bound to the index point
			GLuint buffer;
			/// binding index
			GLuint bindingIndex;
			/// uniforms information
			std::map<std::string, myBlockUniform > uniformOffsets;
	};

	// VARIABLES

	/// stores if init has been called
	bool pInited;


	/// blockCount is used to assign binding indexes
	static int spBlockCount;

	/// Stores info on all blocks found
	static std::map<std::string, UniformBlock> spBlocks;

	/// stores the OpenGL shader types
	static GLenum spGLShaderTypes[ShaderProgram::COUNT_SHADER_TYPE];
	
	/// stores the text string related to each type
	static std::string spStringShaderTypes[ShaderProgram::COUNT_SHADER_TYPE];

	/// aux string used to return the shaders infologs
	std::string pResult;

	/// stores the shaders and program indices
	GLuint pShader[ShaderProgram::COUNT_SHADER_TYPE], pProgram;

	/// stores info on the uniforms
	std::map<std::string, myUniforms> pUniforms;

	// AUX FUNCTIONS

	/// aux function to get info on the uniforms referenced by the shaders
	void addUniforms();
	
	/// aux function to store the info of a uniform
	void addUniform(std::string name, GLenum type, unsigned int size);

	/// aux function to get info on the blocks referenced by the shaders
	void addBlocks();

	/// determines the size in bytes based on the OpenGL type
	int typeSize(int type);

	/// aux function to read the shader's source code from file
	char *textFileRead(std::string fileName);
};

}

#endif
