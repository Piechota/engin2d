#include "Headers.h"
#include "Terrain.h"
#include "ResourceFactory.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GLfloat leftV = -0.5f;
GLfloat rightV = 0.5f;
GLfloat bottomV = -0.5f;
GLfloat topV = 0.5f;
GLfloat closeV = 1.0f;
GLfloat wideV = 10.0f;

Window window;

Terrain* terrain;

void ShaderVertexCreatetest(GLuint &program, const char** shader)
{
	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint vs_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_shader, 1, shader, NULL);

	glCompileShader(vs_shader);

	glGetShaderiv(vs_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs_shader, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetShaderInfoLog(vs_shader, logLength, NULL, info);
	cout << info;
	delete[] info;

	glAttachShader(program, vs_shader);
}
void ShaderFragmentCreatetest(GLuint &program, const char** shader)
{
	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_shader, 1, shader, NULL);

	glCompileShader(fs_shader);

	glGetShaderiv(fs_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs_shader, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetShaderInfoLog(fs_shader, logLength, NULL, info);
	cout << info;
	delete[] info;

	glAttachShader(program, fs_shader);
}
void ShaderVertexFragmentLinktest(GLuint &program, const char** vertex_shader, const char** fragment_shader)
{
	ShaderVertexCreatetest(program, vertex_shader);
	ShaderFragmentCreatetest(program, fragment_shader);

	glLinkProgram(program);

	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetProgramInfoLog(program, logLength, NULL, info);
	cout << info;
	delete[] info;
}

const char* vstest[] =
{
	"#version 330								\n"

	"layout(location=0) in vec4 inPosition;		\n"
	//"layout(location=1) in vec2 inTexCoord;		\n"

	//"uniform mat4 mvpMatrix;					\n"

	"out vec2 TexCoord;							\n"

	"void main()								\n"
	"{											\n"
	"	gl_Position = inPosition;	\n"
	//"	gl_Position = mvpMatrix * inPosition;	\n"
	//"	TexCoord = inTexCoord;					\n"
	"}											\n"
};
const char* fstest[] =
{
	"#version 330								\n"

	//"in vec2 inTexCoord;						\n"

	//"uniform sampler2D tex;						\n"

	"out vec4 Color;							\n"

	"void main()								\n"
	"{											\n"
	"	Color = vec4(0, 0, 1, 1);		\n"
	//"	Color = texture(tex, inTexCoord);		\n"
	"}											\n"
};

GLuint vbotest[2];

GLfloat tiletest[] =
{
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f
};

GLuint programtest;

void Reshape()
{
	int w = window.getSize().x, h = window.getSize().y;

	glViewport(0, 0, w, h);
	MySprite::pMatrix.LoadIdentity();

	if (w < h && w > 0)
		MySprite::pMatrix.Ortho(leftV, rightV, bottomV*h / w, topV*h / w, closeV, wideV);
	else if (w > h && h > 0)
		MySprite::pMatrix.Ortho(leftV*w / h, rightV*w / h, bottomV, topV, closeV, wideV);
	else
		MySprite::pMatrix.Ortho(leftV, rightV, bottomV, topV, closeV, wideV);
}

void InitScene()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Engine2D", Style::Default);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		cout << "glew faild" << endl;
	}

//	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glClearColor(0.5f, 0.f, 0.f, 1.f);

	terrain = new Terrain(ResourceFactory::resource + "map.txt");
	terrain->SetViewSize(mx_vector2(2, 2));
	terrain->SetViewPos(mx_vector2(1, 1));

	glGenBuffers(1, &vbotest[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbotest[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tiletest), tiletest, GL_STATIC_DRAW);

	ShaderVertexFragmentLinktest(programtest, vstest, fstest);

	glUseProgram(programtest);
}

void TerrainDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programtest);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbotest[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);


	glUseProgram(0);

	//terrain->update();

	glFlush();
}

int main(int argc, char *argv[])
{
	InitScene();

	Reshape();

	bool run = true;
	while (run)
	{
		//TODO: INPUT

		TerrainDisplay();
		window.display();
	}
	window.close();

	delete terrain;

	return 0;
}