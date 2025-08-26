#include "Mesh.h"
#include "Renderer.h"
#include "Core/File.h"
#include "Core/Logger.h"

namespace viper {
	bool Mesh::Load(const std::string& filename)
	{
		std::string buffer;
		if (!file::ReadTextFile(filename, buffer)) { Logger::Error("Could not read file: {}", filename); }

		std::stringstream stream(buffer);

		//stream >> color;

	/*	vec2 point;
		while (stream >> point)
		{
			points.push_back(point);
		}*/

		if (!stream.eof()) {
			Logger::Error("Could not parse file: {}", filename);
			return false;
		}

		return true;
	}
	/// <summary>
	///  Draws the Mesh by rendering lines
	/// </summary>
	/// <param name="renderer"></param>
	void Mesh::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		// check if points are empty, if so return
		if (points.empty()) { return; }

		renderer.SetColor(color.x, color.y, color.z);

		// iterate through all points, draw line
		for (int i = 0; i < points.size() - 1; i++) {
			vec2 p1 = (points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Mesh::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	///  Calculates the radius of the Mesh based on the points
	/// </summary>
	void Mesh::CalculateRadius()
	{
		radius = 0;
		for (auto& point : points) {
			float length = point.Length();
			if (length > radius) {
				radius = length;
			}
		}
	}


}