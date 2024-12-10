#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <queue>
#include <vector>
#include <string>
#include <string_view>
#include <bitset>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <unordered_map>

// include spdlog
#define FMT_HEADER_ONLY
#define FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef BOOK_EXPORT
#   ifdef _MSC_VER
#       define BOOK_API __declspec(dllexport)
#   else
#       define BOOK_API __attribute__((visibility("default")))
#   endif
#else
#   ifdef _MSC_VER
#       define BOOK_API __declspec(dllimport)
#   else
#       define BOOK_API
#   endif
#endif

// runtime assertion
#define BOOK_ASSERT assert

// static assertion
#   if defined(__clang__) || defined(__gcc__)
#       define BOOK_STATIC_ASSERT _Static_assert
#   else
#       define BOOK_STATIC_ASSERT static_assert
#   endif

// function inlining
#   if defined(__clang__) || defined(__gcc__)
#       define BOOK_INLINE __attribute__((always_inline)) inline
#       define BOOK_NOINLINE __attribute__((noinline))
#   elif defined(_MSC_VER)
#       define BOOK_INLINE __forceinline inline
#       define BOOK_NOINLINE noinline(noinline)
#else
#    define BOOK_INLINE inline
#   define BOOK_NOINLINE
#endif

// console logging
namespace Book
{
    // typeid
    template<typename T>
    BOOK_INLINE constexpr uint32_t TypeID()
    {
        return static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&typeid(T)));
    }

    struct BOOK_API Logger
    {
        using SPDLog = std::shared_ptr<spdlog::logger>;

        BOOK_INLINE Logger()
        {
            spdlog::set_pattern("%^[%T]-[#%t] %n: %v%$");
            spdlog::set_level(spdlog::level::trace);
        }

        BOOK_INLINE static SPDLog& RefCore()
        {
            static Logger logger;
            return logger.m_SPDCore;
        }

        BOOK_INLINE static SPDLog& RefClient()
        {
            static Logger logger;
            return logger.m_SPDClient;
        }

    private:
        SPDLog m_SPDCore{spdlog::stdout_color_mt("CORE")};
        SPDLog m_SPDClient{spdlog::stdout_color_mt("CLIENT")};
    };
}

#ifdef BOOK_ENABLE_LOG

#   define BOOK_CORE_TRACE(...) Book::Logger::RefCore()->trace(__VA_ARGS__)
#   define BOOK_CORE_DEBUG(...) Book::Logger::RefCore()->debug(__VA_ARGS__)
#   define BOOK_CORE_INFO(...) Book::Logger::RefCore()->info(__VA_ARGS__)
#   define BOOK_CORE_WARN(...) Book::Logger::RefCore()->warn(__VA_ARGS__)
#   define BOOK_CORE_ERROR(...) Book::Logger::RefCore()->error(__VA_ARGS__)
#   define BOOK_CORE_FATAL(...) Book::Logger::RefCore()->critical(__VA_ARGS__)

#   define BOOK_CLIENT_TRACE(...) Book::Logger::RefClient()->trace(__VA_ARGS__)
#   define BOOK_CLIENT_DEBUG(...) Book::Logger::RefClient()->debug(__VA_ARGS__)
#   define BOOK_CLIENT_INFO(...) Book::Logger::RefClient()->info(__VA_ARGS__)
#   define BOOK_CLIENT_WARN(...) Book::Logger::RefClient()->warn(__VA_ARGS__)
#   define BOOK_CLIENT_ERROR(...) Book::Logger::RefClient()->error(__VA_ARGS__)
#   define BOOK_CLIENT_FATAL(...) Book::Logger::RefClient()->critical(__VA_ARGS__)

#else

#   define BOOK_CORE_TRACE(...)
#   define BOOK_CORE_DEBUG(...)
#   define BOOK_CORE_INFO(...)
#   define BOOK_CORE_WARN(...)
#   define BOOK_CORE_ERROR(...)
#   define BOOK_CORE_FATAL(...)

#   define BOOK_CLIENT_TRACE(...)
#   define BOOK_CLIENT_DEBUG(...)
#   define BOOK_CLIENT_INFO(...)
#   define BOOK_CLIENT_WARN(...)
#   define BOOK_CLIENT_ERROR(...)
#   define BOOK_CLIENT_FATAL(...)

#endif

// free allocated memory
#define BOOK_DELETE(ptr) if(!ptr) {} else {delete (ptr); ptr = nullptr;}
