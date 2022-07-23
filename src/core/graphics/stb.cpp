#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#if defined(__MINGW32__)
#define _WIN32
#define STBI_WINDOWS_UTF8
#endif

#include "stb_image.h"
#include "stb_image_write.h"