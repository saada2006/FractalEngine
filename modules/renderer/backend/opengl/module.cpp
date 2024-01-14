#include <renderer/renderer.h>

#include <ftul/fractal_common.h>
#include <ftul/logging.h>
#include <ftul/module.h>

#include <thread>

namespace Fractal {

    class RendererModule : Module {
    public:
        void init(EngineSharedResources* shared_resources) override {
            _renderer = new Renderer;

            _renderer_thread = std::thread(&RendererModule::renderer_thread_exec, this, shared_resources);
        }

        void cleanup() override {
            _renderer_thread.join();
            delete _renderer;

            write_log("Renderer module cleaned up!");
        }

        void renderer_thread_exec(EngineSharedResources* shared_resources) {
            _renderer->init(shared_resources);
            write_log("Renderer intialized!");
            
            _renderer->run_main_loop();

            _renderer->quit();
        }

    private:
        Renderer* _renderer;

        std::thread _renderer_thread;
    };


    extern "C" {
        FRACTAL_EXPORT Module* fractal_alloc_module() {
            return (Module*) new RendererModule;
        }

        FRACTAL_EXPORT void fractal_free_module(Module* mdl) {
            delete mdl;
        }
    }

}






