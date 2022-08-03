#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema : public SimpleScene
{
public:
	Tema();
	~Tema();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	bool CollisionBalloonArrow(float posBOx, float posBOy, float posAOx, float posAOy);
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

protected:
	glm::mat3 modelMatrix;
	float radius = 70;	// radius for player
	float radiusX = 20; // radius on OX for balloon
	float radiusY = 30; // radius on OY for balloon
	float lengthX = 2;
	float lengthY = 4;
	float lengthLine = 70;
	float side = 15;

	float SpeedArrow = 0;

	float pi = 2 * acos(0.0);

	float anglePlayerCursor;


	float angularStep = 0;
	float angle;


	float posAfterClickOy;
	float posAfterClickOx;

	// Valori pentru shuriken
	float angleShuriken = 0;
	float sideShuriken = 30;

	float shurikenOx = resolution.x + 100;
	float shurikenOy = 300;
	float speedShuriken = 400;

	float secondShurikenOx = resolution.x + 100;
	float secondShurikenOy = 800;


	int transpose = 1;
	int scale = 1;


	float posArrowOx = 150;
	float posArrowOy = 0;

	float posPlayerOx = 120;
	float posPlayerOy = 350;


	float posBalloonOx = 600;
	float posBalloonOy = -100;
	float scaleFirst = 1;
	bool collisionFirst = false;

	float secondBalloonOx = 780;
	float secondBalloonOy = -1000;
	float scaleSecond = 1;
	bool collisionSecond = false;

	float thirdBalloonOx = 950;
	float thirdBalloonOy = -500;
	float scaleThird = 1;
	bool collisionThird = false;

	float forthBalloonOx = 1200;
	float forthBalloonOy = -800;
	float scaleForth = 1;
	bool collisionForth = false;

	float fifthBalloonOx = 800;
	float fifthBalloonOy = -400;
	float scaleFifth = 1;
	bool collisionFifth = false;

	float sixthBalloonOx = 800;
	float sixthBalloonOy = -400;
	float scaleSixth = 1;
	bool collisionSixth = false;

	float distancePlayerShuriken;
	float distancePlayerSecShuriken;
	int score = 0;
	int lifes = 3;

	int restrictionLeft = 500;
	int restrictionRight = (int)resolution.y;
	float baseSpeed = 200;

	int click = 0;
	float speed = 300;

	int collisionPlayer = 0;
	int collisionPlayerSec = 0;
	int scoreB = 0;
	// button
	float lengthButton = 1;
	float heightButton = 20;
	float buttonOx = 100;
	float buttonOy = 50;
	float scaleButton = 1;

	glm::vec3 center = glm::vec3(0, 0, 0);
	glm::vec3 centerPlayer = glm::vec3(0, 0, 0);
	glm::vec3 color = glm::vec3(0, 0, 1);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 green = glm::vec3(0, 1, 0);
	glm::vec3 red = glm::vec3(0.85f, 0, 0);
	glm::vec3 yellow = glm::vec3(1, 1, 0);


	glm::ivec2 resolution = window->GetResolution();
};
