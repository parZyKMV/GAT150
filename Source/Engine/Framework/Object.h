#pragma once
#include "Core/Serializable.h"
#include <string>

#define CLASS_PROTOTYPE(classname) \
    virtual std::unique_ptr<Object> Clone() const override { return std::make_unique<classname>(*this); };


namespace viper {
	class Object : public Serializable {
	public:
		std::string name;
		bool isActive{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::unique_ptr<Object> Clone() const = 0;

		// Inherited via Serializable
		void Read(const json::value_t& value) override;
	};
}
