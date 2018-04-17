#include "cmp_background.h"
#include "..\resource_manager.h"


int rows;
int colls;
Vector2f topLeft;
Vector2u bgSize;

BackgroundBuilderComponent::BackgroundBuilderComponent(Entity* p) : Component(p)
{
	_cam = p->GetCompatibleComponent<CameraControllerComponent>()[0];
	bgSize = ResourceManager::Tex_background.getSize();

	// Add enough sprites to cover maximum zoom area
	float aspect = (_cam->getView().getSize().x / _cam->getView().getSize().y);
	rows = (_max_zoom * 2.0f / (_cam->getView().getSize().x / _cam->getView().getSize().y)) / bgSize.y + 1;
	colls = _max_zoom * 2.0f / bgSize.x + 1;
	for (int i = 0; i < rows * colls; i++)
		_sprites.push_back(p->addComponent<SpriteComponent>());

	// Calculate the first tile offset
	topLeft = -Vector2f(colls * bgSize.x / 2.0f, rows * bgSize.y / 2.0f);

	// Prepare the sprites
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < colls; j++)
		{
			_sprites[i * colls + j]->getSprite().setTexture(ResourceManager::Tex_background);
			_sprites[i * colls + j]->getSprite().setOrigin(bgSize.x / 2, bgSize.y / 2);
			Vector2f x = Vector2f(1, 1);
			if (i % 2 == 1)
				x.x = -1;
			if (j % 2 == 1)
				x.y = -1;
			_sprites[i * colls + j]->getSprite().setScale(x);
		}
}


BackgroundBuilderComponent::~BackgroundBuilderComponent()
{
	_cam.~shared_ptr();
}


void BackgroundBuilderComponent::update(const double &dt)
{
	// Offset used to give the illusion of a stationary background
	Vector2f offset = Vector2f(fmod(_cam->getMidpoint().x, bgSize.x * 2), fmod(_cam->getMidpoint().y, bgSize.y * 2));

	// Tile the sprites
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < colls; j++)
			_sprites[i * colls + j]->getSprite().setPosition(Vector2f(j * bgSize.x, i * bgSize.y)
				+ _cam->getMidpoint() + topLeft - offset);
}