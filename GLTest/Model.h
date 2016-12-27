#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Standard.h"

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;


#ifndef MODEL_H
#define	MODEL_H

//	Indexed rendering member using three points
struct face {
	GLuint p1;
	GLuint p2;
	GLuint p3;

	face(GLuint x, GLuint y, GLuint z) : p1(x), p2(y), p3(z) {}
};

//	3D bounding box descriptor
struct boundingBox {
	vec3 bot;
	vec3 top;

	boundingBox() : bot(vec3(0, 0, 0)), top(vec3(0, 0, 0)) {}
	boundingBox(vec3 bot, vec3 top) : bot(bot), top(top) {}
};


class Model {
public:
	Model();
	Model(char* filePath);
	~Model();

	void loadModel(char* filePath);
	void loadBox();

	vec4* getVerts();
	face* getFaces();
	vec4* getNorms();
	vec2* getTex();
	GLuint numVerts();
	GLuint numFaces();
	GLuint numNorms();
	GLuint numTex();
	boundingBox getExtent();

	void setVAO(GLuint inx);
	GLuint vao();


private:
	vec4* vertices = nullptr;
	GLuint nverts = 0;

	face* faces = nullptr;
	GLuint nfaces = 0;

	vec4* normals = nullptr;
	GLuint nnorms = 0;

	vec2* tex = nullptr;
	GLuint ntex = 0;

	boundingBox bound;

	GLuint vaoInx = -1;


	void loadingBar(char* filePath, int cur, int goal);
	vec4 newell(vec4 p1, vec4 p2, vec4 p3);
	void readFile(char* filePath);
};

#endif