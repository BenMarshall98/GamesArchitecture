#pragma once

enum class ComponentType
{
	POSITION = 0,
	RENDER = 1,
	PHYSICS = 2,
	INPUT = 3,
	PLAYBACK = 4,
	NONE = 5
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