#include "Logger.h"

namespace Render2D
{
	LogLevel Logger::s_Level = LogLevel::Trace;

	void Logger::SetLevel(LogLevel newLevel)
	{
		s_Level = newLevel;
	}
}
