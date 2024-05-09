#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera2D
{
private:
	glm::vec2 position;
	float scale;
	int screenWidth;
	int screeenHeight;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
	bool needsUpdateMatrix;
public:
	Camera2D();
	~Camera2D();
	void update();
	void init(int screenWidth, int screenHeight);
	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		needsUpdateMatrix = true;
	}

	void setScale(float newScale) {
		scale = newScale;
		needsUpdateMatrix = true;
	}

	glm::mat4 getCameraMatrix() {
		return cameraMatrix;
	}
};

