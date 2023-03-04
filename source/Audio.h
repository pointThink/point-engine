#pragma once

#include <string>
#include <unordered_map>

#include "Core.h"
#include "Vector.h"

#include "AL/alc.h"

namespace PE
{
	namespace Audio
	{
		static std::string content_path;

		class ENGINE_API AudioResource
		{
			public:
			unsigned int al_buffer;

			AudioResource();
			~AudioResource();

			void LoadFile(std::string file_path);
		};

		class ENGINE_API AudioSource
		{
			private:
			float volume;

			Vector position = { 0, 0 };
			Vector motion = { 0, 0 };

			unsigned int al_source;

			public:
			AudioSource();
			~AudioSource();

			void SetVolume(float volume);
			float GetVolume();

			void SetPosition(Vector position);
			void SetMotion(Vector motion);

			Vector GetPosition();
			Vector GetMotion();
			
			void Stop();
			void Play();
			void SetResource(AudioResource res);
		};

		class ENGINE_API AudioListener
		{
			private:
			unsigned int al_listener;

			Vector position = { 0, 0 };
			Vector motion = { 0, 0 };

			public:
			void SetPosition(Vector position);
			void SetMotion(Vector motion);

			Vector GetPosition();
			Vector GetMotion();

			AudioListener();
			~AudioListener();
		};

		class ENGINE_API AudioManager
		{
			private:
			std::string content_path;

			ALCdevice * al_device = NULL;
			ALCcontext * al_context = NULL;

			AudioListener * listener = NULL; // there can only ever be one audio listiner - PT
			std::unordered_map<std::string, AudioSource *> sources;
			
			std::string ConvertALCErrorToString(ALCenum error);

			public:
			AudioManager(std::string content_path);
			~AudioManager();

			AudioSource * CreateSource(std::string name);
			AudioSource * GetSourceByName(std::string name);
		};
	}
}