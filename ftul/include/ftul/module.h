#ifndef FTUL_MODULE_H
#define FTUL_MODULE_H

namespace Fractal {

    class Module {
    public:
        virtual void init() = 0;
        virtual void cleanup() = 0;
    };

}

#endif