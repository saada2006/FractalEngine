#ifndef FTUL_REFERENCE_H
#define FTUL_REFERENCE_H

#include <memory>

namespace Fractal {

    // filler stuff that I can later reimplement myself

    template<typename T>
    using Reference = std::shared_ptr<T>;

}


#endif