#include "PlaybackComponent.h"

PlaybackComponent::PlaybackComponent() : Component(ComponentType::PLAYBACK)
{
}

void PlaybackComponent::AddPlayback(const Playback& pPlayback)
{
	if (mPlaybackList.empty())
	{
		mPlaybackList.push_back(pPlayback);
		return;
	}
	
	for (int i = mPlaybackList.size() - 1; i >= 0; i--)
	{
		if (pPlayback.mTime > mPlaybackList[i].mTime)
		{
			//TODO: Check if at end
			mPlaybackList.insert(mPlaybackList.begin() + i + 1, pPlayback);
			return;
		}
	}
}

void PlaybackComponent::Swap()
{
	//Do Nothing
}

std::tuple<Playback, Playback> PlaybackComponent::GetPlaybackAtTime(float pTime)
{
	std::tuple<Playback, Playback> result;

	if (mPlaybackList.empty())
	{
		std::get<0>(result).mTime = pTime;
		std::get<1>(result).mTime = pTime;

		return result;
	}

	if (mPlaybackList.size() == 1)
	{
		std::get<0>(result) = mPlaybackList[0];
		std::get<1>(result) = mPlaybackList[0];
		return result;
	}
	
	for (int i = mPlaybackList.size() - 1; i >= 1; i--)
	{
		if (pTime > mPlaybackList[i - 1].mTime)
		{
			std::get<0>(result) = mPlaybackList[i - 1];
			std::get<1>(result) = mPlaybackList[i];
			return result;
		}
	}

	return result;
}