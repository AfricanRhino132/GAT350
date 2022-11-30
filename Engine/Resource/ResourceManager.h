#pragma once
#include "Resource.h"
#include "Core/Utilities.h"

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <cstdarg>

namespace neu
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Initialize();
		void Shutdown();
		
		template <typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& key, TArgs... args);

		template <typename T>
		std::vector<std::shared_ptr<T>> Get();

		template <typename T>
		void Add(const std::string& name, std::shared_ptr<T> resource);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;

	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& key, TArgs... args)
	{
		std::string lowerKey = ToLower(key);

		if (m_resources.find(lowerKey) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[lowerKey]);
		}
		else
		{
			std::shared_ptr<T> resource = std::make_shared<T>();

			resource->Create(key, args...);

			m_resources[lowerKey] = resource;

			return resource;
		}
	}

	template <typename T>
	inline std::vector<std::shared_ptr<T>> ResourceManager::Get()
	{
		std::vector<std::shared_ptr<T>> result;

		for (auto& resource : m_resources)
		{
			// get the value of the map (first = key, second = value)
			// the value is a shared_ptr, get() the raw pointer and try to cast to type T*
			if (dynamic_cast<T*>(resource.second.get()))
			{
				// if it is of type T, add the shared pointer to the vector
				result.push_back(std::dynamic_pointer_cast<T>(resource.second));
			}
		}

		return result;
	}

	template<typename T>
	inline void ResourceManager::Add(const std::string& name, std::shared_ptr<T> resource)
	{
		m_resources[ToLower(name)] = resource;
	}

}