#include "Menu.h"

Menu::Menu(){
}

Menu::Menu(float posX, float posY, int newLineSpace):bg(BG_MENU){
    //ctor
    this->box.x = posX;
    this->box.y = posY;

    this->newLineSpace = newLineSpace;
    this->currentOption = 0;
    this->lastOption = -1;
    this->selectedOption = -1;
    this->gotInput = false;
}

Menu::~Menu()
{
    //dtor
}

void Menu::Update(float dt){
    HandleInputs();
	// Menu Select
    if(gotInput){
        gotInput = false;
        options[currentOption]->SetColor(TEXT_BLACK);
        buttons[currentOption].Open(BUTTON_SELECTED);
        if(lastOption != -1){
            options[lastOption]->SetColor(TEXT_WHITE);
            buttons[lastOption].Open(BUTTON_NOT_SELECTED);
        }
    }
}

void Menu::HandleInputs(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        selectedOption = currentOption;
	}
	// Menu Input
	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		gotInput = true;
		lastOption = currentOption;
		this->currentOption--;
		//cout << option << endl;
		if(this->currentOption < MENU_MIN_t)
			this->currentOption = options.size() - 1;
	}

	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		gotInput = true;
		lastOption = currentOption;
		this->currentOption++;
		//cout << this->option << endl;
		if(this->currentOption > options.size()-1)
			this->currentOption = MENU_MIN_t;
	}
}

void Menu::Render(){
    this->bg.Render((int)Camera::GetX() + box.x - (this->bg.GetWidth()/2), (int)Camera::GetY() + this->box.y + 50 - (this->bg.GetHeight()/2));

    for(unsigned int i = 0; i < buttons.size(); i++){
        this->buttons[i].Render(box.x - (buttons[i].GetWidth()/2), box.y - BUTTON_OFFSET_Y +(newLineSpace*i));
    }

    for(unsigned int i = 0; i < options.size(); i++){
        this->options[i]->Render(0, 0);
    }
}

bool Menu::IsDead(){
    return false;
}

void Menu::NotifyCollision(GameObject* other){
}

bool Menu::Is(std::string type){
    return MENU_TYPE;
}

int Menu::GetLayer(){
    return 0;
}

int Menu::GetSublayer(){
    return 0;
}
bool Menu::GetSelection(){
    if(selectedOption != -1) return true;
    else return false;
}

int Menu::GetSelectedOption(){
    int selected = selectedOption;
    selectedOption = -1;
    return selected;
}

void Menu::AddMenuOption(string newOpt){
    options.push_back(new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, newOpt, TEXT_WHITE, 0,0 ) );
    options.back()->SetPos(this->box.x,this->box.y + newLineSpace*(options.size()-1),true,false);

    Sprite selectedButton = Sprite(BUTTON_NOT_SELECTED, 1, 1);
    buttons.push_back(selectedButton);

    if(options.size() == 1){
        options[currentOption]->SetColor(TEXT_BLACK);
        buttons[currentOption].Open(BUTTON_SELECTED);
    }
}

void Menu::RemoveMenuOption(int option){
    options.erase(options.begin() + option);
    buttons.erase(buttons.begin() + option);

    for(int i = 0; i < options.size(); i++){
        this->options[i]->SetPos(this->box.x,this->box.y + newLineSpace*i,true,false);
    }
    options[currentOption]->SetColor(TEXT_BLACK);
    buttons[currentOption].Open(BUTTON_SELECTED);
}

void Menu::SetPosition(float posX, float posY, int newLineSpace){
    this->box.x = posX;
    this->box.y = posY;
    this->newLineSpace = newLineSpace;
}

