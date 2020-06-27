#ifndef INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_

#include <zeno/Window/Window.hpp>
#include <zeno/Graphics/RenderInfo.hpp>

namespace ze {

    class Renderable {
    public:
        virtual ~Renderable() = default;
        virtual void render(const Window& _window, RenderInfo _info) const = 0;
    };

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_