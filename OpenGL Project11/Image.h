
#pragma once
#include <iostream>
#include <GL/glut.h>

using namespace std;
class Image {
public:
	GLuint text_id;
public:
	Image();
	Image(char* text) {
		LoadText(text, text_id);
	}
	~Image();
public:
	void LoadText(char* text, GLuint& text_id);
};

class Loadimage
{
};
