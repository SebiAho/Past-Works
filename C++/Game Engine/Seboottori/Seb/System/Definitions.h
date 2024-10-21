#pragma once

//Engine defintions
namespace seb
{
	enum class SYS : unsigned int{ DEFAULT = 0x0, ALL = 0x1, GRAPHICS = 0x2, INPUT = 0x4 };//System id, must be exponent of 2 (2, 4, 8, ...)
	enum class COMP : unsigned int{DEFAULT = 0x0, TRANSFORM = 0x1, GRAPHICS = 0x2, INPUT = 0x4, NETWORK = 0x8};
	const unsigned int component_amount = 4;//Number of different component types

	enum class MESSAGE : unsigned int{ ALL = 0, EXIT, REMOVE_COMPONENT };
	static const char ASSET_PATH[12] = { "Seb/Assets/" };//Path to assets, if making changes to it rememper to change array size
}
