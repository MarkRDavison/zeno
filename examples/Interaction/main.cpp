#include <zeno/Game.hpp>
#include <zeno/Graphics.hpp>
#include <zeno/Interaction.hpp>
#include <memory>

constexpr static int ConstraintSceneId = 1;
constexpr static int AnimationSceneId = 2;
constexpr static int ControlSceneId = 3;
constexpr static char iconTextureName[] = "./data/gear.png";
constexpr static char fontName[] = "./data/sansation.ttf";

std::shared_ptr<ze::Scene> constraintScene;
std::shared_ptr<ze::Scene> animationScene;
std::shared_ptr<ze::Scene> controlScene;

std::function<void(int _sceneId)> changeSceneFxn;

class NavigationPanelControl : public ze::Component {
public:
    ~NavigationPanelControl() override = default;

    void initialise() override {
            auto clickBlock = std::make_shared<ze::BlockControl>();
            clickBlock->colour = ze::Colour(0.3f, 0.3f, 0.3f);
            addComponent(clickBlock, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::FillConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::FillConstraint())
            ));
            auto clickable1 = std::make_shared<ze::ButtonControl>();
            clickable1->clickSignal.registerCallback([](ze::Mouse::Button _button) -> void {
                if (_button == ze::Mouse::Button::Left) {
                    changeSceneFxn(ConstraintSceneId);
                }
            });
            clickable1->defaultColour = ze::Colour::Cyan;
            clickable1->hoverColour = ze::Colour::Magenta;
            clickBlock->addComponent(clickable1, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::CenterConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(6.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(32.0f))
            ));
            auto clickable2 = std::make_shared<ze::ButtonControl>();
            clickable2->clickSignal.registerCallback([](ze::Mouse::Button _button) -> void {
                if (_button == ze::Mouse::Button::Left) {
                    changeSceneFxn(AnimationSceneId);
                }
            });
            clickable2->defaultColour = ze::Colour::Cyan;
            clickable2->hoverColour = ze::Colour::Magenta;
            clickBlock->addComponent(clickable2, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(clickable1.get(), ze::ConstraintType::Y_POS)),
                std::shared_ptr<ze::Constraint>(new ze::CenterConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(6.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(32.0f))
            ));
            auto clickable3 = std::make_shared<ze::ButtonControl>();
            clickable3->clickSignal.registerCallback([](ze::Mouse::Button _button) -> void {
                if (_button == ze::Mouse::Button::Left) {
                    changeSceneFxn(ControlSceneId);
                }
            });
            clickable3->defaultColour = ze::Colour::Cyan;
            clickable3->hoverColour = ze::Colour::Magenta;
            clickBlock->addComponent(clickable3, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(clickable2.get(), ze::ConstraintType::Y_POS)),
                std::shared_ptr<ze::Constraint>(new ze::CenterConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(6.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(32.0f))
            ));
    };

    bool handleEvent(const ze::Event& _event) override {
        // TODO: Make optional virtul functions work..
        for (auto& c : children) {
            if (c->handleEvent(_event)) {
                return true;
            }
        }
        return false;
    }
    void renderComponent(const ze::RenderTarget& _target, ze::RenderInfo _info) const override {

    }
};

class ConstraintScene : public ze::Scene {
public:
    ConstraintScene(const ze::Window& _window) :
        desktop(_window) {

    }
    ~ConstraintScene() override = default;

    void update(float _delta) override {
        desktop.update(_delta);
    }

    bool handleEvent(const ze::Event& _event) override {
        if (_event.type == ze::Event::EventType::WindowSizeChanged) {
            desktop.notifyWindowSizeChanged(ze::Vector2f(static_cast<float>(_event.size.width), static_cast<float>(_event.size.height)));
        }
        if (desktop.handleEvent(_event)) {
            return true;
        }
        return false;
    }

    void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override {
        desktop.render(_target, _info);
    }

    void initialise(const ze::Vector2f& _size) {
        desktop.initialise(_size);

        {
            auto nav = std::make_shared<NavigationPanelControl>();
            desktop.m_Root->addComponent(nav, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::DockConstraint(ze::DockDirection::Top)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(64.0f))
            ));
        }

        auto & c = std::make_shared<ze::BlockControl>();
        c->colour = ze::Colour::Red;

        const float gap = 10.0f;
        const float size = 0.4f;

        desktop.m_Root->addComponent(c, ze::ConstraintSet(
            std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(gap)),
            std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(gap)),
            std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(1.0f)),
            std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(size))
        ));

        {
            // right
            auto& r = std::make_shared<ze::BlockControl>();
            r->colour = ze::Colour::Blue;

            desktop.m_Root->addComponent(r, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(c.get(), gap)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(gap)),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(size))
            ));
            {
                // right right
                auto& rr = std::make_shared<ze::BlockControl>();
                rr->colour = ze::Colour::Magenta;

                desktop.m_Root->addComponent(rr, ze::ConstraintSet(
                    std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(r.get(), gap)),
                    std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(gap)),
                    std::shared_ptr<ze::Constraint>(new ze::FillConstraint()),
                    std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(size))
                ));
            }
        }
        {
            // top
            auto& r = std::make_shared<ze::BlockControl>();
            r->colour = ze::Colour::Green;

            desktop.m_Root->addComponent(r, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(gap)),
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(c.get(), gap)),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(size))
            ));
        }
        {
            // top right
            auto& r = std::make_shared<ze::BlockControl>();
            r->colour = ze::Colour::Yellow;

            desktop.m_Root->addComponent(r, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(c.get(), gap)),
                std::shared_ptr<ze::Constraint>(new ze::FollowConstraint(c.get(), gap)),
                std::shared_ptr<ze::Constraint>(new ze::AspectRatioConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(size))
            ));
        }
    }

    ze::Desktop desktop;
};

class AnimationScene : public ze::Scene {
public:
    AnimationScene(const ze::Window& _window) :
        desktop(_window) {

    }
    ~AnimationScene() override = default;

    void update(float _delta) override {
        desktop.update(_delta);
    }

    bool handleEvent(const ze::Event& _event) override {
        if (_event.type == ze::Event::EventType::WindowSizeChanged) {
            desktop.notifyWindowSizeChanged(ze::Vector2f(static_cast<float>(_event.size.width), static_cast<float>(_event.size.height)));
        }
        if (desktop.handleEvent(_event)) {
            return true;
        }
        return false;
    }

    void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override {
        desktop.render(_target, _info);
    }

    void initialise(const ze::Vector2f& _size) {
        desktop.initialise(_size);
        {
            auto nav = std::make_shared<NavigationPanelControl>();
            desktop.m_Root->addComponent(nav, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::DockConstraint(ze::DockDirection::Top)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(64.0f))
            ));
        }
    }

    ze::Desktop desktop;
};

class ControlScene : public ze::Scene {
public:
    ControlScene(ze::TextureManager& _textureManager, const ze::Window& _window) :
        desktop(_window),
        textureManager(_textureManager) {

    }
    ~ControlScene() override = default;

    void update(float _delta) override {
        desktop.update(_delta);
    }

    bool handleEvent(const ze::Event& _event) override {
        if (_event.type == ze::Event::EventType::WindowSizeChanged) {
            desktop.notifyWindowSizeChanged(ze::Vector2f(static_cast<float>(_event.size.width), static_cast<float>(_event.size.height)));
        }
        if (desktop.handleEvent(_event)) {
            return true;
        }
        return false;
    }

    void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override {
        desktop.render(_target, _info);
    }

    void initialise(const ze::Vector2f& _size) {
        desktop.initialise(_size);
        {
            auto nav = std::make_shared<NavigationPanelControl>();
            desktop.m_Root->addComponent(nav, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::DockConstraint(ze::DockDirection::Top)),
                std::shared_ptr<ze::Constraint>(new ze::RelativeConstraint(1.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(64.0f))
            ));
        }
        {
            const float margin = 2.0f;
            const ze::Vector2f textureSize(textureManager.getTexture(iconTextureName).getSize());

            auto backgroundBlock = std::make_shared<ze::BlockControl>();
            backgroundBlock->colour = ze::Colour::White;
            desktop.m_Root->addComponent(backgroundBlock, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::CenterConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::CenterConstraint()),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(textureSize.x + margin * 2.0f)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(textureSize.y + margin * 2.0f))
            ));
            auto texturedBlock = std::make_shared<ze::BlockControl>();
            texturedBlock->colour = ze::Colour::White;
            texturedBlock->texture = &textureManager.getTexture(iconTextureName);
            texturedBlock->textureBounds = ze::FloatRect(ze::Vector2f(), textureSize);
            backgroundBlock->addComponent(texturedBlock, ze::ConstraintSet(
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(margin)),
                std::shared_ptr<ze::Constraint>(new ze::AbsoluteConstraint(margin)),
                std::shared_ptr<ze::Constraint>(new ze::FillConstraint(margin)),
                std::shared_ptr<ze::Constraint>(new ze::FillConstraint(margin))
            ));
        }



    }

    ze::Desktop desktop;
    ze::TextureManager& textureManager;
};

int main(int _argc, char** _argv) {
    ze::Application app;

    if (!app.initialise(ze::VideoMode(800, 800, "Zeno Interaction"))) {
        return EXIT_FAILURE;
    }

    ze::TextureManager textureManager;
    if (!textureManager.loadTexture(iconTextureName, iconTextureName)) {
        return EXIT_FAILURE;
    }

    ze::FontManager fontManager;
    if (!fontManager.loadFont(fontName, fontName, 64)) {
        return EXIT_FAILURE;
    }

    const auto& window = app.getWindow();
    const auto& windowSize = ze::Vector2f(window.getSize());

    constraintScene = std::make_shared<ConstraintScene>(window);
    ((ConstraintScene*)constraintScene.get())->initialise(windowSize);
    animationScene = std::make_shared<AnimationScene>(window);
    ((AnimationScene*)animationScene.get())->initialise(windowSize);
    controlScene = std::make_shared<ControlScene>(textureManager, window);
    ((ControlScene*)controlScene.get())->initialise(windowSize);

    changeSceneFxn = [&app](int _sceneId) -> void {
        ze::Scene* scene = nullptr;
        switch (_sceneId) {
        case ConstraintSceneId:
            scene = constraintScene.get();
            break;
        case AnimationSceneId:
            scene = animationScene.get();
            break;
        case ControlSceneId:
            scene = controlScene.get();
            break;
        }
        app.setScene(scene);
    };

    changeSceneFxn(ControlSceneId);

    app.start();

    return EXIT_SUCCESS;
}