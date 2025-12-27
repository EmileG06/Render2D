#pragma once

#include "Core/Core.h"

#include <print>
#include <chrono>
#include <source_location>

namespace Render2D
{
	enum class LogLevel
	{
		Trace = 0,
		Debug,
		Info,
		Warning,
		Error,
		Critical
	};

	constexpr std::string_view LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Trace:    return "TRACE";
		case LogLevel::Debug:    return "DEBUG";
		case LogLevel::Info:     return "INFO";
		case LogLevel::Warning:  return "WARN";
		case LogLevel::Error:    return "ERROR";
		case LogLevel::Critical: return "CRIT";
		default:                 return "UNKNOWN";
		}
	}

	constexpr std::string_view LogLevelToColor(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Trace:    return "\033[37m";   // White
		case LogLevel::Debug:    return "\033[36m";   // Cyan
		case LogLevel::Info:     return "\033[32m";   // Green
		case LogLevel::Warning:  return "\033[33m";   // Yellow
		case LogLevel::Error:    return "\033[31m";   // Red
		case LogLevel::Critical: return "\033[35m";   // Magenta
		default:                 return "\033[0m";    // Reset
		}
	}

	constexpr std::string_view ResetColor = "\033[0m";

	class Logger
	{
	public:
		template <typename... Args>
		static void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
		{
			auto message = std::format(fmt, std::forward<Args>(args)...);
			std::println("[{}] {}", LogLevelToString(level), message);
		}

		template <typename... Args>
		static void LogColored(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
		{
			auto message = std::format(fmt, std::forward<Args>(args)...);
			std::println("{}[{}]{} {}",
				LogLevelToColor(level),
				LogLevelToString(level),
				ResetColor,
				message);
		}

		template <typename... Args>
		static void LogWithTime(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
		{
			auto now = std::chrono::system_clock::now();
			auto message = std::format(fmt, std::forward<Args>(args)...);
			std::println("[{:%Y-%m-%d %H:%M:%S}] [{}] {}",
				now,
				LogLevelToString(level),
				message);
		}

		template <typename... Args>
		static void LogWithLocation(
			LogLevel level,
			std::format_string<Args...> fmt,
			std::source_location loc = std::source_location::current(),
			Args&&... args)
		{
			auto message = std::format(fmt, std::forward<Args>(args)...);
			std::println("[{}] {}:{} ({}): {}",
				LogLevelToString(level),
				loc.file_name(),
				loc.line(),
				loc.function_name(),
				message);
		}

		template <typename... Args>
		static void LogFull(
			LogLevel level,
			std::format_string<Args...> fmt,
			std::source_location loc = std::source_location::current(),
			Args&&... args)
		{
			auto now = std::chrono::system_clock::now();
			auto message = std::format(fmt, std::forward<Args>(args)...);

			std::println("{}[{:%H:%M:%S}] [{}] {}:{}{} - {}",
				LogLevelToColor(level),
				now,
				LogLevelToString(level),
				loc.file_name(),
				loc.line(),
				ResetColor,
				message);
		}

		static void SetLevel(LogLevel newLevel);

	private:
		static LogLevel s_Level;
	};

}

#ifdef _DEBUG

	#define LOG_TRACE(fmt, ...)    Render2D::Logger::LogFull(Render2D::LogLevel::Trace, fmt, std::source_location::current(), ##__VA_ARGS__)
	#define LOG_DEBUG(fmt, ...)    Render2D::Logger::LogFull(Render2D::LogLevel::Debug, fmt, std::source_location::current(), ##__VA_ARGS__)
	#define LOG_INFO(fmt, ...)     Render2D::Logger::LogFull(Render2D::LogLevel::Info, fmt, std::source_location::current(), ##__VA_ARGS__)
	#define LOG_WARNING(fmt, ...)  Render2D::Logger::LogFull(Render2D::LogLevel::Warning, fmt, std::source_location::current(), ##__VA_ARGS__)
	#define LOG_ERROR(fmt, ...)    Render2D::Logger::LogFull(Render2D::LogLevel::Error, fmt, std::source_location::current(), ##__VA_ARGS__)
	#define LOG_CRITICAL(fmt, ...) Render2D::Logger::LogFull(Render2D::LogLevel::Critical, fmt, std::source_location::current(), ##__VA_ARGS__)

#else

	#define LOG_TRACE(fmt, ...)
	#define LOG_DEBUG(fmt, ...)
	#define LOG_INFO(fmt, ...)
	#define LOG_WARNING(fmt, ...)
	#define LOG_ERROR(fmt, ...)
	#define LOG_CRITICAL(fmt, ...)

#endif
