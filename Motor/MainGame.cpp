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
	window = SDL_CreateWindow("GAAA", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es validar si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
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
        topRightSprite.draw(); // Dibuja el nuevo sprite
    }
	if (topLeftSpriteShown) {
		topLeftSprite.draw();
	}
	if (bottomRightSpriteShown) {
		bottomRightSprite.draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::run()
{
	init();

	startTime = SDL_GetTicks();
	sprite.init(-1, -1, 1, 1);
	topRightSprite.init(1, 1, -1, -1);

	// Inicializamos los nuevos sprites sin mostrarlos inmediatamente
	topLeftSprite.init(-1, 1, 1, -1); // Ajusta las coordenadas según sea necesario
	bottomRightSprite.init(1, -1, -1, 1); // Ajusta las coordenadas según sea necesario

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

		draw(); // Dibuja la escena
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