#include <renderer/renderer.h>

namespace Fractal {

    class RendererModule : public IModule {
    public:
        void init(Reference<EngineSharedResources> esr) override {
            _renderer_thread = std::thread(
                [](Renderer& renderer, Reference<EngineSharedResources> esr) {
                    renderer.init(esr);
                    write_log("Renderer intialized!");
                    
                    renderer.run_main_loop();

                    renderer.quit();
                }, 
                std::reference_wrapper(_renderer),
                esr
            );
        }

        void cleanup() override {
            _renderer_thread.join();
            write_log("Renderer module cleaned up!");
        }
    private:
        Renderer _renderer;
        std::thread _renderer_thread;
    };


    extern "C" {
        FRACTAL_EXPORT Reference<IModule> fractal_alloc_module() {
            return std::make_shared<RendererModule>();
        }
    }

}






