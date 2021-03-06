#ifndef _WIN32OPENGLRENDERINGSCREEN_H
#define _WIN32OPENGLRENDERINGSCREEN_H


#include <windows.h>

class OpenGLTexture;

#include "UIVerticesInfo.h"

#include "Platform\Renderer\OpenGLInclude.h"

class OpenGLPlatformRenderingScreen : public RenderingScreen
{
public:
    DECLARE_ABSTRACT_CLASS_INFO(OpenGLPlatformRenderingScreen,RenderingScreen,Renderer)

	OpenGLPlatformRenderingScreen(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);
    
	void	SetWindowByHandle(void *PtrToHandle);

	void*	GetContextHandle()
	{
		return &myhDC;
	}

protected:
    
	 void Update(const Timer&  timer, void* /*addParam*/)override;


	 virtual void InitializeGL(GLsizei width, GLsizei height)=0;

	 void	InitModifiable()override;
	 void	UninitModifiable()override;

	 void	setCurrentContext() override;

	virtual ~OpenGLPlatformRenderingScreen();
   
	bool SetupPixelFormat(HDC hdc);

	HDC   myhDC; 
	HGLRC myhRC; 

	HWND  myhWnd;

	// WGL_ARB_extensions_string
	static PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
	
	// WGL_ARB_pixel_format
	static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

	// WGL_ARB_render_texture
	static PFNWGLBINDTEXIMAGEARBPROC     wglBindTexImageARB;
	static PFNWGLRELEASETEXIMAGEARBPROC  wglReleaseTexImageARB;

	static PFNWGLSETPBUFFERATTRIBARBPROC wglSetPbufferAttribARB;
		
};    


#endif //_WIN32OPENGLRENDERINGSCREEN_H