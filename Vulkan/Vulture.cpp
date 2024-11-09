
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Vulture.h"

namespace vulture
{
	void Vulture::run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}

	void Vulture::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		char* temp_name = &app_name[0];

		window = glfwCreateWindow(window_width, window_height, 
								temp_name, nullptr, nullptr);
	}

	void Vulture::initVulkan()
	{
		createInstance();
	}

	void Vulture::createInstance()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		std::vector<const char*> extensionList;

		// query extensions
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (int i = 0; i < glfwExtensionCount; i++)
		{
			extensionList.push_back(glfwExtensions[i]);
		}

		extensionList.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

		uint32_t extCount = 0;

		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);

		std::vector<VkExtensionProperties> extList (extCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extList.data());

		std::cout << "Available Extensions:\n";

		bool included = false;

		for (int i = 0; i < extList.size(); i++)
		{
			included = false;

			for (int j = 0; j < extensionList.size(); j++)
			{
				if (strcmp(extList[i].extensionName, extensionList[j]) == 0)
				{
					included = true;
					break;
				}
			}

			if (included)
				std::cout << "\tincluded";
			else
				std::cout << "\t        ";

			std::cout << '\t' << extList[i].extensionName << '\n';
		}

		// defining app info for vulkan instance
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Creating a vulkan instance
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = (uint32_t) extensionList.size();
		createInfo.ppEnabledExtensionNames = extensionList.data();
		createInfo.enabledLayerCount = 0;
		createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

		// Creating vulkan instance
		if (vkCreateInstance(&createInfo, nullptr, &vulkan_instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void Vulture::mainLoop()
	{
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void Vulture::cleanUp()
	{
		vkDestroyInstance(vulkan_instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}
}


