#pragma once
#include "Core/StringHelper.h"
#include "Core/Logger.h"
#include "Core/Singleton.h"
#include "Framework/Object.h"
#include "Resources.h"
#include <memory>
#include <string>
#include <map>

namespace viper {
	class ResourcesManager : public Singleton<ResourcesManager>{
	public:
		void Clear() { m_resources.clear(); }
		template<typename T, typename ... Arge>
		requires std::derived_from<T, Resources>
		res_t<T> Get(const std::string& name, Arge&& ... arge);

		template<typename T, typename ... Arge>
		requires std::derived_from<T, Resources>
		res_t<T> GetWIthId(const std::string& id, const std::string& name, Arge&& ... arge);

		/*static ResourcesManager& Instance() {
			static ResourcesManager instance;
			return instance;
		}*/
	
	private: 
		friend class Singleton<ResourcesManager>;
		ResourcesManager() = default;
	private:
		std::map<std::string, res_t<Resources>> m_resources;
	};

	template<typename T, typename ... Arge>
	requires std::derived_from<T, Resources>
	inline res_t<T> ResourcesManager::Get(const std::string& name, Arge&& ... arge) {
	
		return GetWIthId<T>(name,name, std::forward<Arge>(arge)...);
	}

	template<typename T, typename ...Arge>
	requires std::derived_from<T, Resources>
	inline res_t<T> ResourcesManager::GetWIthId(const std::string& id, const std::string& name, Arge&& ... arge)
	{
		std::string key = tolower(id);
		auto iter = m_resources.find(key);
		//check if the resource exists
		if (iter != m_resources.end()) {
			//check if the resource is of type T
			auto base = iter->second;
			// if the resource is not of type T, return an empty res_t<T>
			auto resource = std::dynamic_pointer_cast<T>(base);
			// if the resource is not of type T, print an error message and return an empty res_t<T>
			if (resource == nullptr) {
				Logger::Warning("",key);
				return res_t<T>{};
			}
			// if the resource is of type T, return it
			return resource;
		}

		//load the resource from file
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Arge>(arge)...) == false) {
			Logger::Warning("",name);
			return res_t<T>{};
		}

		//add the resource to the map
		m_resources[key] = resource;

		return resource;
	}

	inline ResourcesManager& Resourcess() {
		return ResourcesManager::Instance();
	}
}