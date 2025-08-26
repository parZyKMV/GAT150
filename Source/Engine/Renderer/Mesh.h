#pragma once
//#include "..//Math//Vector2.h"
#include "Math//Vector3.h"
//#include "Renderer.h"
#include <vector>
#include "Math//Transform.h"
#include "Resources/Resources.h"

namespace viper {
	class Mesh : public Resources {
	public:
		Mesh() = default;
		Mesh(const std::vector<vec2> points, const vec3& color) :
			points{ points },
			color{ color } {
			CalculateRadius();
		}

		bool Load(const std::string& filename);

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return radius; }

	private:
		void CalculateRadius();

	private:
		float radius{ 0 };
		std::vector<vec2> points;
		vec3 color{ 1, 1, 1 };
	};
}
