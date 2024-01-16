#include <renderer/renderer.h>

#include <ftul/fractal_common.h>
#include <ftul/logging.h>
#include <ftul/module.h>

#include <thread>

namespace Fractal {

    class RendererModule : public Module {
    public:
        void init(Reference<EngineSharedResources> esr) override {
            _renderer = new Renderer;

            _renderer_thread = std::thread(&RendererModule::renderer_thread_exec, this, esr);
        }

        void cleanup() override {
            _renderer_thread.join();
            delete _renderer;

            write_log("Renderer module cleaned up!");
        }

        void renderer_thread_exec(Reference<EngineSharedResources> esr) {
            _renderer->init(esr);
            write_log("Renderer intialized!");
            
            _renderer->run_main_loop();

            _renderer->quit();
        }

    private:
        Renderer* _renderer;

        std::thread _renderer_thread;
    };


    extern "C" {
        FRACTAL_EXPORT Reference<Module> fractal_alloc_module() {
            return std::make_shared<RendererModule>();
        }
    }

}






