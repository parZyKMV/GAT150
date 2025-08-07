#pragma once

namespace viper {
	template <typename T>
	class Singleton {
	public:
		Singleton(const Singleton&) = delete; // Delete copy constructor

		Singleton& operator = (const Singleton&) = delete; // Delete copy assignment operator

		static T& Instance() {
			static T instance; // Guaranteed to be destroyed.
			return instance;   // Instantiated on first use.
		}
	protected:
		Singleton() = default; // Private constructor to prevent instantiation

	};

}
