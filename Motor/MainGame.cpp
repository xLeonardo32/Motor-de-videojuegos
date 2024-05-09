#include "MainGame.h"

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor WD2M", width, height, 0);
	initShaders();
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();


}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.002;
	sprite.draw();
	if (topRightSpriteShown) {
		topRightSprite.draw();
	}
	if (topLeftSpriteShown) {
		topLeftSprite.draw();
	}
	if (bottomRightSpriteShown) {
		bottomRightSprite.draw();
	}
	program.unuse();
	window->swapWindow();
}

void MainGame::run()
{
	init();

	startTime = SDL_GetTicks();
	sprite.init(-1, -1, 1, 1, "Images/mario.png");
	topRightSprite.init(1, 1, -1, -1, "Images/red.png");

	// Inicializamos los nuevos sprites sin mostrarlos inmediatamente
	topLeftSprite.init(-1, 1, 1, -1, "Images/link.png"); // Ajusta las coordenadas según sea necesario
	bottomRightSprite.init(1, -1, -1, 1, "Images/pikachu.png"); // Ajusta las coordenadas según sea necesario
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;
		// Muestra el sprite superior derecho después de 5 segundos
		if (!topRightSpriteShown && elapsedTime >= 5000) {
			topRightSpriteShown = true;
		}

		// Muestra el sprite superior izquierdo después de 10 segundos
		if (!topLeftSpriteShown && elapsedTime >= 10000) {
			topLeftSpriteShown = true;
		}

		// Muestra el sprite inferior derecho después de 15 segundos
		if (!bottomRightSpriteShown && elapsedTime >= 15000) {
			bottomRightSpriteShown = true;
		}

		draw();
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		/*case SDL_MOUSEMOTION:
			cout << " Posición en X " << event.motion.x <<
				" Posición en Y" << event.motion.y << endl;
				
			break;*/
			
		}
	}
}

MainGame::~MainGame()
{
}