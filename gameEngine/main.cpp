#include <iostream>
#include<string>

#define GLEW_STATIC
#include <GL\glew.h>

#include<GLFW\glfw3.h>

#include "ResourceManager.h"
#include "Window.h"
#include "Input.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjLoader.h"
#include "ModelLoader.h"
#include "TexturedModel.h"
#include "TextureLoader.h"
#include "TextureBase.h"
#include "SimpleShader.h"
#include "Renderer.h"
#include "Input.h"
#include "FPSCamera.h"
#include "Entity.h"
#include "EntityManager.h"
#include "TerrainMeshGenerator.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "TerrainManager.h"
#include "BoundingSphere.h"
#include "Error.h"

#include <algorithm>

#include <cmath>
#include<string>


using namespace gE;


std::vector<GLuint>  indices;
std::vector<glm::vec3>  vertices;
std::vector<glm::vec2>  uvs;
std::vector<glm::vec3>  normals;


void framebuffer_size_callback(int width, int height);


// settings
unsigned int SCR_WIDTH;
unsigned int SCR_HEIGHT;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() 
{
	ResourceManager * resourceManager = new ResourceManager();
	resourceManager->loadStringPairFile("config.txt");

	if (glfwInit() == GLFW_PLATFORM_ERROR)
	{
		error("unable to initialize GLFW");
	}

	Window * window = new Window(*resourceManager);
	


	//Input * input = new Input();
	//setInputWindow(window);

	if (window->getWindow() == nullptr) 
	{
		glfwTerminate();
		error("unable to open a window");
	}


	window->setAsCurrentContext();


	SCR_WIDTH = window->getScreenWidth();
	SCR_HEIGHT = window->getscreenHeight();

	//glfwSetFramebufferSizeCallback(window->getWindow(), framebuffer_size_callback);
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		return EXIT_FAILURE;
	}

	glViewport(0, 0, window->getScreenWidth(), window->getscreenHeight());


	glEnable(GL_DEPTH_TEST);


	bool s = loadAssImp("fern.obj", indices, vertices, uvs, normals);

	ModelLoader modelLoader;
	TextureLoader textureLoader;

	Model * model = modelLoader.createModel(vertices, uvs, normals, indices);


/*	//Ritter Bounding Sphere

	bool isPointNotInSphere = false;
	std::vector<glm::vec3> notInSpherePoints;
	std::vector<glm::vec3> points(vertices);
	glm::vec3 centroid;
	double radius;

	do {
		isPointNotInSphere = false;
		
		glm::vec3 startPoint = points[rand() % (points.size()) + 0];
		glm::vec3 largestDistancePoint(startPoint);

		for (auto it : points)
		{
			glm::vec3 oldTestVec(largestDistancePoint.x - startPoint.x, largestDistancePoint.y - startPoint.y, largestDistancePoint.z - startPoint.z);
			glm::vec3 testVec(it.x - startPoint.x, it.y - startPoint.y, it.z - startPoint.z);
			if (glm::length(testVec) > glm::length(oldTestVec))
			{
				largestDistancePoint = it;
			}
		}

	//	std::cout << largestDistancePoint.x << " " << largestDistancePoint.y << " " << largestDistancePoint.z << std::endl;

		glm::vec3 secondLargestPoint(largestDistancePoint);

		for (auto it : points)
		{
			glm::vec3 oldTestVec(secondLargestPoint.x - largestDistancePoint.x, secondLargestPoint.y - largestDistancePoint.y, secondLargestPoint.z - largestDistancePoint.z);
			glm::vec3 testVec(it.x - largestDistancePoint.x, it.y - largestDistancePoint.y, it.z - largestDistancePoint.z);
			if (glm::length(testVec) > glm::length(oldTestVec))
			{
				secondLargestPoint = it;
			}
		}

		glm::vec3 midpoint((secondLargestPoint.x - largestDistancePoint.x) / 2, (secondLargestPoint.y - largestDistancePoint.y) / 2, (secondLargestPoint.z - largestDistancePoint.z) / 2);
		radius = glm::length(midpoint);
	//	std::cout << "radius: " << radius << " centroid: " << midpoint.x << " " << midpoint.y << " " << midpoint.z << std::endl;
		centroid = midpoint +largestDistancePoint;

		for (auto it : points)
		{
			double testLength = glm::length(glm::vec3(it.x - centroid.x, it.y - centroid.y, it.z - centroid.z));
			if (testLength > radius)
			{
				notInSpherePoints.push_back(it);
				isPointNotInSphere = true;
			}
		}
		points = notInSpherePoints;
		notInSpherePoints.clear();
	} while (isPointNotInSphere);

//	double radius;
//	glm::vec3 centroid;

/*	//ritter algorithm
	glm::vec3 xmin, xmax,ymax, ymin, zmin, zmax;
	xmin = ymin = zmin = glm::vec3(1,1,1) * std::numeric_limits<float>::max();
	xmax = ymax = zmax = glm::vec3(1,1,1) * std::numeric_limits<float>::min();

	for (auto p : vertices)
	{
		if (p.x < xmin.x) xmin = p;
		if (p.x > xmax.x) xmax = p;
		if (p.y < ymin.y) ymin = p;
		if (p.y > ymax.y) ymax = p;
		if (p.z < zmin.z) zmin = p;
		if (p.z > zmax.z) zmax = p;
	}

	double xSpan = glm::length(xmax - xmin);
	double ySpan = glm::length(ymax - ymin);
	double zSpan = glm::length(zmax - zmin);

	glm::vec3 dia1 = xmin;
	glm::vec3 dia2 = xmax;

	double maxSpan = xSpan;

	if (ySpan > maxSpan)
	{
		maxSpan = ySpan;
		dia1 = ymin;
		dia2 = ymax;
	}
		
	if (zSpan > maxSpan)
	{
		dia1 = zmin;
		dia2 = zmax;
	}
	//Mathf.Sqrt(Vector3.Dot(v, v))
	glm::vec3 center = (dia1 + dia2) * 0.5f;
	float sqRad = glm::sqrt(glm::dot(dia2-center, dia2-center));//(dia2 - center).sqrMagnitude;
	float radius = sqrtf(sqRad);


	for (auto p : vertices)
	{
		float d = glm::sqrt(glm::dot(p - center, p - center));

		if (d > sqRad)
		{
			float r = glm::sqrt(d);
			radius = (radius + r) * 0.5f;
			sqRad = radius * radius;
			float offset = r - radius;
			center = (radius * center + offset * p) / r;
		}
	}*/

	double radius = 0;
	double x = 0, y = 0, z = 0;
	int cnt = 0;

	for (auto it : vertices)
	{
		x += it.x;
		y += it.y;
		z += it.z;
		cnt++;
	}

	glm::vec3 centroid(x / cnt, y / cnt, z / cnt);

	for (auto it : vertices)
	{
		if (radius < glm::length(it))
		{
			radius = glm::length(it);
		}
	}

	std::cout << "radius: " << radius << " centroid: " << centroid.x << " " << centroid.y << " " << centroid.z << std::endl;

//	BoundingSphere bs1(centroid, radius);
//	BoundingSphere bs2(centroid, radius);


	//TextureBase * texture = new TextureBase(textureLoader.loadTexture("lowPolyTree.png"));

	TextureBase * diffuseCube = new TextureBase(textureLoader.loadTexture("fern.png"));
	TextureBase * specularCube = new TextureBase(textureLoader.loadTexture("fern.png"));


	TexturedModel * texturedModel = new TexturedModel(model, diffuseCube, specularCube);

	SimpleShader * simpleShader = new SimpleShader("simpleVertex.txt","simpleFragment.txt");


	Renderer * renderer = new Renderer(simpleShader, fov, window->getScreenWidth(), window->getscreenHeight());

	
	EntityManager entityManager(*renderer);

	Entity * entity = new Entity(texturedModel, glm::vec3(0,0,0));

	entityManager.addEntity(*entity);

	//INPUT
	gE::initInput(window);
	gE::registerCallbackOnResize(std::bind(&framebuffer_size_callback, RESIZE_CALLBACK_ARGS));


	TerrainMesh*  tg = new TerrainMesh(0,0,"customHeightmap.png");
	TerrainMesh*  tg2 = new TerrainMesh(1, -1, "customHeightmap.png");

	TextureBase mud(textureLoader.loadTexture("mud.png"));
	TextureBase path(textureLoader.loadTexture("path.png"));
	TextureBase fernTG(textureLoader.loadTexture("fern.png"));
	TextureBase grass(textureLoader.loadTexture("grassy2.png"));
	TextureBase blendMap(textureLoader.loadTexture("blendMap.png"));

	tg->setBlendMap(blendMap);

	tg->setDiffuseR(mud);
	tg->setSpecularR(mud);

	tg->setDiffuseG(fernTG);
	tg->setSpecularG(fernTG);

	tg->setDiffuseB(path);
	tg->setSpecularB(path);

	tg->setDiffuseBackground(grass);
	tg->setSpecularBackground(grass);

	tg2->setBlendMap(blendMap);

	tg2->setDiffuseR(mud);
	tg2->setSpecularR(mud);

	tg2->setDiffuseG(fernTG);
	tg2->setSpecularG(fernTG);

	tg2->setDiffuseB(path);
	tg2->setSpecularB(path);

	tg2->setDiffuseBackground(grass);
	tg2->setSpecularBackground(grass);

	TerrainShader * tshader = new TerrainShader("terrainVertex.txt","terrainFragment.txt");

	TerrainRenderer *  terrainRenderer = new TerrainRenderer(tshader,fov,window->getScreenWidth(),window->getscreenHeight());

	TerrainManager tm(terrainRenderer);
	tm.add(tg);
	tm.add(tg2);

	FPSCamera * cam = new FPSCamera();
	
	BoundingSphere bs1(centroid, radius);
	BoundingSphere bs2(centroid, radius);

	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)window->getScreenWidth() / (float)window->getscreenHeight(), 0.1f, 100.0f);


	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		//processInput(window->getWindow());
		if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window->getWindow(), true);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->setDeltaTime(deltaTime);

		simpleShader->startShaderProgram();
		simpleShader->loadTextures();
		// light properties
		//glm::vec3 lightColor = ;
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor(0.5f, 0.5f, 0.5f);// = lightColor   * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor(0.2f, 0.2f, 0.2f); //= diffuseColor * glm::vec3(0.2f); // low influence

		glm::vec3 lightPos(10.0f, 10.0f, 2.0f);

		simpleShader->setLightProperties(ambientColor, diffuseColor, glm::vec3(1.0f, 1.0f, 1.0f));
		simpleShader->setShininess(30.0f);
		simpleShader->setLightPosition(lightPos);

		simpleShader->setCameraPosition(cam->getCameraPosition());
		simpleShader->stopShaderProgram();


		tshader->startShaderProgram();
		tshader->loadTextures();
		tshader->setLightProperties(ambientColor, diffuseColor, glm::vec3(1.0f, 1.0f, 1.0f));
		tshader->setShininess(30.0f);
		tshader->setLightPosition(lightPos);

		tshader->setCameraPosition(cam->getCameraPosition());
		tshader->stopShaderProgram();


		entityManager.renderEntities(cam->getViewMatrix());
		tm.setCameraPos(cam->getCameraPosition());
		tm.process(cam->getViewMatrix());
		glm::vec3 camPos = cam->getCameraPosition();
	//	std::cout << tm.getHeightOfTerrain(camPos.x, camPos.z) << std::endl;

		
		bs1.update(entity->getPosition());
		bs2.update(cam->getCameraPosition());

	//	bs1.collisionBS(bs2);


		window->swapBuffers();
		glfwPollEvents();

	}


	delete window;
	glfwTerminate();
	

	return EXIT_SUCCESS;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

