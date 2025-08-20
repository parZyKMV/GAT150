#pragma once
#include "Framework/Object.h"
#include "Logger.h"
#include "StringHelper.h"
#include "Singleton.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname)	\
class Register##classname{			\
	public:							\
	Register##classname() {			\
		viper::Factory::Instance().Register<classname>(#classname);\
	}								\
};									\
Register##classname register_##classname;

namespace viper {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default; // Virtual destructor for proper cleanup
		virtual std::unique_ptr<Object> Create() = 0; // Pure virtual function to create an object
	};

	template <typename T>
		requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};
	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);
	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name){
		std::string key = tolower(name);
		m_registry[key] = std::make_unique<Creator<T>>();
		Logger::Info("Registered object: {}", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name)
	{
		// Convert the name to lowercase for case-insensitive matching
		std::string key = tolower(name);
		// Find the creator in the registry
		auto it = m_registry.find(key);
		if(it != m_registry.end()) {
			// Use the creator to create an object
			return it->second->Create();
		}
		Logger::Error("Could not crate object: {}", name);

		return nullptr;
	}
}
