#pragma once

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator= (const Scene&) = delete;
	Scene& operator= (Scene&&) = delete;

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(float pDeltaTime) = 0;
	virtual void Swap() = 0;
};

