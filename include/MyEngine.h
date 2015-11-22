#ifndef MY_ENGINE_H
#define MY_ENGINE_H

#include "SimpleGraphicsEngine.h"

using namespace SGE;

class Planet;
class Quad;
class MyObject3D;

struct Material
{
	glm::vec3 color_diffuse;
	glm::vec3 color_specular;
	float reflectance; // [0, 1]
	float specular_reflectance; // [0, 1], part of reflectance
	float specular_polish; // [0, 1]
};

//! The actual program extending SimpleGraphicsEngine
/*!
	Here, all objects can be added to the scene_ and input is handled outside of
	SimpleGraphicsEngine.
*/
class MyEngine : public SimpleGraphicsEngine {
public:
	MyEngine();
	~MyEngine();
	virtual void update();
	virtual void render();
	static void mouseScrollCallback(GLFWwindow * window, double dx, double dy);
	static void cursorPosCallback(GLFWwindow * window, double x, double y);
	static void keyCallback(
		GLFWwindow * window,
		int key,
		int scancode,
		int action,
		int mods);
	void updateCameraController();
	template <class T>
	void Delay(T* input, T end_val, float speed);
private:
	void voxelizeScene();
	void renderVolume();
	void renderGlobal();
	void renderLocalDiffuse();

	void init3DTexture();

	GLuint tex3D;
	int tex_size = 64;
	GLuint shader_rendertexture;
	GLuint shader_display;


	// FBO
	FBO* fbo1_;
	FBO* fbo2_;

	// Cameras
	static Object3D* camera_;
	OrthoCamera* voxelizer_camera_;
	PerspectiveCamera* basic_cam_;

	// Objects
	//Planet* planet_;
	Quad* quad_;
	TriangleMesh* cube_;
	TriangleMesh* floor_mesh_;
	TriangleMesh* bunny_mesh_;

	MyObject3D* bunny_;
	MyObject3D* floor_;

	LightSource* light_;

	// Materials
	Material material1_;
	Material material2_;

	float roll_goal;
	float pitch_goal;
	float yaw_goal;

	float roll;
	float pitch;
	float yaw;

	glm::vec3 camera_pos; 
	glm::vec3 camera_pos_goal; 
	float xmouse;
	float ymouse;

	float delay_counter_;
	int frame_counter_;

	// Shaders
	GLuint shader_phong_;
	GLuint shader_plaintexture_;
	GLuint shader_simplevolume_;
	GLuint shader_worldpositionoutput_;
	GLuint shader_global_;
	GLuint shader_voxelization_;
};

class MyObject3D : public Object3D {
public:
	MyObject3D(Material material);
	~MyObject3D();
	void render(glm::mat4 M, GLuint program_ID);
private:
	Material material_;
};

class Quad : public Object3D {
public:
	Quad();
	~Quad();
private:
	TriangleMesh* mesh_;
};

class Planet : public Object3D {
public:
	Planet();
	~Planet();
private:
	TriangleMesh* mesh_;
	void buildIcosahedron(
		float radius, // Kkm
		std::vector<glm::vec3>* positions,
		std::vector<glm::vec3>* normals,
		std::vector<unsigned short>* elements);
};

#endif