#ifndef _KIGSBITMAP_H_
#define _KIGSBITMAP_H_

#include "TecLibs/Tec3D.h"
#include "TecLibs/2D/BBox2DI.h"
#include "Drawable.h"
#include "CoreModifiableAttribute.h"

// ****************************************
// * KigsBitmap class
// * --------------------------------------
/**
* \file	KigsBitmap.h
* \class	KigsBitmap
* \ingroup Drawable
* \ingroup RendererDrawable
* \brief
* \author	ukn
* \version ukn
* \date	ukn
*
* Module Dependency :<br><ul><li>ModuleRenderer</li></ul>
*/
// ****************************************
class KigsBitmap : public Drawable
{
public:

	class KigsBitmapPixel
	{
	public:
		KigsBitmapPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :R(r), G(g), B(b), A(a) {};
		unsigned char R, G, B, A;
		void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}
	};


	DECLARE_CLASS_INFO(KigsBitmap, Drawable, Renderer)

	/**
	* \brief	constructor
	* \fn 		KigsBitmap(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);
	* \param	name : instance name
	* \param	DECLARE_CLASS_NAME_TREE_ARG : list of arguments
	*/
	KigsBitmap(const kstl::string& name, DECLARE_CLASS_NAME_TREE_ARG);
	
	unsigned int	GetSelfDrawingNeeds() override
	{
		return ((unsigned int)Need_Predraw);
	}

	// no check for out of bound
	inline KigsBitmapPixel	GetPixel(int x, int y) const
	{
		KigsBitmapPixel* readPixel = (KigsBitmapPixel*)myRawPixels;
		readPixel += x;
		readPixel += y*mySize[0];
		return *readPixel;
	}

	void	Box(int x, int y, int sizex, int sizey, const KigsBitmapPixel& color);

	inline void Clear(const KigsBitmapPixel& clearColor)
	{
		Box(0, 0, mySize[0], mySize[1], clearColor);
	}

	inline void PutPixel(int x, int y, const KigsBitmapPixel& write)
	{
		myDirtyZone.Update(x, y);

		KigsBitmapPixel* readPixel = (KigsBitmapPixel*)myRawPixels;
		readPixel += x;
		readPixel += y*mySize[0];
		*readPixel = write;
	}

	void	Line(int sx, int sy, int ex, int ey, const KigsBitmapPixel& color);
	void	Line(Point2DI p1, Point2DI p2, const KigsBitmapPixel& color);

	void	ScrollX(int offset, const KigsBitmapPixel& color);
	void	ScrollY(int offset, const KigsBitmapPixel& color);


protected:

	inline unsigned char*	GetPixelAddress(int x, int y)
	{
		KigsBitmapPixel* readPixel = (KigsBitmapPixel*)myRawPixels;
		readPixel += x;
		readPixel += y*mySize[0];
		return (unsigned char*)readPixel;
	}

	//! init the modifiable and set the _isInit flag to true if OK
	void	InitModifiable() override;

	/**
	* \brief	initialise pre draw method
	* \fn 		virtual bool PreDraw(TravState*);
	* \param	TravState : camera state
	* \return	TRUE if a could PreDraw
	*/
	bool PreDraw(TravState*)  override;

	maVect2DI			mySize;

	// manage a RGBA8888 array of pixel and update it's father texture if needed 
	unsigned char*		myRawPixels;

	virtual ~KigsBitmap();

	BBox2DI	myDirtyZone;

};

#endif // _KIGSBITMAP_H_