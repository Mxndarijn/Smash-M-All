#pragma once

#include <gl/glew.h>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

class Texture
{
public:
	Texture(const std::string& fileName);
	Texture(cv::Mat);
	~Texture();

	void bind();
	void unbind();

	std::vector<unsigned char> matToBytes(cv::Mat image);
	inline GLuint getId() const { return id; }
private:
	GLuint id;
	unsigned char* buffer;
	int width, height, BPP;
	unsigned char* t_Buffer;
};