#pragma once
// Pixel Logging
#include<spdlog/spdlog.h>
#include<cstdio>

#define PX_Info(str, ...) spdlog::info(str, __VA_ARGS__)
#define PX_Error(str, ...)spdlog::critical(str, __VA_ARGS__)
#define PX_Warning(str, ...) spdlog::warn(str, __VA_ARGS__)