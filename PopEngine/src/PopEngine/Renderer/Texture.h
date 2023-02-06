#pragma once

#include <string>

#include "PopEngine/Core.h"

namespace PE
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}