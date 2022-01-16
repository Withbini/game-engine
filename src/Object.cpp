//#include "Object.hpp"
//
//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#endif
//
//Object::Object(Shader& _shader) : _shader(_shader)
//{
//	camera = Camera(glm::vec3(0.f, 0.f, 0.3f));
//}
//
//Object::~Object()
//{
//	if (_vertices)
//	{
//		delete _vertices;
//		_vertices = nullptr;
//	}
//	if (_color)
//	{
//		delete _color;
//		_color = nullptr;
//	}
//	if (_texture)
//	{
//		delete _texture;
//		_texture = nullptr;
//	}
//}
//
//void Object::setVertices(float* vertices, int sz)
//{
//	if (!_vertices)
//		_vertices = new float[sz];
//	memcpy(_vertices, vertices, sz * sizeof(float));
//	verticeSize = sz;
//}
//
//void Object::setIndices(unsigned* indices, int sz)
//{
//	if (!_indices)
//		_indices = new unsigned int[sz];
//
//	memcpy(_indices, indices, sz * sizeof(unsigned int));
//	indicesSize = sz;
//}
//
//void Object::preProcess()
//{
//	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
//	glEnableVertexAttribArray(3);*/
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//}
//
//unsigned int Object::loadTexture(const char* imagePath)
//{
//	int width, height, channel;
//	img_data = stbi_load(imagePath, &width, &height, &channel, 0);
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	if (img_data)
//	{
//		GLenum format;
//		if (channel == 1)
//			format = GL_RED;
//		else if (channel == 3)
//			format = GL_RGB;
//		else if (channel == 4)
//			format = GL_RGBA;
//		
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		setTextureParam();
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//		return -1;
//	}
//	stbi_image_free(img_data);
//
//	return textureID;
//}
//
//void Object::setBufferData()
//{
//	glGenBuffers(1, &abo);
//	glBindBuffer(GL_ARRAY_BUFFER, abo);
//	glBufferData(GL_ARRAY_BUFFER, verticeSize * sizeof(float), _vertices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &eabo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eabo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(float), _indices, GL_STATIC_DRAW);
//}
//
//void Object::setTextureParam()
//{
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//}
//
//void Object::draw()
//{
//
//	const float currentTime = glfwGetTime();
//	camera.deltaTime = currentTime - camera.lastFrame;
//	camera.lastFrame = currentTime;
//
//	_shader.use();
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, texture);
//	//glUniform1i(glGetUniformLocation(_shader.ID, "texture1"), 0);
//
//	camera.getViewMatrix();
//	camera.getProjectionMatrix();
//
//	glUniformMatrix4fv(glGetUniformLocation(_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(camera.model));
//	glUniformMatrix4fv(glGetUniformLocation(_shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
//	glUniformMatrix4fv(glGetUniformLocation(_shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
//
//	glBindVertexArray(abo);
//
//	//glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (const GLvoid*)0);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}
//
//void Object::mouseCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (bFirstMouse)
//	{
//		lastX = static_cast<float>(xpos);
//		lastY = static_cast<float>(ypos);
//		bFirstMouse = false;
//	}
//
//	const float xOffset = static_cast<float>(xpos) - lastX;
//	const float yOffset = lastY - static_cast<float>(ypos);
//	lastX = static_cast<float>(xpos);
//	lastY = static_cast<float>(ypos);
//
//	camera.processMouseMovement(xOffset, yOffset);
//}
//
//void Object::mouseScrollCallback(GLFWwindow* window, double pos)
//{
//	camera.processMouseScroll(pos);
//}
//
//void Object::inputCallback(GLFWwindow* window)
//{
//	camera.processInput(window);
//}
