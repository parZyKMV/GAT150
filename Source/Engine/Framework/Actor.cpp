#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Componets/RendererComponent.h"
#include "Core/Factory.h"

namespace viper {
	FACTORY_REGISTER(Actor);
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


		//update all components
		for(auto& component : m_components) {
			if (component->isActive) component->Update(dt);
		}
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
	void Actor::AddComponents(std::unique_ptr<Component> componets)
	{
		componets->owner = this; // Set the owner of the component to this actor
		m_components.push_back(std::move(componets));
	}
}
