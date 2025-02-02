#pragma once
#include <AL/alc.h>
#include <AL/al.h>


static void ALC_CheckAndThrow(ALCdevice* device)
{
	if (alcGetError(device) != ALC_NO_ERROR)
	{
		throw("error with alcDevice");
	}
}


static void AL_CheckAndThrow()
{
	ALenum err = alGetError();
	if (err != AL_NO_ERROR)
	{
		throw("error with al");
	}
}