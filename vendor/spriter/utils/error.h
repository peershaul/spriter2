#pragma once

#define GLE(func) gle::clear();                 \
    func;                                       \
    gle::check()

namespace gle{
    void clear();
    void check();
}
