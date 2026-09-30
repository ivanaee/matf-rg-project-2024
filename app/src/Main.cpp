#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>

class MainController : public engine::core::Controller {
protected:
    void initialize() override {
        engine::graphics::OpenGL::enable_depth_testing();
    }

    void update() override {
        auto platform =
            engine::core::Controller::get<engine::platform::PlatformController>();

        auto camera =
            engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();

        float dt = platform->dt();

        if (platform->key(engine::platform::KEY_W).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::FORWARD, dt
            );
        }

        if (platform->key(engine::platform::KEY_S).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::BACKWARD, dt
            );
        }

        if (platform->key(engine::platform::KEY_A).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::LEFT, dt
            );
        }

        if (platform->key(engine::platform::KEY_D).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::RIGHT, dt
            );
        }

        auto mouse = platform->mouse();

        camera->rotate_camera(mouse.dx, mouse.dy);
        camera->zoom(mouse.scroll);
    }

    void begin_draw() override {
        engine::graphics::OpenGL::clear_buffers();
    }

    void draw() override {
        auto resources =
            engine::core::Controller::get<engine::resources::ResourcesController>();

        auto graphics =
            engine::core::Controller::get<engine::graphics::GraphicsController>();

        auto shader = resources->shader("basic");
        auto backpack = resources->model("backpack");

        shader->use();

        shader->set_mat4(
            "projection",
            graphics->projection_matrix()
        );

        shader->set_mat4(
            "view",
            graphics->camera()->view_matrix()
        );

        shader->set_mat4(
            "model",
            glm::mat4(1.0f)
        );

        backpack->draw(shader);
    }

    void end_draw() override {
        engine::core::Controller::get<engine::platform::PlatformController>()
            ->swap_buffers();
    }
};

class MainApp final : public engine::core::App {
protected:
    void app_setup() override {
        auto main_controller = register_controller<MainController>();

        main_controller->after(
            engine::core::Controller::get<engine::core::EngineControllersEnd>()
        );
    }
};

int main(int argc, char** argv) {
    auto app = std::make_unique<MainApp>();
    return app->run(argc, argv);
}