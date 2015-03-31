#include "IWidget.h"

IWidget::IWidget(const int id_, const char* texture)
{
	id = id_;
	default_texture = gGraphicManager::getGraphicManager().loadTexture(texture);
	size = gGraphicManager::getTextureSize(default_texture);

	coords.x = coords.y = 0;
}

void IWidget::draw()
{
	gGraphicManager::getGraphicManager().RenderTexture(default_texture, coords.x, coords.y);
}

void IWidget::remove()
{
	//Remove from the screen 
}

bool IWidget::load()
{
	//Load content to draw
}