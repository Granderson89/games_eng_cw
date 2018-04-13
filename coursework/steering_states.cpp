#include "steering_states.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_player_state.h"
#include "components/cmp_weapon_component.h"
#include "input_manager.h"
#include "system_physics.h"

using namespace sf;
using namespace Physics;

float optimum_distance = 750.0f;
float danger_distance = 1000.0f;
float close_distance = 400.0f;
float low_health = 25.0f;

void SeekState::execute(Entity *owner, double dt) noexcept {
	// Swtich to missiles
	auto activeType = owner->GetCompatibleComponent<WeaponComponent>().at(0)->getP2ActiveType();
	if (activeType == "CANNONS") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}
	if (activeType == "TORPEDOS") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}	
	// Fire weapons
	InputManager::Player[1].fire = true;
	// Change colour to represent state
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Green);
	// Get steering and set it
	auto output = _steering.getSteering();
	auto body = owner->get_components<PlayerPhysicsComponent>().at(0)->getBody();
	auto new_position = sv2_to_bv2(invert_height(owner->getPosition() + (output.direction * (float)dt)));
	float new_rotation;
	if (body->GetTransform().q.GetAngle() > -output.rotation) {
		new_rotation = body->GetTransform().q.GetAngle() - dt;
	}
	else {
		new_rotation = body->GetTransform().q.GetAngle() + dt;
	}
	body->SetTransform(new_position, new_rotation);
	// Check for change to face
	if (length(owner->getPosition() - _player->getPosition()) < optimum_distance) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("face");
	}
	// Check for change to flee
	if (owner->get_components<PlayerStateComponent>().at(0)->health < low_health) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("flee");
	}
}

void FleeState::execute(Entity *owner, double dt) noexcept {
	// Switch to missiles
	auto activeType = owner->GetCompatibleComponent<WeaponComponent>().at(0)->getP2ActiveType();
	if (activeType == "CANNONS") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}
	if (activeType == "TORPEDOS") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}
	// Fire weapons
	InputManager::Player[1].fire = true;
	// Change colour to represent state
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Yellow);
	// Get steering and set it
	auto output = _steering.getSteering();
	auto body = owner->get_components<PlayerPhysicsComponent>().at(0)->getBody();
	auto new_position = sv2_to_bv2(invert_height(owner->getPosition() + (output.direction * (float)dt)));
	float new_rotation;
	if (body->GetTransform().q.GetAngle() > -output.rotation) {
		new_rotation = body->GetTransform().q.GetAngle() - dt;
	}
	else {
		new_rotation = body->GetTransform().q.GetAngle() + dt;
	}
	body->SetTransform(new_position, new_rotation);
	// Check for change to face
	if ((length(owner->getPosition() - _player->getPosition()) > optimum_distance && 
		owner->get_components<PlayerStateComponent>().at(0)->health > low_health) ||
		length(owner->getPosition() - _player->getPosition()) > danger_distance) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("face");
	}
}

void FaceState::execute(Entity *owner, double dt) noexcept {
	// Switch to cannons
	auto activeType = owner->GetCompatibleComponent<WeaponComponent>().at(0)->getP2ActiveType();
	if (activeType == "TORPEDOS") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}
	if (activeType == "MISSILES") {
		owner->GetCompatibleComponent<WeaponComponent>().at(0)->changeP2Weapon();
	}
	// Fire weapons
	InputManager::Player[1].fire = true;
	// Change colour to represent state
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(Color::Blue);
	// Get steering and set it
	auto output = _steering.getSteering();
	auto body = owner->get_components<PlayerPhysicsComponent>().at(0)->getBody();
	auto new_position = sv2_to_bv2(invert_height(owner->getPosition()));
	float new_rotation;
	if (body->GetTransform().q.GetAngle() > -output.rotation) {
		new_rotation = body->GetTransform().q.GetAngle() - dt;
	}
	else {
		new_rotation = body->GetTransform().q.GetAngle() + dt;
	}
	body->SetTransform(new_position, new_rotation);
	// Check for change to seek
	if (length(owner->getPosition() - _player->getPosition()) > optimum_distance) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("seek");
	}
	// Check for changes to flee
	else if (length(owner->getPosition() - _player->getPosition()) < close_distance) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("flee");
	}
	if (owner->get_components<PlayerStateComponent>().at(0)->health < low_health) {
		auto sm = owner->get_components<StateMachineComponent>();
		sm[0]->changeState("flee");
	}
}