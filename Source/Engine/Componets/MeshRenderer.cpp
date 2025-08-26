#include "MeshRenderer.h"
#include "Renderer/Mesh.h"
#include "Core/Factory.h"

namespace viper {
	FACTORY_REGISTER(MeshRenderer)
	void MeshRenderer::Update(float dt) {
	}

	void MeshRenderer::Draw(Renderer& renderer) {
		/*auto mesh = Resourcess().get<Mesh>(meshName);
		if (m_mesh) {
			renderer.DrawMesh(m_mesh, transform);
		}*/
	}
}
