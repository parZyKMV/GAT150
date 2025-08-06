#pragma once  
#include <memory>  

namespace viper {  
	class Resources {  
	public:  
		Resources() = default;  
		virtual ~Resources() = default;  
	};  

	template<typename T = Resources>  
	using res_t = std::shared_ptr<T>;  
}
