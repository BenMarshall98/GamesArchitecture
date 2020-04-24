#pragma once

#include "Entity.h"
#include "UserCamera.h"

class UserEntity final : public Entity
{
	std::shared_ptr<UserCamera> mCamera;

public:
	UserEntity(const glm::vec3 & pPosition);
	~UserEntity() = default;

	UserEntity(const UserEntity &) = delete;
	UserEntity(UserEntity&&) = delete;
	UserEntity & operator= (const UserEntity &) = delete;
	UserEntity & operator= (UserEntity&&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Swap() override;
};

