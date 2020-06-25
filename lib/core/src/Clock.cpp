#include <zeno/Core/Clock.hpp>

namespace ze {

    Clock::Clock() {
        m_Start = std::chrono::steady_clock::now();
    }
}
