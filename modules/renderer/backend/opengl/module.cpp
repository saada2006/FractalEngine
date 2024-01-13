#include <renderer/renderer.h>

#include <ftul/fractal_common.h>
#include <ftul/logging.h>
#include <ftul/module.h>

namespace Fractal {

    class RendererModule : Module {
    public:
        void init() override {
            _renderer = new Renderer;
            _renderer->init();

            write_log("Renderer intialized!");

        }

        void cleanup() override {
            _renderer->quit();
            delete _renderer;

            write_log("Renderer cleaned up!");
        }

    private:
        Renderer* _renderer;
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






