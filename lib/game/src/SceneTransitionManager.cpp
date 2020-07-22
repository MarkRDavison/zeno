#include <zeno/Game/SceneTransitionManager.hpp>

namespace ze {

	int SceneTransitionManager::sceneId = 0;

	SceneTransitionManager::SceneTransitionManager(const std::function<void(void)>& _exitCallback) :
		m_ExitCallback(_exitCallback) {

	}
	SceneTransitionManager::~SceneTransitionManager() {

	}

	int SceneTransitionManager::registerState() {
		return ++sceneId;
	}

	void SceneTransitionManager::pushSceneTransition(int _newSceneId) {
		if (m_TransitionMap.count(_newSceneId) == 1) {
			m_TransitionMap.at(_newSceneId)();
		}
	}

	void SceneTransitionManager::registerSceneTransition(int _sceneId, const std::function<void()>& _transitionCallback) {
		m_TransitionMap.insert(std::make_pair(_sceneId, _transitionCallback));
	}

	void SceneTransitionManager::resetCurrentScene() {
		pushSceneTransition(m_CurrentSceneId);
	}

	void SceneTransitionManager::exitApplication(void) const {
		if (m_ExitCallback) {
			m_ExitCallback();
		}
	}

}
