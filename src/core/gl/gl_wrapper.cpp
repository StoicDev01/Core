#include "gl_wrapper.h"

namespace core::gl{
    
    uint32_t GLObjectWithID::get_id(){
        return m_id;
    }

    void GLObjectWithBind::bind(){

    }

    void GLObjectWithBind::unbind(){

    }

    // VERTEX ARRAY
    VertexArray::VertexArray(){
        glGenVertexArrays(1, &m_id);
        bind();
    };

    VertexArray::~VertexArray(){
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::bind(){
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind(){
        glBindVertexArray(0);
    }

    // VERTEX BUFFER
    VertexBuffer::VertexBuffer(GLenum buffer_type){
        glGenBuffers(1, &m_id);
        m_buffer_type = buffer_type;
        bind();
    }

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1, &m_id);
    }

    void VertexBuffer::set_data(float* vertex_buffer_data, size_t size, GLenum usage ){
        bind();
        glBufferData(m_buffer_type, size, vertex_buffer_data, usage);
    }

    void VertexBuffer::set_data(uint32_t* vertex_buffer_data, size_t size, GLenum usage ){
        bind();
        glBufferData(m_buffer_type, size, vertex_buffer_data, usage);
    }

    void VertexBuffer::bind(){
        glBindBuffer(m_buffer_type, m_id);
    }

    void VertexBuffer::unbind(){
        glBindBuffer(m_buffer_type, 0);
    }

    // SHADER
    Shader::Shader(){

    }

    Shader::Shader(std::string shader_code, GLenum shader_type){
        create(shader_code, shader_type);
    }

    Shader::Shader(std::filesystem::path shader_code_path, GLenum shader_type){
        create(shader_code_path, shader_type);
    }

    Shader::~Shader(){
        glDeleteShader(m_id);
    }

    void Shader::create(std::string shader_code, GLenum shader_type){
        verify_initialized();

        m_id = glCreateShader(shader_type);
        m_shader_code = shader_code;
        m_initialized = true;
    }

    void Shader::create(std::filesystem::path shader_code_path, GLenum shader_type){
        verify_initialized();

        m_id = glCreateShader(shader_type);
        std::ifstream shader_stream(shader_code_path, std::ios::in);

        if (shader_stream.is_open()){
            std::stringstream sstr;
            sstr << shader_stream.rdbuf();
            m_shader_code = sstr.str();
            shader_stream.close();
        }
        else{
            fmt::print("[ SHADER ] Error Could not open shader file ");
            endl();
        }

        m_initialized = true;
    }

    bool Shader::compile(){
        const char* shader_code_ptr = m_shader_code.c_str();
        glShaderSource(m_id, 1, &shader_code_ptr, NULL);
        glCompileShader(m_id);

        GLint result = GL_FALSE;
        GLint info_leng = 0;

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_leng);

        if ( result == GL_FALSE ){
            std::vector<char> shader_error_message(info_leng);
            glGetShaderInfoLog(m_id, info_leng, &info_leng, &shader_error_message[0]);
            
            fmt::print("[ SHADER COMPILE ] {}", &shader_error_message[0]);
            endl();
            return false;
        }
        return true;
    }

    void Shader::verify_initialized(){
        if (m_initialized){
            glDeleteShader(m_id);
            m_initialized = false;
            fmt::print("[ SHADER ] WARNING creating shader twice");
            endl();
        }
    }

    // SHADER PROGRAM
    ShaderProgram::ShaderProgram(){
        m_id = glCreateProgram();
    }
    ShaderProgram::~ShaderProgram(){
        detach_all();
        glDeleteProgram(m_id);
    }

    void ShaderProgram::attach(Shader& shader){
        glAttachShader(m_id, shader.get_id());
        m_attached_shaders.push_back(shader.get_id());
    }

    void ShaderProgram::detach_id(uint32_t shader_id){
        bool attached_shader = false;
        std::vector<uint32_t>::iterator shader_iterator;

        // verify if has id attached
        for (auto shader = m_attached_shaders.begin(); shader != m_attached_shaders.end(); shader++){
            if (*shader == shader_id){
                attached_shader = true;
                shader_iterator = shader;
                break;
            }
        }

        // detach
        if (attached_shader){
            glDetachShader(m_id, shader_id);
            m_attached_shaders.erase(shader_iterator);
        }
    }

    void ShaderProgram::detach(Shader& shader){
        detach_id(shader.get_id());
    }

    void ShaderProgram::detach_all(){
        auto iterator = m_attached_shaders.begin();

        while(iterator != m_attached_shaders.end()){
            glDetachShader(m_id, *iterator);
            iterator = m_attached_shaders.erase(iterator);
        }
    }

    bool ShaderProgram::link(){
        int result;
        int info_log_lenght;

        glLinkProgram(m_id);

        // Check the program
        glGetProgramiv(m_id, GL_LINK_STATUS, &result);
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_lenght);

        if ( info_log_lenght > 0 ){
            std::vector<char> program_error_message(info_log_lenght+1);
            glGetProgramInfoLog(m_id, info_log_lenght, NULL, &program_error_message[0]);
            fmt::print("[ SHADER PROGRAM LINK ] {}", &program_error_message[0]);
            endl();
        }
    }

    void ShaderProgram::use(){
        glUseProgram(m_id);
    }


}