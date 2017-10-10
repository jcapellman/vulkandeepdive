#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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

#define LOG_FILENAME "log.txt"
#define APP_NAME "Vulkan Deep-dive Day 01"
