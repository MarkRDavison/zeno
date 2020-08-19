#include <zeno/Graphics/RenderWindow.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ze {

	Vector2u RenderWindow::getSize() const {
		return Window::getSize();
	}

	void RenderWindow::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void RenderWindow::clear(ze::Colour _colour) {
		glClearColor(_colour.r, _colour.g, _colour.b, _colour.a);
		clear();
	}

	void RenderWindow::setActive(bool _active) {
		if (m_Active != _active) {
			m_Active = _active;
			if (m_Active) {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glViewport(0, 0, (int)getSize().x, (int)getSize().y);
			}
		}
	}

	void RenderWindow::display() {
		glfwSwapBuffers(this->getHandle());
	}

}