#ifndef INCLUDED_ZENO_GAME_SCENE_TRANSITION_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_SCENE_TRANSITION_MANAGER_HPP_

#include <map>
#include <functional>

namespace ze {

	class SceneTransitionManager {
	public:
		SceneTransitionManager(const std::function<void(void)>& _exitCallback);
		~SceneTransitionManager();

		static int registerState();

		void pushSceneTransition(int _newSceneId);
		void registerSceneTransition(int _sceneId, const std::function<void()>& _transitionCallback);
		void resetCurrentScene();
		void exitApplication(void) const;

	private:
		static int sceneId;

		int m_CurrentSceneId{ 0 };
		std::map<int, std::function<void()>> m_TransitionMap;
		const std::function<void(void)> m_ExitCallback;
	};

}

#endif // INCLUDED_ZENO_GAME_SCENE_TRANSITION_MANAGER_HPP_