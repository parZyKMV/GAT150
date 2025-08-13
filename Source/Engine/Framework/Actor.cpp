#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Componets/RendererComponent.h"

namespace viper {
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			if(lifespan <= 0) {
				destroyed = true;
				return; // Actor is destroyed, no further updates needed
			}
		}

		for(auto& component : m_components) {
			if (component->isActive) component->Update(dt);
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : m_components) {
			if (component->isActive) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
	}

	float Actor::GetRadius()
	{
		return 50.0f;// (m_texture) ? m_texture->getSize().Length() * 0.5f * transform.scale * 0.9f : 0;
	}
	void Actor::AddComponents(std::unique_ptr<Component> componets)
	{
		componets->owner = this; // Set the owner of the component to this actor
		m_components.push_back(std::move(componets));
	}
}
