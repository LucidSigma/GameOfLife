#include "Game.h"

#include "Colours.h"

Game::Game()
{
	if (!Initialise())
	{
		throw std::runtime_error("Game could not be created.");
	}
}

Game::~Game() noexcept
{
	SDL_Quit();
}

void Game::Play()
{
	while (m_isRunning)
	{
		PollEvents();
		Update();
		Draw();
	}
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialise SDL: %s", SDL_GetError());

		return false;
	}

	try
	{
		SDL_Rect windowPosition { 100, 100, s_WindowWidth, s_WindowHeight };

		m_window = Window("Game of Life", windowPosition);
		m_renderer = Renderer(m_window.GetPointer(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	m_isRunning = true;

	return true;
}

void Game::PollEvents()
{
	SDL_Event gameEvent;

	while (SDL_PollEvent(&gameEvent))
	{
		switch (gameEvent.type)
		{
		case SDL_KEYDOWN:
			if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				m_isRunning = false;
			}

			break;

		case SDL_QUIT:
			m_isRunning = false;

			break;

		default:
			break;
		}
	}
}

void Game::Update()
{
	static constexpr float MillisecondsPerSecond = 1000.0f;

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + MillisecondsPerSecond / s_FrameRate))
	{
		#define pass
		pass;
	}

	static constexpr float Epsilon = 0.05f;
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / MillisecondsPerSecond;

	if (deltaTime > Epsilon)
	{
		deltaTime = Epsilon;
	}

	m_ticksCount = SDL_GetTicks();

	m_cellGrid.IterateCells();
}

void Game::Draw()
{
	m_renderer.Clear(Colours::Blue);

	m_cellGrid.Draw(m_renderer, s_WindowWidth, s_WindowHeight);

	m_renderer.Draw();
}