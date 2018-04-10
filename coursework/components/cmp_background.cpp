#include "cmp_background.h"
#include "..\resource_manager.h"


int rows;
int colls;
Vector2f offset;

BackgroundBuilderComponent::BackgroundBuilderComponent(Entity* p) : Component(p)
{
	_cam = p->GetCompatibleComponent<CameraControllerComponent>()[0];

	rows = _max_zoom / ResourceManager::Tex_background.getSize().x + 1;
	colls = (_max_zoom * (_cam->getView().getSize().x / _cam->getView().getSize().y)) / ResourceManager::Tex_background.getSize().y + 1;
	for (int i = 0; i < rows * colls; i++)
		_sprites.push_back(p->addComponent<SpriteComponent>());

	offset = -Vector2f(_max_zoom / 2.0f, _max_zoom / (_cam->getView().getSize().x / _cam->getView().getSize().y) / 2.0f);

	for (int i = 0; i < colls; i++)
		for (int j = 0; j < rows; j++)
		{
			_sprites[i * j + i]->getSprite().setTexture(ResourceManager::Tex_background);
			_sprites[i * j + i]->getSprite().setOrigin(128, 128);
			if (i % 2 == 1)
				_sprites[i * j + i]->getSprite().setScale(-1.0f, 1.0f);
			if (j % 2 == 1)
				_sprites[i * j + i]->getSprite().setScale(1.0f, -1.0f);
		}
}


BackgroundBuilderComponent::~BackgroundBuilderComponent()
{
	_cam.~shared_ptr();
}


void BackgroundBuilderComponent::update(double dt)
{
	for (int i = 0; i < colls; i++)
		for (int j = 0; j < rows; j++)
			_sprites[i * j + i]->getSprite().setPosition(Vector2f(i * ResourceManager::Tex_background.getSize().x
				, j * ResourceManager::Tex_background.getSize().y)
				+ _cam->getMidpoint() + offset);
}