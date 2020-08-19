#ifndef INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_

#include <zeno/Window/Window.hpp>
#include <zeno/Graphics/RenderInfo.hpp>
#include <zeno/Graphics/RenderTarget.hpp>

namespace ze {

    class Renderable {
    public:
        virtual ~Renderable() = default;
        virtual void render(const RenderTarget& _target, RenderInfo _info) const = 0;
    };

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP_