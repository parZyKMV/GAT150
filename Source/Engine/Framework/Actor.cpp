#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Componets/RendererComponent.h"
#include "Core/Factory.h"

namespace viper {
	FACTORY_REGISTER(Actor);

	Actor::Actor(const Actor& other):
		Object{ other },
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform }
	{
		// copy components
		for(auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			m_components.push_back(std::move(clone));
		}
	}

	void Actor::Start() {
		for (auto& component : m_components) {
			component->Start();
		}
	}

	void Actor::Destroyed() {
		for (auto& component : m_components) {
			component->Destroyed();
		}
	}

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
	
	void Actor::Read(const json::value_t& value){
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);

		if(JSON_HAS(value,transform)) transform.Read(JSON_GET(value,transform));

		//read components
		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponents(std::move(component));
			}
		}
	}
}
