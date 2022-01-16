//#pragma once
//
//#include "Shader.hpp"
//#include "Camera.hpp"
//#include <gl/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//
//#include "Camera.hpp"
//
//class Object
//{
//public:
//	Object(Shader& _shader);
//
//	//TODO : three of rule, fifth of rule
//
//	virtual ~Object();
//
//	void setVertices(float* vertices, int sz);
//
//    /*void setTexture(float *texture,int sz)
//    {
//        if(!_texture)
//            _texture = new float[sz];
//
//        memcpy(_texture, texture, sz*sizeof(float));
//        textureSize = sz;
//    }
//    void setColor(float *color,int sz)
//    {
//        if(!_color)
//            _color = new float[sz];
//
//        memcpy(_color, color, sz*sizeof(float));
//        colorSize = sz;
//    }*/
//	void setIndices(unsigned int* indices, int sz);
//
//	void preProcess();
//
//	unsigned int loadTexture(const char* imagePath);
//
//	void setBufferData();
//
//	void draw();
//
//	unsigned int getEabo()
//	{
//		return eabo;
//	}
//
//	Camera camera;
//
//	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
//
//	void mouseScrollCallback(GLFWwindow* window, double pos);
//	void inputCallback(GLFWwindow* window);
//private:
//    Shader _shader;
//    float *_vertices;
//    float *_color;
//    float *_texture;
//    
//    unsigned int *_indices;
//
//
//    //일단 지저분하지만 이렇게
//    int verticeSize;
//    /*int textureSize;
//    int colorSize;*/
//    int indicesSize;
//
//    //GLuint texture;
//    unsigned int abo, eabo;
//    
//    
//
//    //image
//    unsigned char* img_data;
//
//	//camera
//	bool bFirstMouse = true;
//	float lastX = 400.f, lastY = 300.f;
//
//	void setTextureParam();
//};
//
//
