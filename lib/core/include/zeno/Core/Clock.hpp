#ifndef INCLUDED_ZENO_CORE_CLOCK_HPP_
#define INCLUDED_ZENO_CORE_CLOCK_HPP_

#include <chrono>

namespace ze {

    class Clock {
    public:
        Clock();

        float restart() {
            return restart<float>();
        }
        float getElapsedTime() const {
            return getElapsedTime<float>();
        }

        template <typename T>
        T restart() {
            const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

            T result = std::chrono::duration<T>(now - m_Start).count();
            m_Start = now;

            return result;
        }
        template <typename T>
        T getElapsedTime() const {
            const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

            return std::chrono::duration<T>(now - m_Start).count();
        }

    private:
        std::chrono::steady_clock::time_point m_Start{};
    };

}

#endif // INCLUDED_ZENO_CORE_CLOCK_HPP_