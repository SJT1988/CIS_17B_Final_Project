#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

/*
size_t is shorthand for the unsigned int size of a container.
we may have LOTS of components so it is good to have a large supply of IDs.
*/
using ComponentID = std::size_t;

/*
Every time we call this, lastID will remember what it was last.
So when we return lastID++, we will get the next one.
*/
inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

/*
Gets a component's ID.
*/
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

// Entities are not allowed to hold more than this many components
constexpr std::size_t maxComponents = 32;

/*
These two lines define a component array for an entity, which will
allow us to compare cap and compare components we already have so
that duplicates are not introduced
*/
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

// +------------------------+
// | $$$ COMPONENT CLASS $$$|
// +------------------------+

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}
};

// +---------------------+
// | $$$ ENTITY CLASS $$$|
// +---------------------+

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw()
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	// ComponentManager will loop through all components and destroy those that are inactive
	void destroy() { active = false; }

	// Used during tests if component already exists
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		/* When we get a specific kind of component c, it will
		always have the same position in the component array,
		based on its componentTypeID:
		*/
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

// +----------------------+
// | $$$ MANAGER CLASS $$$|
// +----------------------+

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities),
			std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};