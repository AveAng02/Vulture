#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <vulkan/vulkan.h>

namespace vulture
{
	class Vulture
	{
	public:

		Vulture(std::string app_name_, uint32_t window_width_, uint32_t window_height_)
			: app_name(app_name_), window_height(window_height_), window_width(window_width_)
		{

		}

		void run();

	private:
		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanUp();

		void createInstance();

		uint32_t window_height, window_width;
		std::string app_name;
		GLFWwindow* window;
		VkInstance vulkan_instance;
	};
}




