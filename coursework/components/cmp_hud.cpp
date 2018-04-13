#include "cmp_hud.h"
#include "cmp_player_state.h"
#include "cmp_weapon_component.h"
#include "cmp_camera.h"
#include "cmp_text.h"
#include "../game.h"

HudComponent::HudComponent(Entity* p, std::shared_ptr<Entity> player, std::shared_ptr<Entity> camera)
	: Component(p), _player(player), _camera(camera) {}

void HudComponent::update(double dt) {
	// Get player state
	auto state = _player->GetCompatibleComponent<PlayerStateComponent>().front();
	auto weapons = _player->GetCompatibleComponent<WeaponComponent>();

	// Update health
	auto healthText = _parent->GetCompatibleComponent<TextComponent>().at(0);
	healthText->SetText("Health: " + std::to_string((int)state->health));
	// Update energy
	auto energyText = _parent->GetCompatibleComponent<TextComponent>().at(1);
	energyText->SetText("\nEnergy: " + std::to_string((int)state->energy));
	// Update weapon selection
	auto weaponTypeText = _parent->GetCompatibleComponent<TextComponent>().at(2);
	string activeType;
	if (_player == player1) {
		activeType = weapons.at(0)->getP1ActiveType();
	}
	else {
		activeType = weapons.at(0)->getP2ActiveType();
	}
	weaponTypeText->SetText("\n\nWeapon: " + activeType);
	// Update weapon cooldowns
	auto weaponCoolText = _parent->GetCompatibleComponent<TextComponent>().at(3);
	weaponCoolText->SetText("\n\n\nCool: ");
	for (int i = 0; i < weapons.size(); i++) {
		auto weapon = weapons.at(i);
		if (weapon->getType() != activeType) {
			continue;
		}
		float cooldown = weapon->getCooldown();
		weaponCoolText->AddText(std::to_string(cooldown) + "\n");
	}

	// Get camera and view
	auto cameraComp = _camera->GetCompatibleComponent<CameraControllerComponent>().at(0);
	Vector2f position = cameraComp->getMidpoint();
	Vector2f view_dims = cameraComp->getView().getSize();
	// Update positions
	if (_player == player1) {
		position -= Vector2f(view_dims.x / 2.0f, view_dims.y / 2.0f);
		healthText->SetPosition(position);
		energyText->SetPosition(position);
		weaponTypeText->SetPosition(position);
		weaponCoolText->SetPosition(position);
	}
	else {
		position -= Vector2f(0.0f, view_dims.y / 2.0f);
		healthText->SetPosition(position);
		energyText->SetPosition(position);
		weaponTypeText->SetPosition(position);
		weaponCoolText->SetPosition(position);
	}
}

void HudComponent::render() {

}
