#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

namespace logger = SKSE::log;
using namespace std::literals;