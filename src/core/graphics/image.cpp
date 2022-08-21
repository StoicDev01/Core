#include "image.h"




namespace core::graphics{

    // COLOR
    Color Color::red() { return Color(255, 0, 0, 255); }
    Color Color::green() { return Color(0, 255, 0, 255); }
    Color Color::blue() { return Color(0, 0, 255, 255); }
    Color Color::white() { return Color(255, 255, 255, 255); }
    Color Color::black() { return Color(0, 0, 0, 255); }

    Color::Color(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a){
        r = p_r;
        g = p_g;
        b = p_b;
        a = p_a;
    }
    
    Color::Color(){}

    core::Vector4f Color::to_glcolor(){
        return core::Vector4f(
            (float)r / 255.0f, 
            (float)g / 255.0f, 
            (float)b / 255.0f, 
            (float)a / 255.0f
        ); 
    }

    void Color::from_glcolor(core::Vector4f gl_color){
        r = uint8_t(gl_color.x * 255); 
        g = uint8_t(gl_color.y * 255);
        b = uint8_t(gl_color.z * 255);
        a = uint8_t(gl_color.w * 255);
    }

    // IMAGE
    Image::Image(core::Vector2u size, int color_channels, unsigned char* data){
        m_color_channels = color_channels;
        m_data = data;
        m_size = size;
    }

    Image::Image(Vector2u size , Color fill_color){
        m_color_channels = 4;
        // create data
        m_size = size;
        m_data = (unsigned char *)malloc(size.x * size.y * m_color_channels);
        
        // fill data with fill color
        for (auto i =0; i < size.x * size.y; i++){
            unsigned char* pixel_pointer = &m_data[i * m_color_channels];
            pixel_pointer[0] = fill_color.r;
            pixel_pointer[1] = fill_color.g;
            pixel_pointer[2] = fill_color.b;
            pixel_pointer[3] = fill_color.a;
        }
    }

    Image::Image(std::filesystem::path path){
        int size_x;
        int size_y;

        stbi_set_flip_vertically_on_load(true);  

        #ifdef __MINGW32__
            // convert windows wide char to stbi compatible char
            const wchar_t* path_utf16 = path.c_str();
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string utf8_path = converter.to_bytes(path.c_str());

            m_data = stbi_load(utf8_path.c_str(), &size_x, &size_y, &m_color_channels, 3);
        #else
            m_data = stbi_load(path.c_str(), &size_x, &size_y, &m_color_channels, 3);
        #endif

        m_size.x = (uint32_t)size_x;
        m_size.y = (uint32_t)size_y;
    }

    Image::~Image(){
        stbi_image_free(m_data);
    }

    // save a png to output path
    // FIX ME: allow other image formats
    void Image::save(std::filesystem::path p_path){
        stbi_flip_vertically_on_write(true);
        stbi_write_png((const char *)p_path.u8string().c_str(), m_size.x, m_size.y, m_color_channels, m_data, m_size.x * m_color_channels);
    }

    void Image::set_pixel(core::Vector2u pixel_pos, Color color){
        bool is_in_bounds = in_bounds(pixel_pos);
        assert(is_in_bounds);

        int offset = (pixel_pos.x + m_size.x * pixel_pos.y) * m_color_channels;

        stbi_uc *pixel_offset = m_data + offset;
        pixel_offset[0] = color.r;
        pixel_offset[1] = color.g;
        pixel_offset[2] = color.b;

        if (m_color_channels == 4)
            pixel_offset[3] = color.a;
        
    }

    Color Image::get_pixel(core::Vector2u pixel_pos) const{
        bool is_in_bounds = in_bounds(pixel_pos);
        assert(is_in_bounds);

        const stbi_uc *pixel_offset = m_data + (pixel_pos.x * m_size.x * pixel_pos.y) * m_color_channels;
        Color new_color(
            pixel_offset[0],
            pixel_offset[1],
            pixel_offset[2],
            255
        );

        if (m_color_channels == 4)
            new_color.a = pixel_offset[3];
        
        return new_color;
    }

    bool Image::in_bounds(core::Vector2u pixel_pos) const {
        if (
            pixel_pos.x > m_size.x or
            pixel_pos.y > m_size.y
        )
            return false;
        else
            return true;
    }

    bool Image::is_valid() const{
        if (m_data)
            return true;
        return false;
    }

    unsigned char* Image::get_data(){
        return m_data;
    }
}