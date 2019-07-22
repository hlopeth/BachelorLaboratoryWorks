#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(const string file_name, const GLint wrapping_mode, const GLint filtering_mode)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering_mode);

    load_texture(file_name);
}

// Используется только для wrapping_mode = GL_CLAMP_TO_BORDER.
Texture::Texture(const string file_name, const GLfloat border_color[4], const GLint filtering_mode)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering_mode);

    load_texture(file_name);
}

void Texture::load_texture(string file_name)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nr_channels;
    const auto data = stbi_load(file_name.c_str(), &width, &height, &nr_channels, 0);
    if (data)
    {
        const int point_pos = file_name.find_last_of('.');
        const string file_format = file_name.substr(point_pos, file_name.length() - point_pos);
        GLint format = 0;
        if (file_format == ".jpg")
            format = GL_RGB;
        if (file_format == ".png")
            format = GL_RGBA;
        if (format == 0)
        {
            cout << "File " << file_name << " has unknown format" << endl;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture from " << file_name << endl;
    }
    stbi_image_free(data);
}
