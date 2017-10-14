#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "vulkan-1.lib")

#define APP_NAME "Vulkan Deep-dive Day 01"

#define FILENAME_CONFIG "config.cfg"
#define FILENAME_LOG "log.txt"
