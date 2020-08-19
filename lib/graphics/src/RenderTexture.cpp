#include <zeno/Graphics/RenderTexture.hpp>
#include <GL/glew.h>

namespace ze {

	RenderTexture::~RenderTexture() {

	}

	bool RenderTexture::create(const Vector2u& _size) {
		m_Active = true;
		m_Size = _size;
		glGenFramebuffers(1, &m_Framebuffer);
		if (m_Framebuffer == 0) {
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		
		glGenTextures(1, &m_Texture);
		if (m_Texture == 0) {
			return false;
		}
		
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)m_Size.x, (int)m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		//if (m_UseDepthTexture) {
		//	glGenTextures(1, &m_DepthTexture);
		//	if (m_DepthTexture == 0) {
		//		return false;
		//	}
		//	glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (int)m_Size.x, (int)m_Size.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		//}
		
		glGenRenderbuffers(1, &m_DepthBuffer);
		if (m_DepthBuffer == 0) {
			return false;
		}
		
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int)m_Size.x, (int)m_Size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
		
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture, 0);
		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	void RenderTexture::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void RenderTexture::clear(ze::Colour _colour) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderTexture::setActive(bool _active) {
		if (m_Active != _active) {
			m_Active = _active;
			if (m_Active) {
				glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
				glViewport(0, 0, (int)m_Size.x, (int)m_Size.y);
			} else {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
	}

	Vector2u RenderTexture::getSize() const {
		return m_Size;
	}

	void RenderTexture::bindTexture() const {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glUniform1i(m_Texture, 0);
	}
}