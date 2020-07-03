#include <zeno/Game/Application.hpp>
#include <zeno/Core/Clock.hpp>
#include <zeno/Window/Window.hpp>
#include <iostream>

namespace ze {

	bool Application::startSplash(const VideoMode& _videoMode, Scene* _splashScene) {
		m_StartingMode = _videoMode;
		m_SplashShowing = true;

		VideoMode splashVideoMode = _videoMode;
		splashVideoMode.fullscreen = false;
		splashVideoMode.decorated = false;
		splashVideoMode.width = 800;
		splashVideoMode.height = 400;
		if (!m_Window.initialise(splashVideoMode)) {
			std::cerr << "Failed to initialise splash screen." << std::endl;
			return false;
		}

		if (!ze::Shader::createDefaultShaders()) {
			std::cerr << "Failed to initialise default shaders." << std::endl;
			return false;
		}

		setScene(_splashScene);

		return true;
	}
	void Application::renderSplash() {
		render(0.0f);
	}
	bool Application::splashFinished() {
		return splashFinished(m_StartingMode);
	}
	bool Application::splashFinished(const VideoMode& _videoMode) {

		if (m_Window.getWindowFullscreen()) {
			m_Window.setWindowFullscreen(_videoMode.fullscreen);
		}
		else {
			m_Window.setSize(ze::Vector2u(_videoMode.width, _videoMode.height));
			m_Window.setWindowDecorated(_videoMode.decorated);
			m_Window.center();
		}

		setScene(nullptr);

		m_Initialised = true;
		return true;
	}
	bool Application::initialise(const Vector2u& _resolution, const std::string& _name) {
		VideoMode mode{ _resolution, _name };
		mode.contextMajor = 4;
		mode.contextMinor = 5;
		return initialise(mode);
	}
	bool Application::initialise(const VideoMode& _videoMode) {
		if (m_Initialised) {
			std::cerr << "Cannot initalise an application twice." << std::endl;
			return false;
		}
		if (!m_Window.initialise(_videoMode)) {
			std::cerr << "Failed to initialise window." << std::endl;
			return false;
		}
		if (!ze::Shader::createDefaultShaders()) {
			std::cerr << "Failed to initialise default shaders." << std::endl;
			return false;
		}

		m_StartingMode = _videoMode;
		m_Initialised = true;
		return true;
	}

	void Application::update(float _delta) {
		if (m_Scene != nullptr) {
			m_Scene->update(_delta);
		}
	}

	void Application::render(float _alpha) {
		RenderInfo info{};
		info.projection = Mat4x4::Orthographic3D(0.0f, static_cast<float>(m_Window.getSize().x), static_cast<float>(m_Window.getSize().y), 0.0f, -1.0f, +1.0f);
		info.alpha = _alpha;
		ze::Window::clear();

		if (m_Scene != nullptr) {
			m_Scene->render(m_Window, info);
		}

		m_Window.display();
	}

	void Application::start() {
		if (!m_Initialised) {
			std::cerr << "Cannot start application without initialising it." << std::endl;
			return;
		}
		m_Running = true;

		Clock clock{};
		const float delta = 1.0f / 60.0f;
		float accumulator = 0.0f;
		float statsAccumulator = 0.0f;
		unsigned int fps = 0;
		unsigned int ups = 0;
		while (m_Running) {
			float frameTime = clock.restart<float>();
			if (frameTime > 0.5f) {
				frameTime = 0.5f;
			}

			accumulator += frameTime;

			statsAccumulator += frameTime;

			if (statsAccumulator >= 1.0f) {
				//std::cout << "FPS: " << fps << " UPS: " << ups << std::endl;
				statsAccumulator -= 1.0f;
				fps = 0;
				ups = 0;
			}


			while (accumulator >= delta) {
				ze::Event event;
				m_Window.pumpEvents();
				while (m_Window.pollEvent(event)) {
					if (event.type == ze::Event::EventType::WindowClosed) {
						stop();
					}

					if (m_Scene != nullptr) {
						m_Scene->handleEvent(event);
					}
				}

				// Update
				update(delta);
				ups++;

				accumulator -= delta;
			}

			// Render
			render(accumulator / delta);
			fps++;
		}

		m_Window.close();
	}

	void Application::stop() {
		m_Running = false;
	}

	void Application::setScene(Scene* _scene) {
		m_Scene = _scene;
	}
	Window& Application::getWindow() {
		return m_Window;
	}
	const Window& Application::getWindow() const {
		return m_Window;
	}

}
