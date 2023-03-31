#include "Audio.h"

#include "Logging.h"
#include "Game.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace PE;
using namespace PE::Audio;


// piece of code for loadin .wav files stolen from the internet
// because i couldnt be bothered to write it myself - PT
bool IsBigEndian()
{
	int a = 1;
	return !((char *)&a)[0];
}

int ConvertToInt(char* buffer, int len)
{
	int a = 0;
	if (!IsBigEndian())
		for (int i = 0; i < len; i++)
			((char *)&a)[i] = buffer[i];
	else
		for (int i = 0; i < len; i++)
			((char *)&a)[3 - i] = buffer[i];
	return a;
}

char* LoadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		PE::LogError(std::string(fn) + " is not a valid WAVE file");
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = ConvertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = ConvertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = ConvertToInt(buffer, 2);
	in.read(buffer, 4);      //data
	in.read(buffer, 4);
	size = ConvertToInt(buffer, 4);
	char* data = new char[size];
	in.read(data, size);
	return data;
}

std::string ConvertALCErrorToString(ALCenum error)
{
	// OpenAL dosent do error messages so this is the best youre getting - PT
	std::string al_error;

	switch (error)
	{
		case ALC_NO_ERROR: al_error = "No error"; break;
		case ALC_OUT_OF_MEMORY: al_error = "Out of memory"; break;
		case ALC_INVALID_CONTEXT: al_error = "Invalid context"; break;
		case ALC_INVALID_DEVICE: al_error = "Invalid device"; break;
		case ALC_INVALID_ENUM: al_error = "Invalid enum"; break;
		case ALC_INVALID_VALUE: al_error = "Invalid value"; break;
	}

	return al_error;
}

std::string ConvertALErrorToString(ALenum error)
{
	std::string al_error;

	switch (error)
	{
		case AL_NO_ERROR: al_error = "No error"; break;
		case AL_OUT_OF_MEMORY: al_error = "Out of memory"; break;
		case AL_INVALID_ENUM: al_error = "Invalid enum"; break;
		case AL_INVALID_VALUE: al_error = "Invalid value"; break;
	}

	return al_error;
}

// AudioManager

AudioManager::AudioManager(std::string a_conetnt_path)
{
	content_path = a_conetnt_path;

	// get the name of the device
	char* device_name = (char*) alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	// initialize the device - PT
	al_device = alcOpenDevice(device_name);

	if (al_device == NULL)
	{
		if (alcGetError(al_device) == ALC_NO_ERROR)
		{
			// this should never happen, but it might - PT
			PE::LogError("Audio device is null but alcGetError() returned ALC_NO_ERROR, please report this bug");
			PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 5, { 0, 0 }));
			exit(5);
		}

		PE::LogError("Failed to initialize OpenAL device: " + ConvertALCErrorToString(alcGetError(al_device)));
	}

	al_context = alcCreateContext(al_device, NULL);
	alcMakeContextCurrent(al_context);

	if (al_context == NULL)
	{
		if (alcGetError(al_device) == ALC_NO_ERROR)
		{
			PE::LogError("OpenAL context is null but alcGetError() returned ALC_NO_ERROR, please report this bug");
			PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 6, { 0, 0 }));
			exit(6);
		}

		PE::LogError("Failed to initialize OpenAL context: " + ConvertALCErrorToString(alcGetError(al_device)));
	}
}

AudioManager::~AudioManager()
{
	alcCloseDevice(al_device);
	alcDestroyContext(al_context);
}

AudioSource* AudioManager::CreateSource(std::string name)
{
	AudioSource* source = new AudioSource;
	sources[name] = source;
	return source;
}

AudioSource* AudioManager::GetSourceByName(std::string name)
{
	AudioSource* source = nullptr;

	if (sources.contains(name))
		source = sources[name];
	else
		PE::LogWarning("Could not find audio source " + name);

	return source;
}

// AudioSoucre

AudioSource::AudioSource()
{
	alGenSources(1, &al_source);
	alSourcei(al_source, AL_SOURCE_RELATIVE, true);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &al_source);
}

void AudioSource::SetVolume(float volume)
{
	this->volume = volume;
	alSourcef(al_source, AL_GAIN, volume);
}

void AudioSource::SetPosition(Vector position)
{
	alSource3f(al_source, AL_POSITION, position.x, position.y, 0);
	this->position = position;
}

void AudioSource::SetMotion(Vector motion)
{
	alSource3f(al_source, AL_VELOCITY, motion.x, motion.y, 0);
	this->motion = motion;
}

float AudioSource::GetVolume() { return volume; }
Vector AudioSource::GetPosition() { return this->position; }
Vector AudioSource::GetMotion() { return this->motion; }

void AudioSource::Play()
{ 
	alSourcePlay(al_source);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
		PE::LogWarning("Could not play audio: " + ConvertALErrorToString(error));
}
void AudioSource::Stop() { alSourceStop(al_source); }

void AudioSource::SetResource(AudioResource res)
{
	alSourcei(al_source, AL_BUFFER, res.al_buffer);
}

// AudioListiner

AudioListener::AudioListener() {}

void AudioListener::SetPosition(Vector position)
{
	alListener3f(AL_POSITION, position.x, position.y, 0);
	this->position = position;
}

void AudioListener::SetMotion(Vector motion)
{
	alListener3f(AL_VELOCITY, motion.x, motion.y, 0);
	this->motion = motion;
}

Vector AudioListener::GetPosition() { return this->position; }
Vector AudioListener::GetMotion() { return this->motion; }

// AudioResource

AudioResource::AudioResource()
{
	alGenBuffers(1, &al_buffer);
}

AudioResource::~AudioResource()
{
	alDeleteBuffers(1, &al_buffer);
}

void AudioResource::LoadFile(std::string path)
{
	int channels, sample_rate, bps, size;

	char* wave_data = LoadWAV((content_path + "/audio/" + path).c_str(), channels, sample_rate, bps, size);

	std::ofstream file("file.wav", std::ios::binary);

	file.write(wave_data, size);

	ALenum format;

	if (channels == 1)
	{
		if (sample_rate == 8)
			format = AL_FORMAT_MONO8;
		else
			format = AL_FORMAT_MONO16;
	}
	else if (channels == 2)
	{
		if (sample_rate == 8)
			format = AL_FORMAT_STEREO8;
		else
			format = AL_FORMAT_STEREO16;
	}
	else
	{
		PE::LogWarning("Could not load WAV file, file corrupted or unsupported format");
		return;
	}


	alBufferData(al_buffer, format, wave_data, sample_rate, size);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
		PE::LogWarning("Could not load wave: " + ConvertALErrorToString(error));
}
