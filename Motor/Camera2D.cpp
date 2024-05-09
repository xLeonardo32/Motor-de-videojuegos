#include "Camera2D.h"

Camera2D::Camera2D() : scale(1.0f), screenWidth(500),
	screeenHeight(500), cameraMatrix(1.0f)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::update()
{
	if (needsUpdateMatrix) {
		glm::vec3 translate(-position.x, -position.y, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);
		glm::vec3 newScale(scale, scale, 0.0f);
		needsUpdateMatrix = false;
	}
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screeenHeight = screeenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth,
		0.0f, (float)screenHeight);
}
