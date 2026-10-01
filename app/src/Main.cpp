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
        auto campfire = resources->model("campfire");
        auto tree = resources->model("tree");

        shader->use();

        // Camera projection matrix.
        shader->set_mat4(
            "projection",
            graphics->projection_matrix()
        );

        // Camera view matrix.
        shader->set_mat4(
            "view",
            graphics->camera()->view_matrix()
        );

        // Position and size of our campsite model.
        glm::mat4 campfire_model = glm::mat4(1.0f);

        campfire_model = glm::translate(
            campfire_model,
            glm::vec3(0.0f, -1.8f, -5.0f)
        );

        campfire_model = glm::scale(
            campfire_model,
            glm::vec3(0.5f)
        );

        shader->set_mat4("model", campfire_model);

        campfire->draw(shader);

        glm::mat4 tree_model = glm::mat4(1.0f);

        tree_model = glm::translate(
            tree_model,
            glm::vec3(20.0f, -1.8f, -9.0f)
        );

        tree_model = glm::scale(
            tree_model,
            glm::vec3(3.5f, 5.5f, 3.5f)
        );

        shader->set_mat4("model", tree_model);

        tree->draw(shader);

        glm::mat4 tree_model2 = glm::mat4(1.0f);

        tree_model2 = glm::translate(
            tree_model2,
            glm::vec3(-30.0f, -1.8f, -11.0f)
        );

        tree_model2 = glm::scale(
            tree_model2,
            glm::vec3(3.2f, 5.0f, 3.2f)
        );

        shader->set_mat4("model", tree_model2);

        tree->draw(shader);

        glm::mat4 tree_model3 = glm::mat4(1.0f);

        tree_model3 = glm::translate(
            tree_model3,
            glm::vec3(3.0f, -1.8f, -24.0f)
        );

        tree_model3 = glm::scale(
            tree_model3,
            glm::vec3(3.0f, 4.7f, 3.0f)
        );

        shader->set_mat4("model", tree_model3);

        tree->draw(shader);
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