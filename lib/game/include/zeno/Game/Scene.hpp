#ifndef INCLUDED_ZENO_GAME_SCENE_HPP_
#define INCLUDED_ZENO_GAME_SCENE_HPP_

#include <zeno/Graphics/Renderable.hpp>
#include <zeno/Core/Event.hpp>

namespace ze {

    class Scene : Renderable {
    public:
        virtual ~Scene() = 0;

        virtual void update(float _delta) = 0;
        virtual bool handleEvent(const Event& _event) = 0;
        void render(const Window& _window, RenderInfo _info) const override = 0;
    };

    inline Scene::~Scene() = default;

}

#endif // INCLUDED_ZENO_GAME_SCENE_HPP_