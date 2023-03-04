
#include "Image.h"
#include "GL\glut.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Image::LoadText(char* file, GLuint& texture_id) {

    FILE* fp = NULL;
    if (fopen_s(&fp, file, "rb")) {
        printf("ERROR : No %s. \n fail to bind %d\n", file, texture_id);
        return;
    }
    int width, height, channel;
    unsigned char* images = stbi_load_from_file(fp, &width, &height, &channel, 4);
    fclose(fp);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    free(images);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);      glVertex2f(0, 0);
    glTexCoord2f(0.0, 1.0);      glVertex2f(0, 510);
    glTexCoord2f(1.0, 1.0);      glVertex2f(1024, 510);
    glTexCoord2f(1.0, 0.0);      glVertex2f(1024, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    images = 0;
}