#ifndef INCLUDED_ZENO_GRAPHICS_RENDER_INFO_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDER_INFO_HPP_

#include <zeno/Graphics/Texture.hpp>
#include <zeno/Graphics/Shader.hpp>
#include <zeno/Core/Mat4x4.hpp>

namespace ze {

    struct RenderInfo {

        Shader* shader{ nullptr };
        const Texture* texture{ nullptr };

        Mat4x4 model{ 1.0f };
        Mat4x4 view{ 1.0f };
        Mat4x4 projection{ 1.0f };
        float alpha{ 1.0f };

    };

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDER_INFO_HPP_