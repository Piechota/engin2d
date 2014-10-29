#include <glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "matrix.h"
#include "obj.h"
#include "Deferred_Light.h"

using namespace sf;

const char* scene_vs[]=
{
	"#version 330							\n"

	"layout(location=0) in vec4 Position;	\n"
	"layout(location=1) in vec2 TexCoord;	\n"

	"out vec2 UV;							\n"

	"void main()							\n"
	"{										\n"
	"	gl_Position = Position;				\n"
	"	UV = TexCoord;						\n"
	"}										\n"
};
const char* scene_fs[]=
{
	"#version 330							\n"

	"in vec2 UV;							\n"
	"uniform sampler2D tex;					\n"
	"out vec4 diffuse;						\n"
	
	"void main()							\n"
	"{										\n"
	"	diffuse = texture(tex, UV);			\n"
	"}										\n"
};

const GLint shadow_size = 4096;


GLfloat scene[] = 
{
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f
};
GLfloat scene_coord[] = 
{
	0.0f,  0.0f,
	1.0f,  0.0f,
	1.0f, -1.0f,
	0.0f, -1.0f
};

GLuint scene_vbo[2];
GLuint scene_shader;

GLfloat left = -0.5f;
GLfloat right = 0.5f;
GLfloat bottom = -0.5f;
GLfloat top = 0.5f;
GLfloat close = 1.0f;
GLfloat wide = 10.0f;

mx_matrix4 pMatrix;

GLuint shadowbuffer;
GLuint FBO;

GLuint Diffuse;
GLuint NormSpec;
GLuint Depth;

GLuint shadowmap;

Model cube;
Model axe;
Model sciana;
Model fence;
Model filar;

Direction light1;
Direction light2;
Ambient light0(0.07f, 0.07f, 0.1f);

Window window;			//SFML
//SDL_Window *mainwindow; /* Our window handle */

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	pMatrix.LoadIdentity();

	if(w < h && w > 0)
		pMatrix.Frustum(left, right, bottom*h/w, top*h/w, close, wide);
	else if(w > h && h > 0)
		pMatrix.Frustum(left*w/h, right*w/h, bottom, top, close, wide);
	else
		pMatrix.Frustum(left, right, bottom, top, close, wide);
}

void InitScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	scene_shader = glCreateProgram();
	
	GLuint vs_shdr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_shdr, 1, scene_vs, NULL);

	GLuint fs_shdr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_shdr, 1, scene_fs, NULL);

	glCompileShader(vs_shdr);
	glCompileShader(fs_shdr);

	glAttachShader(scene_shader, vs_shdr);
	glAttachShader(scene_shader, fs_shdr);

	glLinkProgram(scene_shader);

	glGenBuffers(2, scene_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, scene_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene), scene, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, scene_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_coord), scene_coord, GL_STATIC_DRAW);

	Init_Obj(true);
	Init_Light();

	cube.Load("../cube.obj", "../cube_diffuse.bmp", "../cube_normal.bmp", "../cube_specular.bmp");
	axe.Load("../axe.obj", "../axe_diffuse.bmp", "../axe_normal.bmp", "../axe_specular.bmp");
	sciana.Load("../sciana.obj", "../sciana_diffuse.bmp", "../sciana_normal.bmp", "../sciana_specular.bmp");
	fence.Load("../fence.obj", "../fence_diffuse.bmp", "../fence_normal.bmp", "../fence_specular.bmp");
	filar.Load("../filar.obj", "../fence_diffuse.bmp", "../fence_normal.bmp", "../fence_specular.bmp");

	cube.translate(0.0f, -1.0f, (-(close+wide)/2.0f));
	axe.translate(0.0f, -1.0f, -(close+wide)/2.0f);
	sciana.translate(0.0f, -1.0f, (-(close+wide)/2.0f));
	fence.translate(0.0f, -1.0f, -(close+wide)/2.0f);
	filar.translate(0.0f, -1.0f, -(close+wide)/2.0f);

	cube.change_scale(0.4f);
	axe.change_scale(0.4f);
	sciana.change_scale(0.4f);
	fence.change_scale(0.4f);
	filar.change_scale(0.4f);

	light1.set_color(0.2f, 0.2f, 0.3f);
	light1.set_position(2.0f, 1.f, (-(close+wide)/2.0f)+1.f);
	light1.lookAt(0.0f, 0.0f, (-(close+wide)/2.0f));

	light2.set_color(0.05f, 0.05f, 0.075f);
	light2.set_position(0.0f, 0.5f, 1.0f);
	light2.lookAt(0.0f, 0.0f, (-(close+wide)/2.0f));
	
	//===========================================================================================================

	glGenFramebuffers(1, &shadowbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowbuffer);

	glGenTextures(1, &shadowmap);
	glBindTexture(GL_TEXTURE_2D, shadowmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, shadow_size, shadow_size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowmap, 0);
	glDrawBuffer(GL_NONE);

	//==========================================================================================================

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	
	glGenTextures(1, &Diffuse);
	glBindTexture(GL_TEXTURE_2D, Diffuse);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.getSize().x, window.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);		//SFML

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &NormSpec);
	glBindTexture(GL_TEXTURE_2D, NormSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, window.getSize().x, window.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);		//SFML

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &Depth);
	glBindTexture(GL_TEXTURE_2D, Depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, window.getSize().x, window.getSize().y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);		//SFML

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Diffuse, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, NormSpec, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Depth, 0);

	GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, buffers);

	//==========================================================================================================

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glCullFace(GL_TRUE);
}

void DisplayScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, shadowbuffer);
	glViewport(0, 0, shadow_size, shadow_size);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	cube.drawShadow(light1.mvDepth(), light1.pDepth(close, wide)); 
	axe.drawShadow(light1.mvDepth(), light1.pDepth(close, wide)); 
	sciana.drawShadow(light1.mvDepth(), light1.pDepth(close, wide)); 
	fence.drawShadow(light1.mvDepth(), light1.pDepth(close, wide)); 
	filar.drawShadow(light1.mvDepth(), light1.pDepth(close, wide)); 
	fence.drawShadow(light1.mvDepth(), light1.pDepth(close, wide), -1.0f, 1.0f, 1.0f); 
	filar.drawShadow(light1.mvDepth(), light1.pDepth(close, wide), -1.0f, 1.0f, 1.0f); 

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, window.getSize().x, window.getSize().y);		//SFML
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube.draw(pMatrix);
	axe.draw(pMatrix);
	sciana.draw(pMatrix);
	fence.draw(pMatrix);
	filar.draw(pMatrix);
	fence.draw(pMatrix, -1.0f, 1.0f, 1.0f);
	filar.draw(pMatrix, -1.0f, 1.0f, 1.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, window.getSize().x, window.getSize().y);		//SFML
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	draw_lights();

	light0.draw_light(Diffuse);

	draw_shadows();
	light1.draw_shadow(Diffuse, NormSpec, Depth, shadowmap, window.getSize().x, window.getSize().y, pMatrix, close, wide);		//SFML

	glBindFramebuffer(GL_FRAMEBUFFER, shadowbuffer);
	glViewport(0, 0, 4096, 4096);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	cube.drawShadow(light2.mvDepth(), light2.pDepth(close, wide)); 
	axe.drawShadow(light2.mvDepth(), light2.pDepth(close, wide)); 
	sciana.drawShadow(light2.mvDepth(), light2.pDepth(close, wide)); 
	fence.drawShadow(light2.mvDepth(), light2.pDepth(close, wide)); 
	filar.drawShadow(light2.mvDepth(), light2.pDepth(close, wide)); 
	fence.drawShadow(light2.mvDepth(), light2.pDepth(close, wide), -1.0f, 1.0f, 1.0f); 
	filar.drawShadow(light2.mvDepth(), light2.pDepth(close, wide), -1.0f, 1.0f, 1.0f); 

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	//glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	draw_shadows();
	light2.draw_shadow(Diffuse, NormSpec, Depth, shadowmap, window.getSize().x, window.getSize().y, pMatrix, close, wide);

	glViewport(0, 0, shadow_size/12, shadow_size/12);

	glUseProgram(scene_shader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, scene_vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, scene_vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowmap);
	glUniform1i(glGetUniformLocation(scene_shader, "tex"), 0);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glUseProgram(0);
	glFlush();
}

void DeleteScene()
{
	cube.kill();
	axe.kill();
	sciana.kill();
	fence.kill();
	filar.kill();

	Delete_Obj();
	Delete_Light();

	glDeleteFramebuffers(1, &FBO);
	glDeleteFramebuffers(1, &shadowbuffer);
}

int main()
{
	//SDL_GLContext maincontext; /* Our opengl context handle */
	//SDL_Init(SDL_INIT_VIDEO);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//mainwindow = SDL_CreateWindow("Shadow test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	//	1024, 1024, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	window.create(VideoMode(), "shadowTEST", Style::Fullscreen);		//SFML

	/*maincontext = SDL_GL_CreateContext(mainwindow);
	SDL_GL_SetSwapInterval(1);
*/
	GLenum error = glewInit();

	InitScene();

	Reshape(window.getSize().x, window.getSize().y);		//SFML

	Event event; //SFML
	
	GLfloat rotateX = 0.0f;
	GLfloat rotateY = 0.0f;

	bool run = true;
	bool mouse_l = false;
	bool mouse_r = false;
	bool rot = false;
	int time = 0;
	
	Vector2i pos;		//SFML
	while(run)
	{


		/*SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch (event.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:

				break;
			}
		}*/
		Event event;		//SFML
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case Event::Closed:
				run = false;
				break;
			case Event::KeyPressed:
				if(event.key.code == Keyboard::Escape)
					run = false;
				break;
			case Event::MouseButtonPressed:
				if(event.mouseButton.button == Mouse::Left)
				{
					pos = Mouse::getPosition(window);
					mouse_l = true;
				}
				if(event.mouseButton.button == Mouse::Right)
				{
					rot = !rot;
					time = 90;
				}
				break;
			case Event::MouseButtonReleased:
				if(event.mouseButton.button == Mouse::Left)
					mouse_l = false;
				if(event.mouseButton.button == Mouse::Right)
					mouse_r = false;

				rotateX = rotateY = 0.0f;
				break;
			case Event::MouseMoved:
				if(mouse_l)
				{
				
				rotateY = 30*(right - left)/static_cast<GLfloat>(window.getSize().x)*(static_cast<int>(event.mouseMove.x)-pos.x);
				pos.x = static_cast<int>(event.mouseMove.x);
				
				rotateX = -30*(top-bottom)/static_cast<GLfloat>(window.getSize().y)*(pos.y-static_cast<int>(event.mouseMove.y));
				pos.y = static_cast<int>(event.mouseMove.y);
				}
				break;
			}

		}
		Reshape(window.getSize().x, window.getSize().y);	//SFML
		cube.rotate(rotateX, rotateY, 0.0f);
		axe.rotate(rotateX, rotateY, 0.0f);
		sciana.rotate(rotateX, rotateY, 0.0f);
		fence.rotate(rotateX, rotateY, 0.0f);
		filar.rotate(rotateX, rotateY, 0.0f);

		if(time)
		{
			if(rot)
			{ axe.rotate(0.0f, 0.0f, -0.3f); time--;}
			else
			{ axe.rotate(0.0f, 0.0f, 0.3f); time--;}
			
		}

		
		DisplayScene();
		//SDL_GL_SwapWindow(mainwindow);
		window.display();		//SFML
	}
	/*SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();*/
	window.close();		//SFML
	DeleteScene();

	return 0;
}
