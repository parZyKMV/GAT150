#pragma once
#include "Framework/Object.h"
#include "Logger.h"
#include "StringHelper.h"
#include "Singleton.h"
#include "Math/Transform.h"
#include "Framework/Actor.h"
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

	template <typename T>
	requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) :
			m_prototype(std::move(prototype))
		{}
		std::unique_ptr<Object> Create() override {
			return m_prototype->Clone();
		}

	private:
		std::unique_ptr<T> m_prototype;
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T>
		requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

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
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype){
		// Convert the name to lowercase for case-insensitive matching
		std::string key = tolower(name);

		//add to registry
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		Logger::Info("{} prototype added to factor.", name);
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
			auto object = it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release(); // Release ownership of the object to return a unique_ptr
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Type mismatch of factory object: {}", name);
		}
		else {
			Logger::Error("Could not crate factory object: {}", name);
		}
		return nullptr;
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name) {
		return Factory::Instance().Create<T>(name);
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = viper::Transform{ position, rotation, scale };
		return instance;
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = transform;
		return instance;
	}
}
