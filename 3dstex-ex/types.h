#pragma once

#include <stdint.h>
#include <string>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

enum PixelFormat
{
	// Standard types.
	// Must never modify these to maintain header compatibility.
	RGBA8,
	RGB8,
	RGBA5551,
	RGB565,
	RGBA4,
	LA8,
	HILO8,
	L8,
	A8,
	LA4,
	L4,
	A4,
	ETC1,
	ETC1A4,

	// Special types.
	DefaultFormat,
	PNG,
	AutoETC1,
	AutoL8,
	AutoL4,
};

typedef struct
{
	u32 magic;
	u32 verstion;
	u32 format;         //< Format matching ctrulib enum GPU_TEXCOLOR
	u32 width;          //< Width (original width to next power of 2)
	u32 height;         //< Height (original height to next power of 2)
	u32 widthOriginal;  //< Width of original input
	u32 heightOriginal; //< Height of original input
	u32 mipcount;
} Header;
