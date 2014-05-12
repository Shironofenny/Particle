#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <assert.h>

#include "../GLHeader.h"
#include "Scene.h"
#include "../IDimension.h"

class Renderer : public IDimension
{
	public:

		Renderer();

		virtual ~Renderer();

		virtual void Render();
};

#endif
