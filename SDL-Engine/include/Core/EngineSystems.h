#pragma once
#include "IO/FileSystem/FileHandler.h"
#include "Events/EventSystem.h"

namespace Core
{
	inline auto MainFileHandler = IO::FileSystem::FileHandler();
	inline auto MainEventSystem = new Events::EventSystem();
}
