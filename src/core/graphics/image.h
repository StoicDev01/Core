#pragma once

#include <locale>
#include <codecvt>
#include <string>

#include "glm/vec2.hpp"
#include "filesystem"
#include "fmt/format.h"
#include "fstream"

#include "../system/core_utils.h"
#include "../system/transform.h"

#if defined(__MINGW32__)
#define STBI_WINDOWS_UTF8
#endif

#include "stb_image.h"
#include "stb_image_write.h"

namespace core::graphics {

    class Color {
        public:
        static Color red();
        static Color green();
        static Color blue();
        static Color white();
        static Color black();

        Color(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a);
        Color();

        core::Vector4f to_glcolor();
        void from_glcolor(core::Vector4f gl_color);

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    class Image {
        public:
        Image(core::Vector2u size , int color_channels, unsigned char* data);
        Image(core::Vector2u size , Color fill_color = Color::black());
        Image(std::filesystem::path path);
        ~Image();

        void save(std::filesystem::path p_path);
        void set_pixel(core::Vector2u pixel_pos, Color color);
        Color get_pixel(core::Vector2u pixel_pos) const ;

        bool in_bounds(core::Vector2u pixel_pos) const;
        bool is_valid() const;

        unsigned char* get_data();

        core::Vector2u m_size;
        int m_color_channels;

        private:
        unsigned char* m_data;
    };
}