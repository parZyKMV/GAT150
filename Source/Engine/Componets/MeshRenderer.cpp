#include "MeshRenderer.h"
#include "Renderer/Mesh.h"
#include "Core/Factory.h"
#include "Resources/ResourcesManager.h"

namespace viper {
	FACTORY_REGISTER(MeshRenderer)
	void MeshRenderer::Update(float dt) {
	}

	void MeshRenderer::Draw(Renderer& renderer) {
		/*auto mesh = Resourcess().Get<Mesh>(meshName);
		if (m_mesh) {
			renderer.DrawMesh(m_mesh, transform);
		}*/
	}
}
