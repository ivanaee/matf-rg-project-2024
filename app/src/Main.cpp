#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <imgui.h>

class MainController : public engine::core::Controller {
protected:
    float m_fire_intensity = 1.0f;
    float m_grayscale_amount = 0.0f;

    glm::vec3 m_fire_color = glm::vec3(1.0f, 0.45f, 0.10f);

    bool m_event_sequence_active = false;
    float m_event_timer = 0.0f;
    int m_event_stage = 0;

    void initialize() override {
        engine::graphics::OpenGL::enable_depth_testing();
        engine::graphics::OpenGL::enable_blending();
        engine::graphics::OpenGL::enable_face_culling();

        engine::graphics::OpenGL::initialize_post_processing(800, 600);
    }

    void update() override {
        auto platform =
            engine::core::Controller::get<engine::platform::PlatformController>();

        auto camera =
            engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();

        float dt = platform->dt();

        // Camera movement
        if (platform->key(engine::platform::KEY_W).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::FORWARD,
                dt
            );
        }

        if (platform->key(engine::platform::KEY_S).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::BACKWARD,
                dt
            );
        }

        if (platform->key(engine::platform::KEY_A).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::LEFT,
                dt
            );
        }

        if (platform->key(engine::platform::KEY_D).state()
            == engine::platform::Key::State::Pressed) {
            camera->move_camera(
                engine::graphics::Camera::Movement::RIGHT,
                dt
            );
        }

        // Fire intensity with keyboard
        if (platform->key(engine::platform::KEY_UP).is_down()) {
            m_fire_intensity += dt;
        }

        if (platform->key(engine::platform::KEY_DOWN).is_down()) {
            m_fire_intensity -= dt;
        }

        if (m_fire_intensity > 2.0f) {
            m_fire_intensity = 2.0f;
        }

        if (m_fire_intensity < 0.1f) {
            m_fire_intensity = 0.1f;
        }

        // Start timed event sequence
        if (platform->key(engine::platform::KEY_T).state()
            == engine::platform::Key::State::JustPressed) {

            m_event_sequence_active = true;
            m_event_timer = 0.0f;
            m_event_stage = 0;

            m_fire_color = glm::vec3(1.0f, 0.45f, 0.10f);
            m_fire_intensity = 1.0f;
        }

        // Timed event sequence
        if (m_event_sequence_active) {
            m_event_timer += dt;

            if (m_event_stage == 0 && m_event_timer >= 2.0f) {
                m_fire_color = glm::vec3(1.0f, 0.15f, 0.05f);

                m_event_stage = 1;
                m_event_timer = 0.0f;
            }
            else if (m_event_stage == 1 && m_event_timer >= 2.0f) {
                m_fire_intensity = 0.15f;

                m_event_stage = 2;
                m_event_sequence_active = false;
            }
        }

        auto mouse = platform->mouse();

        camera->rotate_camera(mouse.dx, mouse.dy);
        camera->zoom(mouse.scroll);
    }

    void begin_draw() override {
        engine::graphics::OpenGL::begin_post_processing();
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

        // Camera matrices
        shader->set_mat4(
            "projection",
            graphics->projection_matrix()
        );

        shader->set_mat4(
            "view",
            graphics->camera()->view_matrix()
        );

        shader->set_vec3(
            "viewPos",
            graphics->camera()->Position
        );

        // Directional light
        shader->set_vec3(
            "dirLightDirection",
            glm::vec3(-0.2f, -1.0f, -0.3f)
        );

        shader->set_vec3(
            "dirLightColor",
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        // Point light - campfire
        shader->set_vec3(
            "pointLightPosition",
            glm::vec3(7.0f, -0.5f, -5.0f)
        );

        shader->set_vec3(
            "pointLightColor",
            m_fire_color * m_fire_intensity
        );

        // Spotlight attached to camera
        auto camera = graphics->camera();

        shader->set_vec3(
            "spotLightPosition",
            camera->Position
        );

        shader->set_vec3(
            "spotLightDirection",
            camera->Front
        );

        shader->set_vec3(
            "spotLightColor",
            glm::vec3(1.0f, 1.0f, 0.9f)
        );

        shader->set_float(
            "spotLightCutOff",
            glm::cos(glm::radians(12.5f))
        );

        shader->set_float(
            "spotLightOuterCutOff",
            glm::cos(glm::radians(17.5f))
        );

        // Campsite
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

        // Tree 1
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

        // Tree 2
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

        // Tree 3
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

        // Skybox
        auto skybox_shader = resources->shader("skybox");
        auto night_skybox = resources->skybox("night");

        graphics->draw_skybox(
            skybox_shader,
            night_skybox
        );

        // GUI
        // It is drawn before post-processing so the slider value
        // is available immediately in the current frame.
        graphics->begin_gui();

        ImGui::Begin("Lighting controls");

        ImGui::SliderFloat(
            "Fire intensity",
            &m_fire_intensity,
            0.1f,
            2.0f
        );

        ImGui::ColorEdit3(
            "Fire color",
            &m_fire_color.x
        );

        ImGui::SliderFloat(
            "Grayscale",
            &m_grayscale_amount,
            0.0f,
            1.0f
        );

        ImGui::End();

        graphics->end_gui();

        // Post-processing
        auto postprocess_shader = resources->shader("postprocess");

        postprocess_shader->use();

        postprocess_shader->set_float(
            "grayscaleAmount",
            m_grayscale_amount
        );

        engine::graphics::OpenGL::end_post_processing();
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