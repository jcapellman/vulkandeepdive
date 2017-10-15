#pragma once

#include "Main.h"
#include "igfxrenderer.h"
#include "return_set.h"
#include "manager_container.h"
#include "vulkan_device.h"

class vulkan_renderer : public igfxrenderer {
	public:
		explicit vulkan_renderer(manager_container container) : igfxrenderer(container), m_instance_(nullptr)
		{
		}

		~vulkan_renderer()
		{
			vkDestroyInstance(m_instance_, nullptr);

			m_instance_ = nullptr;
		}

		void Render() override;

		string GetName() override
		{
			return "Vulkan";
		}

		return_set<bool> Initialize() override;

		return_set<bool> enumerate_devices();
	private:
		VkInstance m_instance_;
		vector<vulkan_device> m_devices_;
};
