#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../coursework/game.h"
#include "../coursework/resource_manager.h"

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
Scene* Engine::_pausedScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

void Loading_update(float dt, const Scene* const scn) {
  //  cout << "Eng: Loading Screen\n";
  if (scn->isLoaded()) {
    cout << "Eng: Exiting Loading Screen\n";
    loading = false;
  } else {
    loadingspinner += 220.0f * dt;
    loadingTime += dt;
  }
}
void Loading_render() {
  // cout << "Eng: Loading Screen Render\n";
  static CircleShape octagon(80, 8);
  octagon.setOrigin(80, 80);
  octagon.setRotation(loadingspinner);
  octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
  octagon.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
  t.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f,0.3f));
  Renderer::queue(&t);
  Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  {
    frametimes[++ftc] = dt;
    static string avg = _gameName + " FPS:";
    if (ftc % 60 == 0) {
      double davg = 0;
      for (const auto t : frametimes) {
        davg += t;
      }
      davg = 1.0 / (davg / 255.0);
      _window->setTitle(avg + toStrDecPt(2, davg));
    }
  }

  if (loading) {
    Loading_update(dt, _activeScene);
  } else if (_activeScene != nullptr) {
	  if (_activeScene != &pause) {
		  Physics::update(dt);
	  }
    _activeScene->Update(dt);
  }
}

void Engine::Render(RenderWindow& window) {
  if (loading) {
    Loading_render();
  } else if (_activeScene != nullptr) {
    _activeScene->Render();
  }

  Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
                   const std::string& gameName, unsigned int style, Scene* scn) {
  RenderWindow window(VideoMode(width, height), gameName, style);
  _gameName = gameName;
  _window = &window;
  Renderer::initialise(window);
  Physics::initialise();
  ChangeScene(scn);
  bool loaded = false;
  ChangeScene(scn, true);
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }

	  if (event.type == Event::KeyPressed ||
		  event.type == Event::KeyReleased) {
		  InputManager::storeKey(event.key.code);
		  InputManager::update();
	  }

	  if (event.type == Event::JoystickButtonPressed ||
		  event.type == Event::JoystickButtonReleased ||
		  event.type == Event::JoystickMoved) {
		  InputManager::storeButton(event.joystickButton.joystickId, event.joystickButton.button);
		  InputManager::update();
	  }
	}
	InputManager::menuUpdate();

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		_activeScene->UnLoad();
		if (_pausedScene != nullptr)
			_pausedScene->UnLoad();
      window.close();
    }

    window.clear();
    Update();
    Render(window);
    window.display();
  }
  if (_activeScene != nullptr) {
    _activeScene->UnLoad();
    _activeScene = nullptr;
  }
  window.close();
  Physics::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
  auto e = make_shared<Entity>(this);
  ents.list.push_back(e);
  return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad();
	}

	if (!s->isLoaded()) {
		loadingTime = 0;
		_activeScene->Load();
		loading = true;
	}
}

void Engine::ChangeScene(Scene* s, bool async) {
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad();
	}

	if (!s->isLoaded()) {
		loadingTime = 0;
		_activeScene->LoadAsync();
		loading = true;
	}
}

void Engine::PauseScene(Scene* s) {
	cout << "Eng: pausing scene: " << _activeScene << endl;
	_pausedScene = _activeScene;
	_activeScene = s;

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->Load();
		loading = true;
	}
}

void Engine::ResumeScene() {
	cout << "Eng: resuming scene: " << _pausedScene << endl;
	auto old = _activeScene;
	_activeScene = _pausedScene;

	if (old != nullptr) {
		old->UnLoad();
	}
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    // Are we already loading asynchronously?
    if (_loaded_future.valid() // yes
        &&                     // Has it finished?
        _loaded_future.wait_for(chrono::seconds(0)) ==
            future_status::ready) {
      // Yes
      _loaded_future.get();
      _loaded = true;
    }
    return _loaded;
  }
}
void Scene::setLoaded(bool b) {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    _loaded = b;
  }
}

void Scene::UnLoad() {
  ents.list.clear();
  setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
// Return time since Epoc
long long now() {
  return std::chrono::high_resolution_clock::now()
      .time_since_epoch()
      .count();
}
// Return time since last() was last called.
long long last() {
  auto n = now();
  static auto then = now();
  auto dt = n - then;
  then = n;
  return dt;
}
} // namespace timing

Scene::~Scene() { UnLoad(); }