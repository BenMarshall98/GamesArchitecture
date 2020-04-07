#pragma once

enum class ComponentType
{
	POSITION = 0,
	RENDER = 1,
	PHYSICS = 2,
	NONE = 3
};

class Component
{
	ComponentType mType;

public:
	explicit Component(const ComponentType pType) : mType(pType) {}
	virtual ~Component() = default;

	Component(const Component &) = delete;
	Component(Component&&) = delete;
	Component & operator= (const Component &) = delete;
	Component & operator= (Component&&) = delete;

	ComponentType GetType() const
	{
		return mType;
	}

	virtual void Swap() = 0;
};