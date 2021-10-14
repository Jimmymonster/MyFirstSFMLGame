#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->pause = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->shaking = false;
	this->temp = sf::seconds(0.f);
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}
const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->pause = true;
}

void State::unpauseState()
{
	this->pause = false;
}

void State::shakeScreen()
{
	srand(time(0));
	if (this->temp == sf::seconds(0.f)) {
		this->view = this->saveView = this->window->getView();
		this->temp = this->clock.getElapsedTime();
		cou = 0;
	}
	else if (this->clock.getElapsedTime() - this->temp >= sf::seconds(0.05f)) {
		if(cou%2==0) this->view.move(sf::Vector2f( rand() % 10, rand() % 10));
		else this->view = this->saveView;
		this->temp = this->clock.getElapsedTime();
		cou++;
	}
	if (cou>=4) {
		this->view = this->saveView;
		this->temp = sf::seconds(0.f);
		this->shaking = false;
	}
	this->window->setView(this->view);
}

void State::UpdateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::UpdateKeytime(const float deltaTime)
{
	if (this->keytime < keytimeMax) {
		this->keytime += 50.f * deltaTime;
	}
}
