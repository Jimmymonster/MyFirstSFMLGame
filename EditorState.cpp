#include "EditorState.h"

void EditorState::initVariable()
{
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/angsana.ttc")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstateKeybinds.ini.txt");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void EditorState::initButtons()
{

}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initVariable();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initBackground();
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

//functions

void EditorState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->endState();
	}
}

void EditorState::UpdateBTN()
{
	//Update BTN and handle their function
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosView);
	}
}

void EditorState::Update(const float& deltaTime)
{
	this->UpdateMousePositions();
	this->UpdateInput(deltaTime);

	this->UpdateBTN();
}

void EditorState::RenderBTN(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}

void EditorState::Render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	this->RenderBTN(*target);

	//temporary check for mouse position
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x+10,this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}
