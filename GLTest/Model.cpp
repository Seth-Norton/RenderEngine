#include "model.h"


//----------------------------------------------------------------------------
//--------------------------------	CREATION	------------------------------
//----------------------------------------------------------------------------

Model::Model() {
}

Model::Model(char* filePath) {
	readFile(filePath);
}

Model::~Model() {

}


//----------------------------------------------------------------------------
//--------------------------------	INTERFACE	------------------------------
//----------------------------------------------------------------------------

void Model::loadModel(char* filePath) {
	readFile(filePath);
}

void Model::loadBox()
{
	this->nverts = 8;
	GLint topx = .5, botx = -.5, topy = .5, boty = -.5, topz = .5, botz = -.5;
	vec4 walls[8] = {
		//	Bottom
		vec4(botx, boty, botz, 1),
		vec4(topx, boty, botz, 1),
		vec4(topx, boty, topz, 1),
		vec4(botx, boty, topz, 1),

		//	Top
		vec4(botx, topy, botz, 1),
		vec4(topx, topy, botz, 1),
		vec4(topx, topy, topz, 1),
		vec4(botx, topy, topz, 1),

	};

	this->vertices = (vec4 *)malloc(this->nverts * sizeof(vec4));
	memcpy(this->vertices, walls, this->nverts * sizeof(vec4));

	this->bound = boundingBox(vec3(botx, boty, botz), vec3(topx, topy, topz));

	
	this->nfaces = 12;
	face polys[12] = {
		//	Bot
		face(0, 1, 2),
		face(0, 2, 3),

		//	Top
		face(4, 5, 6),
		face(4, 6, 7),

		//	Front
		face(0, 1, 5),
		face(0, 5, 4),

		//	Back
		face(2, 3, 7),
		face(2, 7, 6),

		//	Right
		face(1, 2, 6),
		face(1, 6, 5),

		//	Left
		face(3, 0, 4),
		face(3, 4, 7)

	};

	
	this->faces = (face *)malloc(this->nfaces * sizeof(face));
	memcpy(this->faces, polys, this->nfaces * sizeof(face));



	this->nnorms = this->nverts;
	vec4 norms[8] = {
		newell(vertices[faces[2].p1], vertices[faces[2].p2], vertices[faces[2].p3]),
		newell(vertices[faces[2].p1], vertices[faces[2].p2], vertices[faces[2].p3]),
		newell(vertices[faces[2].p1], vertices[faces[2].p2], vertices[faces[2].p3]),
		newell(vertices[faces[2].p1], vertices[faces[2].p2], vertices[faces[2].p3]),

		newell(vertices[faces[3].p1], vertices[faces[3].p2], vertices[faces[3].p3]),
		newell(vertices[faces[3].p1], vertices[faces[3].p2], vertices[faces[3].p3]),
		newell(vertices[faces[3].p1], vertices[faces[3].p2], vertices[faces[3].p3]),
		newell(vertices[faces[3].p1], vertices[faces[3].p2], vertices[faces[3].p3])
	};

	this->normals = (vec4 *)malloc(this->nnorms * sizeof(vec4));
	memcpy(this->normals, norms, this->nnorms * sizeof(vec4));







	this->ntex = this->nverts;
	vec2 texes[12] = {
		//	Back wall
		vec2(0, 0),
		vec2(4, 0),
		vec2(4, 4),
		vec2(0, 4),

		//	Left
		vec2(0, 0),
		vec2(4, 0),
		vec2(4, 4),
		vec2(0, 4),

		//	Floor
		vec2(0, 0),
		vec2(3, 0),
		vec2(3, 3),
		vec2(0, 3)
	};

	this->tex = (vec2 *)malloc(this->ntex * sizeof(vec2));
	memcpy(this->tex, texes, this->ntex * sizeof(vec2));


	//	TODO: Move to better location
	glGenVertexArrays(1, &this->vaoInx);
	glBindVertexArray(this->vaoInx);

	GLuint vBuf, eBuf;

	glGenBuffers(1, &vBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vBuf);
	glBufferData(GL_ARRAY_BUFFER, this->nverts * sizeof(vec4), this->vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &eBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nfaces * 3 * sizeof(GLuint), this->faces, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//	Unbind vao
	glBindVertexArray(0);
}

vec4* Model::getVerts()
{
	return vertices;
}

GLuint Model::numVerts()
{
	return nverts;
}

face* Model::getFaces()
{
	return faces;
}

GLuint Model::numFaces()
{
	return nfaces;
}

vec4* Model::getNorms()
{
	return normals;
}

vec2 * Model::getTex()
{
	return tex;
}

GLuint Model::numNorms()
{
	return nnorms;
}

GLuint Model::numTex()
{
	return ntex;
}


boundingBox Model::getExtent()
{
	return bound;
}

void Model::setVAO(GLuint inx)
{
	this->vaoInx = inx;

	//if (this->vertices)
	//	free(this->vertices);
}

GLuint Model::vao()
{
	return this->vaoInx;
}


//----------------------------------------------------------------------------
//--------------------------------	FUNCTIONALITY	--------------------------
//----------------------------------------------------------------------------

vec4 Model::newell(vec4 p1, vec4 p2, vec4 p3) {
	GLfloat x, y, z;
	x = (p1.y - p2.y)*(p1.z + p2.z);
	x += (p2.y - p3.y)*(p2.z + p3.z);
	x += (p3.y - p1.y)*(p3.z + p1.z);

	y = (p1.z - p2.z)*(p1.x + p2.x);
	y += (p2.z - p3.z)*(p2.x + p3.x);
	y += (p3.z - p1.z)*(p3.x + p1.x);

	z = (p1.x - p2.x)*(p1.y + p2.y);
	z += (p2.x - p3.x)*(p2.y + p3.y);
	z += (p3.x - p1.x)*(p3.y + p1.y);

	return glm::normalize(vec4(x, y, z, 0));
}


void Model::readFile(char * filePath)
{
	char buf[1000];
	GLfloat x, y, z;
	GLfloat botx = FLT_MAX, boty = FLT_MAX, botz = FLT_MAX;
	GLfloat topx = FLT_MIN, topy = FLT_MIN, topz = FLT_MIN;
	GLuint n, i1, i2, i3;
	FILE* f;

	//	Read Header
	fopen_s(&f, filePath, "r");
	if (!f) {
		printf("ERROR: Could not open %s\n", filePath);
		return;
	}
	fscanf_s(f, "%s", buf); // ply
	if (strncmp(buf, "ply", 3)) {
		printf("ERROR: Not a ply file\n");
		return;
	}
	fscanf_s(f, "%*s %*s %*f");					//	format ascii 1.0
	fscanf_s(f, "%*s %*s %d", &nverts);		//	element vertex numPoints
	nnorms = nverts;
	fscanf_s(f, "%*s %*s %*s");					//	property float32 x
	fscanf_s(f, "%*s %*s %*s");					//	property float32 y
	fscanf_s(f, "%*s %*s %*s");					//	property float32 z
	fscanf_s(f, "%*s %*s %d", &nfaces);			//	element face numFaces
	fscanf_s(f, "%*s %*s %*s %*s %*s");			//	property list uint8 int32 vertex_indices
	fscanf_s(f, "%*s");							//	end_header

	//printf("%d vertices\n", nverts);
	//printf("%d faces\n", nfaces);

	
	vertices = (vec4 *)malloc((nverts + 16) * sizeof(vec4));
	memset(vertices, 0, nverts * sizeof(vec4));
	normals = (vec4 *)malloc(nnorms * sizeof(vec4));
	memset(normals, 0, nnorms * sizeof(vec4));

	for (GLuint i = 0; i < nverts; i++) {
		fscanf_s(f, "%f %f %f", &x, &y, &z);
		vertices[i] = vec4(x, y, z, 1.0);

		if (x < botx) botx = x;
		if (x > topx) topx = x;
		if (y < boty) boty = y;
		if (y > topy) topy = y;
		if (z < botz) botz = z;
		if (z > topz) topz = z;
	}


	bound = boundingBox(vec3(botx, boty, botz), vec3(topx, topy, topz));
	GLfloat maxDist = length(bound.top - bound.bot);

	vertices[nverts]     = vec4(botx, boty, botz, 1.0);
	vertices[nverts + 1] = vec4(topx, boty, botz, 1.0);
	vertices[nverts + 2] = vec4(topx, topy, botz, 1.0);
	vertices[nverts + 3] = vec4(botx, topy, botz, 1.0);

	vertices[nverts + 4] = vec4(botx, boty, botz, 1.0);
	vertices[nverts + 5] = vec4(botx, boty, topz, 1.0);
	vertices[nverts + 6] = vec4(botx, topy, topz, 1.0);
	vertices[nverts + 7] = vec4(botx, topy, botz, 1.0);

	vertices[nverts + 8] = vec4(topx, boty, botz, 1.0);
	vertices[nverts + 9] = vec4(topx, boty, topz, 1.0);
	vertices[nverts + 10]= vec4(topx, topy, topz, 1.0);
	vertices[nverts + 11]= vec4(topx, topy, botz, 1.0);

	vertices[nverts + 12]= vec4(botx, boty, topz, 1.0);
	vertices[nverts + 13]= vec4(topx, boty, topz, 1.0);
	vertices[nverts + 14]= vec4(topx, topy, topz, 1.0);
	vertices[nverts + 15]= vec4(botx, topy, topz, 1.0);




	faces = (face *)malloc(nfaces * sizeof(face));
	memset(faces, 0, nfaces * sizeof(face));
	for (GLuint i = 0; i < nfaces; i++) {
		fscanf_s(f, "%d %d %d %d", &n, &i1, &i2, &i3);

		if (n != 3) {
			printf("ERROR: %d faces not 3\n", n);
			return;
		}


		vec4 nor = newell(vertices[i1], vertices[i2], vertices[i3]);
		//vec4 center = (vertices[i1] + vertices[i2] + vertices[i3]) / 3;

		faces[i] = face(i1, i2, i3);
		normals[i1] += nor;
		normals[i2] += nor;
		normals[i3] += nor;
	}

	for (GLuint i = 0; i < nnorms; i++) {
		normals[i] = glm::normalize(normals[i]);
	}


	//loadingBar(filePath, nverts + nfaces, nverts + nfaces);
}




void Model::loadingBar(char* filePath, int cur, int goal) {
	int len = 40;
	float complete = (float)cur / (float)goal;

	printf("\r%25s [", filePath);
	for (int i = 0; i < len; i++) {
		if (i <= len*complete)
			printf("-");
		else
			printf(" ");

		if (i == len / 2)
			printf(" %3.0f%% ", complete * 100);
	}
	printf("]");

	if (cur == goal)
		printf("\n");
}