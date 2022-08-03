#include "Tema.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include "Matrix.h"

using namespace std;

Tema::Tema()
{
}

Tema::~Tema()
{
}

void Tema::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	{
		std::vector<VertexFormat> vertices;

		float angle = 0.0f;

		int num_points = 150;
		std::vector<unsigned short> indices;

		for (int i = 0; i < num_points; i++)
		{
			float angle = pi * float(i) / float(num_points);

			float x = radius * sin(angle);
			float y = radius * cos(angle);

			vertices.push_back(VertexFormat(centerPlayer + glm::vec3(x, y, 0), color));
			indices.push_back((unsigned short)i);
		}

		meshes["player"] = new Mesh("player");
		Mesh* player = CreateMesh("player", vertices, indices);

		player->SetDrawMode(GL_LINE_LOOP);
		AddMeshToList(player);
	}

	{
		std::vector<VertexFormat> verticesArrow =
		{
			VertexFormat(center, color),
			VertexFormat(center + glm::vec3(-side, side, 0), color),
			VertexFormat(center + glm::vec3(-side, -side, 0), color)
		};

		std::vector<unsigned short> indicesArrow = { 0, 1, 2 };

		meshes["arrowHead"] = new Mesh("arrowHead");
		Mesh* arrowHead = CreateMesh("arrowHead", verticesArrow, indicesArrow);

		arrowHead->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(arrowHead);
	}

	{
		glm::vec3 startPoly = center + glm::vec3(0, -radiusY, 0);
		std::vector<VertexFormat> verticesPoly =
		{
			VertexFormat(startPoly, green),
			VertexFormat(startPoly + glm::vec3(-lengthX, -lengthY, 0), green),
			VertexFormat(startPoly + glm::vec3(lengthX * 2, -lengthY * 2, 0), green),
			VertexFormat(startPoly + glm::vec3(-lengthX * 2, -lengthY * 3, 0), green),
			VertexFormat(startPoly + glm::vec3(lengthX * 2, -lengthY * 4, 0), green),
			VertexFormat(startPoly + glm::vec3(-lengthX * 2, -lengthY * 5, 0), green),
		};

		std::vector<unsigned short> indicesPoly = { 0, 1, 2, 3, 4 };

		meshes["polyline"] = new Mesh("polyline");
		Mesh* polyline = CreateMesh("polyline", verticesPoly, indicesPoly);

		polyline->SetDrawMode(GL_LINE_STRIP);
		AddMeshToList(polyline);
	}

	{
		std::vector<VertexFormat> verticesShuriken =
		{
			VertexFormat(center, green),
			VertexFormat(center + glm::vec3(sideShuriken, 0, 0), green),
			VertexFormat(center + glm::vec3(sideShuriken, sideShuriken, 0), green),
			VertexFormat(center + glm::vec3(0, sideShuriken, 0), green),
			VertexFormat(center + glm::vec3(-sideShuriken, sideShuriken, 0), green),
			VertexFormat(center + glm::vec3(-sideShuriken, 0, 0), green),
			VertexFormat(center + glm::vec3(-sideShuriken, -sideShuriken, 0), green),
			VertexFormat(center + glm::vec3(0, -sideShuriken, 0), green),
			VertexFormat(center + glm::vec3(sideShuriken, -sideShuriken, 0), green)
		};

		std::vector<unsigned short> indicesShuriken =
		{
			0, 1, 2,
			0, 3, 4,
			0, 5, 6,
			0, 7, 8
		};

		meshes["shuriken"] = new Mesh("shuriken");
		Mesh* shuriken = CreateMesh("shuriken", verticesShuriken, indicesShuriken);

		shuriken->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(shuriken);
	}

	{
		std::vector<VertexFormat> verticesButton =
		{
			VertexFormat(center, white),
			VertexFormat(center + glm::vec3(lengthButton, 0, 0), white),
			VertexFormat(center + glm::vec3(0, heightButton, 0), white),
			VertexFormat(center + glm::vec3(lengthButton, heightButton, 0), white)
		};

		std::vector<unsigned short> indicesButton =
		{
			1, 2, 3,
			2, 1, 3,
			0, 2, 3
		};

		meshes["button"] = new Mesh("button");
		Mesh* button = CreateMesh("button", verticesButton, indicesButton);

		button->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(button);
	}

	{
		float twopi = 4 * acos(0.0);
		int num_points = 150;
		float angle = 0.0f;

		std::vector<VertexFormat> verticesBall;
		std::vector<unsigned short> indicesBall;

		for (int i = 0; i < num_points; i++)
		{
			float angle = twopi * float(i) / float(num_points);

			float x = radiusX * sin(angle);
			float y = radiusY * cos(angle);

			verticesBall.push_back(VertexFormat(center + glm::vec3(x, y, 0), red));
			indicesBall.push_back((unsigned short)i);
		}

		meshes["balloon"] = new Mesh("balloon");
		Mesh* balloon = CreateMesh("balloon", verticesBall, indicesBall);

		balloon->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(balloon);
	}

	{
		float twopi = 4 * acos(0.0);
		int num_points = 150;
		float angle = 0.0f;

		std::vector<VertexFormat> verticesYellowBall;
		std::vector<unsigned short> indicesYellowBall;

		for (int i = 0; i < num_points; i++)
		{
			float angle = twopi * float(i) / float(num_points);

			float x = radiusX * sin(angle);
			float y = radiusY * cos(angle);

			verticesYellowBall.push_back(VertexFormat(center + glm::vec3(x, y, 0), yellow));
			indicesYellowBall.push_back((unsigned short)i);
		}

		meshes["yellowBalloon"] = new Mesh("yellowBalloon");
		Mesh* balloon = CreateMesh("yellowBalloon", verticesYellowBall, indicesYellowBall);

		balloon->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(balloon);
	}

	{
		std::vector<VertexFormat> verticesLine =
		{
			VertexFormat(center, color),
			VertexFormat(center + glm::vec3(-lengthLine, 0, 0), color)
		};

		std::vector<unsigned short> indicesLine = { 0, 1 };

		meshes["line"] = new Mesh("line");
		Mesh* line = CreateMesh("line", verticesLine, indicesLine);

		line->SetDrawMode(GL_LINE_STRIP);
		AddMeshToList(line);
	}

	{
		std::vector<VertexFormat> verticesShuriken;
		std::vector<unsigned short> indicesShuriken;
	}
}


// centerX and centerY represent the coordinates of the balloon's center
// x, y coordinates of the arrow
bool Tema::CollisionBalloonArrow(float centerX, float centerY, float x, float y) {

	if (pow(x - centerX, 2) / pow(radiusX, 2) + pow(y - centerY, 2) / pow(radiusY, 2) < 1)
		return true;

	return false;
}



Mesh* Tema::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));


	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);

	CheckOpenGLError();

	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Tema::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema::Update(float deltaTimeSeconds)
{
	if (lifes > 0) {

		glLineWidth(3);
		glPointSize(5);

		// Render player
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(posPlayerOx, posPlayerOy);
		modelMatrix *= Matrix::Rotate(glm::radians(angularStep));
		RenderMesh2D(meshes["player"], shaders["VertexColor"], modelMatrix);

		// Render Arrow
		modelMatrix = glm::mat3(1);

		if (click == 0) {
			angle = angularStep;
			posAfterClickOx = posPlayerOx;
			posAfterClickOy = posPlayerOy;
			modelMatrix *= Matrix::Translate(posPlayerOx, posPlayerOy);
			modelMatrix *= Matrix::Rotate(glm::radians(angle));
			modelMatrix *= Matrix::Translate(posArrowOx, posArrowOy);
		}
		else {
			modelMatrix *= Matrix::Translate(posAfterClickOx, posAfterClickOy);
			modelMatrix *= Matrix::Translate((posArrowOx)*cos(RADIANS(angle)), (posArrowOx)*sin(RADIANS(angle)));
			modelMatrix *= Matrix::Rotate(glm::radians(angle));
		}

		RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["arrowHead"], shaders["VertexColor"], modelMatrix);


		// first Balloon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(posBalloonOx, posBalloonOy);
		modelMatrix *= Matrix::Scale(scaleFirst, scaleFirst);
		RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);

		// second Balloon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(secondBalloonOx, secondBalloonOy);
		modelMatrix *= Matrix::Scale(scaleSecond, scaleSecond);
		RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);


		//thirdBalloon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(thirdBalloonOx, thirdBalloonOy);
		modelMatrix *= Matrix::Scale(scaleThird, scaleThird);
		RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);


		//forthBalloon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(forthBalloonOx, forthBalloonOy);
		modelMatrix *= Matrix::Scale(scaleForth, scaleForth);
		RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);

		//fifthBalloon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(fifthBalloonOx, fifthBalloonOy);
		modelMatrix *= Matrix::Scale(scaleFifth, scaleFifth);
		RenderMesh2D(meshes["yellowBalloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);

		// sixth
		modelMatrix = glm::mat3(1);
		modelMatrix *= Matrix::Translate(sixthBalloonOx, sixthBalloonOy);
		modelMatrix *= Matrix::Scale(scaleSixth, scaleSixth);
		RenderMesh2D(meshes["yellowBalloon"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);


		angleShuriken += deltaTimeSeconds * 100;
		modelMatrix = glm::mat3(1);

		modelMatrix *= Matrix::Translate(shurikenOx, shurikenOy);
		modelMatrix *= Matrix::Rotate(glm::radians(angleShuriken));
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);

		modelMatrix *= Matrix::Translate(secondShurikenOx, secondShurikenOy);
		modelMatrix *= Matrix::Rotate(glm::radians(angleShuriken));
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);

		modelMatrix *= Matrix::Translate(buttonOx, buttonOy);
		modelMatrix *= Matrix::Scale(scaleButton, 1);
		RenderMesh2D(meshes["button"], shaders["VertexColor"], modelMatrix);

	}
}

void Tema::FrameEnd()
{

}


void Tema::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (posPlayerOy < resolution.y - radius) {
			posPlayerOy += deltaTime * 200;
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (posPlayerOy > radius + 100) {
			posPlayerOy -= deltaTime * 200;
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (speed < 1500 && click == 0) {
			speed += 1000 * deltaTime;
			scaleButton += 150 * deltaTime;
		}
	}
	else {
		scaleButton = 1;
	}


	if (scoreB != score)
		cout << "Score: " << score << endl;

	scoreB = score;

	// Schimbare valori shruriken
	if (shurikenOx > -sideShuriken * 2) {
		shurikenOx -= deltaTime * speedShuriken;
	}
	else {
		shurikenOx = resolution.x + rand() % 200;
		shurikenOy = rand() % (resolution.y - 100) + 100;
	}

	if (secondShurikenOx > -sideShuriken * 2) {
		secondShurikenOx -= deltaTime * (speedShuriken + 50);
	}
	else {
		secondShurikenOx = resolution.x + rand() % 300;
		secondShurikenOy = rand() % (resolution.y - 100) + 100;
	}



	if (click == 1) {
		if (posArrowOx < resolution.x + 300 && posArrowOy < resolution.y + 300 && posArrowOy > -1000 && posArrowOx > -1000) {
			posArrowOx += speed * deltaTime * cos(RADIANS(angle));
			posArrowOy += speed * deltaTime * sin(RADIANS(angle));
		}
		else {
			posArrowOx = 150;
			posArrowOy = 0;
			click = 0;
			speed = 100;
		}
	}

	// first balloon
	if (posBalloonOy < resolution.y + 200) {
		posBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		posBalloonOy = -100 - rand() % 1000;
		posBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// second balloon
	if (secondBalloonOy < resolution.y + 200) {
		secondBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		secondBalloonOy = -100 - rand() % 1000;
		secondBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// third balloon
	if (thirdBalloonOy < resolution.y + 200) {
		thirdBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		thirdBalloonOy = -100 - rand() % 1000;
		thirdBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// forth balloon
	if (forthBalloonOy < resolution.y + 200) {
		forthBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		forthBalloonOy = -100 - rand() % 1000;
		forthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// fifth balloon
	if (fifthBalloonOy < resolution.y + 200) {
		fifthBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		fifthBalloonOy = -100 - rand() % 1000;
		fifthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// sixth balloon
	if (sixthBalloonOy < resolution.y + 200) {
		sixthBalloonOy += deltaTime * (rand() % 200 + baseSpeed);
	}
	else {
		sixthBalloonOy = -100 - rand() % 1000;
		sixthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
	}

	// Detect collisions
	if (click == 1) {
		float x = (posArrowOx)*cos(RADIANS(angle)) + posAfterClickOx;
		float y = (posArrowOx)*sin(RADIANS(angle)) + posAfterClickOy;

		// fist balloon collision
		if (CollisionBalloonArrow(posBalloonOx, posBalloonOy, x, y) == true) {
			collisionFirst = true;
		}
		if (collisionFirst == true) {
			if (scaleFirst > 0)
				scaleFirst -= deltaTime * 5;
			else {
				posBalloonOy = -100 - rand() % 1000;
				posBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleFirst = 1;
				score++;
				collisionFirst = false;
			}
		}

		// second balloon collision
		if (CollisionBalloonArrow(secondBalloonOx, secondBalloonOy, x, y) == true) {
			collisionSecond = true;

		}
		if (collisionSecond == true) {
			if (scaleSecond > 0)
				scaleSecond -= deltaTime * 5;
			else {
				secondBalloonOy = -100 - rand() % 1000;
				secondBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleSecond = 1;
				score++;
				collisionSecond = false;
			}
		}


		// third balloon collision
		if (CollisionBalloonArrow(thirdBalloonOx, thirdBalloonOy, x, y) == true) {
			collisionThird = true;

		}
		if (collisionThird == true) {
			if (scaleThird > 0)
				scaleThird -= deltaTime * 5;
			else {
				thirdBalloonOy = -100 - rand() % 1000;
				thirdBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleThird = 1;
				score++;
				collisionThird = false;
			}
		}

		// forth balloon collision
		if (CollisionBalloonArrow(forthBalloonOx, forthBalloonOy, x, y) == true) {
			collisionForth = true;

		}
		if (collisionForth == true) {
			if (scaleForth > 0)
				scaleForth -= deltaTime * 5;
			else {
				forthBalloonOy = -100 - rand() % 1000;
				forthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleForth = 1;
				score++;
				collisionForth = false;
			}
		}

		// fifthballoon collision
		if (CollisionBalloonArrow(fifthBalloonOx, fifthBalloonOy, x, y) == true) {
			collisionFifth = true;
		}
		if (collisionFifth == true) {
			if (scaleFifth > 0)
				scaleFifth -= deltaTime * 5;
			else {
				fifthBalloonOy = -100 - rand() % 1000;
				fifthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleFifth = 1;
				if (score > 0)
					score--;
				collisionFifth = false;
			}
		}
		// sixth balloon
		if (CollisionBalloonArrow(sixthBalloonOx, sixthBalloonOy, x, y) == true) {
			collisionSixth = true;

		}
		if (collisionSixth == true) {
			if (scaleSixth > 0)
				scaleSixth -= deltaTime * 5;
			else {
				sixthBalloonOy = -100 - rand() % 1000;
				sixthBalloonOx = rand() % (restrictionRight - restrictionLeft) + restrictionLeft;
				scaleSixth = 1;
				if (score > 0)
					score--;
				collisionSixth = false;
			}
		}
	}

	// Collision player - first shuriken
	distancePlayerShuriken = sqrt(pow(posPlayerOx - shurikenOx, 2) + pow(posPlayerOy - shurikenOy, 2));
	if (distancePlayerShuriken < sideShuriken + radius) {
		collisionPlayer = 1;
		shurikenOx = resolution.x + rand() % 200;
		shurikenOy = rand() % (resolution.y - 100) + 100;
	}
	if (collisionPlayer == 1) {
		lifes--;
		collisionPlayer = 0;
	}


	// Collision player - second shuriken
	distancePlayerSecShuriken = sqrt(pow(posPlayerOx - secondShurikenOx, 2) + pow(posPlayerOy - secondShurikenOy, 2));
	if (distancePlayerSecShuriken < sideShuriken + radius) {
		collisionPlayerSec = 1;
	}
	if (collisionPlayerSec == 1) {
		secondShurikenOx = resolution.x + rand() % 200;
		secondShurikenOy = rand() % (resolution.y - 100) + 100;
		lifes--;
		collisionPlayerSec = 0;
	}
}

void Tema::OnKeyPress(int key, int mods)
{

}

void Tema::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	mouseY = resolution.y - mouseY;

	if (mouseX > posPlayerOx) {
		float dot = (posPlayerOx - mouseX) * (posPlayerOx - mouseX);
		float cross = (posPlayerOy - mouseY) * (posPlayerOx - mouseX);

		float alpha = atan2(cross, dot);
		float pi = 2 * acos(0.0);

		angularStep = floor(alpha * 180. / pi + 0.5);
	}
}

void Tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		click = 1;
	}
}

void Tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema::OnWindowResize(int width, int height)
{
}
