#include <engine/core/Engine.hpp>

class MainApp final : public engine::core::App {
protected:
    void app_setup() override {
    }
};

int main(int argc, char** argv) {
    auto app = std::make_unique<MainApp>();
    return app->run(argc, argv);
}
