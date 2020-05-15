#include "PyramidScene.h"

#include <DirectXColors.h>
#include <iomanip>
#include <sstream>


#include "CameraManager.h"
#include "ClientNetworkingManager.h"
#include "ClientSystem.h"
#include "ConstantBuffer.h"
#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "DearImGui/imgui_impl_win32.h"
#include "DearImGui/imgui_impl_opengl3.h"
#include "EntityManager.h"
#include "GrenageProjectileEntity.h"
#include "InputSystem.h"
#include "LargeProjectileEntity.h"
#include "LightingManager.h"
#include "ModelLoader.h"
#include "Octree.h"
#include "PhysicsManager.h"
#include "PhysicsSystem.h"
#include "PlaneEntity.h"
#include "PyramidShapeEntity.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "SmallProjectileEntity.h"
#include "SystemManager.h"
#include "UserEntity.h"
#include "UserInterfaceManager.h"
#include "Win32Window.h"

void PyramidScene::Load()
{
	auto octree = std::make_unique<Octree>(glm::vec3(0.0f), glm::vec3(1.0f));
	PhysicsManager::Instance()->SetPhysicsTree(std::move(octree));
	
	auto systemManager = SystemManager::Instance();

	const auto clientSystem = std::make_shared<ClientSystem>(this);
	systemManager->AddUpdateSystem(clientSystem);

	const auto inputSystem = std::make_shared<InputSystem>();
	systemManager->AddUpdateSystem(inputSystem);
	
	mPhysicsSystem = std::make_shared<PhysicsSystem>();
	systemManager->AddUpdateSystem(mPhysicsSystem);

	mPlaybackSystem = std::make_shared<PlaybackSystem>();
	systemManager->AddUpdateSystem(mPlaybackSystem);

	const auto renderSystem = std::make_shared<RenderSystem>();
	systemManager->AddRenderSystem(renderSystem);

	SceneManager::Instance()->SetTargetTime(pow(10.0f, mTargetGraphics));

	Reset();

	CameraManager::Instance()->SetPerspective(0.01f, 100.0f);

	LightingManager::Instance()->SetPointLight({ glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(1.0f, 1.0f, 1.0f) });
}

void PyramidScene::Render()
{
	const auto render = RenderManager::Instance();

	UserInterfaceManager::Instance()->NewFrame();

	ImGui::Begin("Games Architecture and Networking");
	ImGui::Text("Current Size of Pyramid %i. Size of Pyramid After Reset %i", mCurrentSizePyramid, mNextSizePyramid);
	ImGui::Text("Target Frequency of Graphics %.2f Hz", pow(10.0f, mTargetGraphics));
	ImGui::Text("Target Frequency of Network %.2f Hz", pow(10.0f, mTargetNetwork));
	ImGui::Text("Actual Frequency of Graphics %.2f Hz", SceneManager::Instance()->GetFrameRate());
	ImGui::Text("Actual Frequency of Network %.2f Hz", mActualNetwork);
	
	if (mSimulation)
	{
		ImGui::Text("Current Simulation Time %.3f", mDisplaySimulationTime);
	}
	else if (mPlayback)
	{
		ImGui::Text("Current Playback Time %.3f", mDisplayPlaybackTime);
		ImGui::Text("Current Playback Speed %.2f", mPlaybackSpeeds[mDisplayPlaybackSpeed]);
		ImGui::Text("Playback Status: %s", mPlaybackPlay ? "Playing" : "Paused");
	}

	bool check = mMainCamera;
	
	ImGui::Checkbox("Main Camera", &mMainCamera);

	if (check != mMainCamera)
	{
		if (mMainCamera)
		{
			ClientNetworkingManager::Instance()->AddSendMessage("MainCamera");
		}
		else
		{
			ClientNetworkingManager::Instance()->AddSendMessage("RemoveMainCamera");
		}
		mMainCamera = check;
	}

	if (mMainCamera)
	{
		if (!mPlayback)
		{
			auto type = "Small";

			if (mProjectile == ProjectileType::LARGE)
			{
				type = "Large";
			}
			else if (mProjectile == ProjectileType::GRENADE)
			{
				type = "Grenade";
			}
			
			ImGui::Text("Current Projectile Type : %s", type);
		}
	}

	if (ImGui::CollapsingHeader("Controls"))
	{
		if (ImGui::TreeNode("Camera"))
		{
			ImGui::BulletText("Pan Up / Down - \"Ctrl\" + W / S");
			ImGui::BulletText("Pan Left / Right - \"Ctrl\" + A / D");
			ImGui::BulletText("Pan Forward / Backwards - \"Ctrl\" + Q / E");

			ImGui::Separator();

			ImGui::BulletText("Rotate Up / Down - W / S");
			ImGui::BulletText("Rotate Left / Right - A / D");
			
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Firing"))
		{
			ImGui::BulletText("Change Projectile Type - Z / X");
			ImGui::BulletText("Fire - Spacebar");
			
			ImGui::Text("Note: Must be main camera to fire projectiles");
			ImGui::Text("Note: Must not be in playback mode to affect firing");
			
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Playback"))
		{
			ImGui::BulletText("Increase / Decrease Playback Speed - < / >");
			ImGui::BulletText("Move Playback Forward / Backward - Left / Right");
			ImGui::BulletText("Pause Playback - Up");
			ImGui::BulletText("Unpause Playback - Down");

			ImGui::Text("Note: Must be main camera to change playback");
			ImGui::Text("Note: Must be in playback mode to affect playback");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Pyramid"))
		{
			ImGui::BulletText("Increase / Decrease Pyramid Size - T / G");
			ImGui::BulletText("Apply New Pyramid Size - R");

			ImGui::Text("Note: Must be main camera to affect pyramid");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Timing"))
		{
			ImGui::BulletText("Increase / Decrease Graphics Frequency - U / J");
			ImGui::BulletText("Increase / Decrease Networking Frequency - Y / H");
			ImGui::TreePop();
		}
	}
	
	UserInterfaceManager::Instance()->EndFrame();

	render->ClearRenderTargetView(DirectX::Colors::CornflowerBlue);

	EntityManager::Instance()->Render();

	UserInterfaceManager::Instance()->Render();
	
	render->Present();
}

void PyramidScene::Update(const float pDeltaTime)
{
	//Check Key Presses

	//Reset
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('R');

		if (delay <= 0.0f && status && mMainCamera)
		{
			delay = 0.5f;

			ClientNetworkingManager::Instance()->AddSendMessage("ResetPyramid");
			
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Increase Pyramid Size
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('T');

		if (delay <= 0.0f && status && mMainCamera)
		{
			delay = 0.1f;

			ClientNetworkingManager::Instance()->AddSendMessage("IncreasePyramid");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Decrease Pyramid Size
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('G');

		if (delay <= 0.0f && status && mMainCamera)
		{
			delay = 0.1f;

			ClientNetworkingManager::Instance()->AddSendMessage("DecreasePyramid");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Change Projectile Type - Increase
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('X');

		if (delay <= 0.0f && status && mMainCamera)
		{
			delay = 0.25f;

			auto nextProjectile = static_cast<int>(mProjectile);
			nextProjectile++;

			if (static_cast<ProjectileType>(nextProjectile) == ProjectileType::NONE)
			{
				nextProjectile = 0;
			}

			mProjectile = static_cast<ProjectileType>(nextProjectile);
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Change Projectile Type - Decrease
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('Z');

		if (delay <= 0.0f && status && mMainCamera)
		{
			delay = 0.25f;

			auto nextProjectile = static_cast<int>(mProjectile);
			nextProjectile--;

			if (nextProjectile < 0)
			{
				nextProjectile = static_cast<int>(ProjectileType::NONE) - 1;
			}

			mProjectile = static_cast<ProjectileType>(nextProjectile);
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Fire Projectile
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus(VK_SPACE);

		if (delay <= 0.0f && status && mMainCamera && !mPlayback)
		{
			delay = 0.5f;

			auto cameraPosition = CameraManager::Instance()->GetViewPosition();

			//TODO: https://gamedev.stackexchange.com/questions/90443/launch-velocity-for-simple-3d-projectile
			const auto displacement = glm::vec3(0.0f) - cameraPosition;
			cameraPosition += glm::normalize(displacement) * 0.1f;

			const auto dist = glm::length(displacement);

			const auto t = 1.0f;

			const auto velocity = (1.0f / t * displacement - 0.5f * glm::vec3(0.0f, -1.0f, 0.0f) * t);

			std::ostringstream str;

			str << "AddP";
			
			if (mProjectile == ProjectileType::SMALL)
			{
				str << "S";
			}
			else if (mProjectile == ProjectileType::LARGE)
			{
				str << "L";
			}
			else if (mProjectile == ProjectileType::GRENADE)
			{
				str << "G";
			}

			for (int i = 0; i < 3; i++)
			{
				uint32_t num = *((uint32_t*)&cameraPosition[i]);
				str << std::setw(8) << std::setfill('0') << std::hex << num;
			}

			for (int i = 0; i < 3; i++)
			{
				uint32_t num = *((uint32_t*)&velocity[i]);
				str << std::setw(8) << std::setfill('0') << std::hex << num;
			}

			const auto message = str.str();

			ClientNetworkingManager::Instance()->AddSendMessage(message);  
		}
	}

	//Change Playback Speed - Increase
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus(VK_OEM_PERIOD);

		if (delay <= 0.0f && status && mPlayback)
		{
			delay = 0.25f;

			ClientNetworkingManager::Instance()->AddSendMessage("IncreasePlayback");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Change Playback Speed - Decrease
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus(VK_OEM_COMMA);

		if (delay <= 0.0f && status && mPlayback)
		{
			delay = 0.25f;

			ClientNetworkingManager::Instance()->AddSendMessage("DecreasePlayback");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Change Playback Position - Decrease
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus(VK_LEFT);

		if (delay <= 0.0f && status && mPlayback)
		{
			delay = 0.1f;

			ClientNetworkingManager::Instance()->AddSendMessage("StepBackPlayback");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Change Playback Position - Increase
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus(VK_RIGHT);

		if (delay <= 0.0f && status && mPlayback)
		{
			delay = 0.1f;

			ClientNetworkingManager::Instance()->AddSendMessage("StepUpPlayback");
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Pause Playback
	{
		const auto status = Win32Window::Instance()->GetKeyStatus(VK_UP);

		if (status && mPlayback)
		{
			ClientNetworkingManager::Instance()->AddSendMessage("PausePlayback");
		}
	}

	//UpPause Playback
	{
		const auto status = Win32Window::Instance()->GetKeyStatus(VK_DOWN);

		if (status && mPlayback)
		{
			ClientNetworkingManager::Instance()->AddSendMessage("UnpausePlayback");
		}
	}

	//Target Graphics - Decrease
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('J');

		if (delay <= 0.0f && status)
		{
			delay = 0.25f;

			mTargetGraphics -= 0.1f;

			if (mTargetGraphics < 0.0f)
			{
				mTargetGraphics = 0.0f;
			}

			SceneManager::Instance()->SetTargetTime(pow(10.0f, mTargetGraphics));
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Target Graphics - Increase
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('U');

		if (delay <= 0.0f && status)
		{
			delay = 0.25f;

			mTargetGraphics += 0.1f;

			if (mTargetGraphics > 3.0f)
			{
				mTargetGraphics = 3.0f;
			}

			SceneManager::Instance()->SetTargetTime(pow(10.0f, mTargetGraphics));
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Target Network - Decrease
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('H');

		if (delay <= 0.0f && status)
		{
			delay = 0.25f;

			mTargetNetwork -= 0.1f;

			if (mTargetNetwork < 0.0f)
			{
				mTargetNetwork = 0.0f;
			}

			std::ostringstream str;

			str << "NetT";

			const auto time = 1.0f / pow(10.0f, mTargetNetwork);

			uint32_t num = *((uint32_t*)&(time));
			str << std::setw(8) << std::setfill('0') << std::hex << num;

			const auto timeMessage = str.str();
			ClientNetworkingManager::Instance()->AddSendMessage(timeMessage);
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	//Target Network - Increase
	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('Y');

		if (delay <= 0.0f && status)
		{
			delay = 0.25f;

			mTargetNetwork += 0.1f;

			if (mTargetNetwork > 3.0f)
			{
				mTargetNetwork = 3.0f;
			}

			std::ostringstream str;

			str << "NetT";

			const auto time = 1.0f / pow(10.0f, mTargetNetwork);

			uint32_t num = *((uint32_t*)&(time));
			str << std::setw(8) << std::setfill('0') << std::hex << num;

			const auto timeMessage = str.str();
			ClientNetworkingManager::Instance()->AddSendMessage(timeMessage);
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	if (mPlaybackPlay)
	{
		mPlaybackTime += pDeltaTime * mPlaybackSpeeds[mPlaybackSpeed];
	}
	
	mSimulationTime += pDeltaTime;
	
	if (mPlaybackTime > mMaxTime)
	{
		mPlaybackTime = mMaxTime;
	}
	if (mPlaybackTime < 0.0f)
	{
		mPlaybackTime = 0.0f;
	}
	
	mPlaybackSystem->SetPlaybackTime(mPlaybackTime);

	EntityManager::Instance()->Update(pDeltaTime);
}

void PyramidScene::Unload()
{
	ClientNetworkingManager::Instance()->AddSendMessage("RemoveMainCamera");
}

void PyramidScene::Reset()
{
	mCurrentSizePyramid = mNextSizePyramid;
	mSimulation = false;
	mSimulationTime = 0.0f;
	mMaxTime = 0.0f;
	mPlaybackTime = 0.0f;
	mDisplaySimulationTime = 0.0f;
	mDisplayPlaybackTime = 0.0f;
	mPlaybackSpeed = 9;
	mDisplayPlaybackSpeed = 9;
	mPlayback = false;
	mPlaybackPlay = true;
	mPhysicsSystem->StopSimulation();
	mPlaybackSystem->StopSimulation();

	auto entityManager = EntityManager::Instance();

	entityManager->Reset();

	PhysicsManager::Instance()->Reset();

	Entity::Reset();

	entityManager->AddEntity(std::make_shared<UserEntity>(glm::vec3(1.0f, 0.5f, 1.0f)));

	entityManager->AddEntity(std::make_shared<PlaneEntity>());

	const auto offset = 1.0f / sqrt(2.0f) * 0.02f;

	auto mass = false;

	for (auto i = mCurrentSizePyramid; i >= 1; i--)
	{
		const auto y = static_cast<float>(mCurrentSizePyramid - i) * offset + 0.01f;

		for (auto j = 0; j < i; j++)
		{
			for (auto k = 0; k < i; k++)
			{
				const auto x = j * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;
				const auto z = k * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;

				entityManager->AddEntity(std::make_shared<PyramidShapeEntity>(glm::vec3(x, y, z), mass));
			}
		}

		mass = true;
	}

	ClientNetworkingManager::Instance()->AddSendMessage("ResetComplete");
}

void PyramidScene::Swap()
{
	if (mReset)
	{
		Reset();
		mReset = false;
		return;
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));

	mDisplaySimulationTime = mSimulationTime;
	mDisplayPlaybackTime = mPlaybackTime;
	mDisplayPlaybackSpeed = mPlaybackSpeed;

	EntityManager::Instance()->Swap();
}