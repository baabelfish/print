#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace pr {

enum class Misc {
    Clear,
    None
};

enum class Ansi {
    Reset = 0,
    Bold = 1,
    Faint = 2,
    Italic = 3,
    Underline = 4,
    BlinkSlow = 5,
    BlinkRapid = 6,
    None
};

enum class Fg {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    None
};

enum class Bg {
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,
    None
};

namespace internal {

static inline std::string add0toTime(int time) {
    return (time < 10 ? "0" : "") + std::to_string(time);
}

template<typename T> inline void _ansiHelper(const T& t) {
    if (t != T::None) { std::cout << "\033[" + std::to_string(static_cast<int>(t)) + 'm'; }
}
inline void _print(const Ansi& t, std::string = "", std::string = "") { _ansiHelper(t); }
inline void _print(const Fg& t, std::string = "", std::string = "") { _ansiHelper(t); }
inline void _print(const Bg& t, std::string = "", std::string = "") { _ansiHelper(t); }
inline void _print(const Misc& t, std::string = "", std::string = "") {
    switch (t) {
        case Misc::Clear:
            std::cout << "\033[2J";
            break;
        default:
            break;
    }
}

template<typename C, typename T = typename C::value_type>
inline void _print_container(const C& c) {
    std::cout << "( ";
    for (auto& x : c) {
        std::cout << x << " ";
    }
    std::cout << ")";
}

template<typename T>
inline void _print(const T& t, std::string prefix = "", std::string postfix = "") {
    std::cout << prefix << t << postfix;
}

#define __PRINT_CONTAINER_HELPER(CTYPE)\
template<typename T> inline void _print(const CTYPE<T>& c, std::string = "", std::string = "") { _print_container(c); }

__PRINT_CONTAINER_HELPER(std::vector)
__PRINT_CONTAINER_HELPER(std::deque)
__PRINT_CONTAINER_HELPER(std::forward_list)
__PRINT_CONTAINER_HELPER(std::list)
__PRINT_CONTAINER_HELPER(std::set)
__PRINT_CONTAINER_HELPER(std::multiset)
__PRINT_CONTAINER_HELPER(std::unordered_set)
__PRINT_CONTAINER_HELPER(std::unordered_multiset)

// __PRINT_CONTAINER_HELPER(std::queue)
// __PRINT_CONTAINER_HELPER(std::priority_queue)
// __PRINT_CONTAINER_HELPER(std::array)
// __PRINT_CONTAINER_HELPER(std::stack)
// __PRINT_CONTAINER_HELPER(std::map)
// __PRINT_CONTAINER_HELPER(std::multimap)
// __PRINT_CONTAINER_HELPER(std::unordered_map)
// __PRINT_CONTAINER_HELPER(std::unordered_multimap)

template<typename T>
inline void _log(std::string filename, int line, T f, Fg fg = Fg::None, Ansi ansi = Ansi::None, Bg bg = Bg::None) {
    time_t current;
    struct tm* timeinfo;
    time(&current);
    timeinfo = localtime(&current);

    std::cout
        << "["
        << "\033[1m\033[30m"
        << internal::add0toTime(timeinfo->tm_hour) << ":"
        << internal::add0toTime(timeinfo->tm_min) << ":"
        << internal::add0toTime(timeinfo->tm_sec)
        << "\033[0m"
        << "] ";

    _print(fg);
    _print(bg);
    _print(ansi);
    _print(f);
    _print(Ansi::Reset);

    if (!filename.empty() && line != -1) {
        std::cout
            << " ("
            << "\033[1m\033[30m@"
            << filename
            << ":"
            << line
            << "\033[0m"
            << ")";
    }
    std::cout << "\033[0m" << std::endl;
}

} // namespace internal

inline void print() {}

template<typename First, typename... Args>
inline void print(First f, Args... args) {
    internal::_print(f, "", (sizeof...(args) != 0) ? ", " : "");
    if (sizeof...(args) == 0) { std::cout << "\033[0m" << std::endl; }
    print(std::forward<Args>(args)...);
}


template<typename T> inline void log(T f) { internal::_log("", -1, f); }
template<typename T> inline void logWarning(T f) { internal::_log("", -1, f, Fg::Yellow, Ansi::Bold); }
template<typename T> inline void logError(T f) { internal::_log("", -1, f, Fg::Red, Ansi::Bold); }
template<typename T> inline void logFatal(T f) { internal::_log("", -1, f, Fg::White, Ansi::Bold, Bg::Red); }

#ifndef NDEBUG
#define LOG(X) internal::_log(__FILE__, __LINE__, X)
#define LOGWarning(X) internal::_log(__FILE__, __LINE__, X, Fg::Yellow, Ansi::Bold)
#define LOGError(X) internal::_log(__FILE__, __LINE__, X, Fg::Red, Ansi::Bold)
#define LOGFatal(X) internal::_log(__FILE__, __LINE__, X, Fg::White, Ansi::Bold, Bg::Red)
#else
#define LOG(X)
#define LOGWarning(X)
#define LOGError(X)
#define LOGFatal(X)
#endif

} // namespace pr
