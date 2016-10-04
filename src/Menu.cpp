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
        options[currentOption]->SetColor(TEXT_WHITE);
        options[currentOption]->SetStyle(SHADED);
        if(lastOption != -1){
            options[lastOption]->SetColor(TEXT_BLACK);
            options[lastOption]->SetStyle(BLENDED);
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
    this->bg.Render((int)Camera::pos.x + box.x, (int)Camera::pos.y + this->box.y);
    for(int i = 0; i < options.size(); i++){
        this->options[i]->Render(0, 0);
    }
}

bool Menu::IsDead(){
}

void Menu::NotifyCollision(GameObject* other){
}

bool Menu::Is(std::string type){
}

int Menu::GetLayer(){
}

int Menu::GetSublayer(){
}

int Menu::GetSelectedOption(){
    return selectedOption;
}

void Menu::AddMenuOption(string newOpt){
    options.push_back(new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, newOpt, TEXT_BLACK, 0,0 ) );
    options.back()->SetPos(this->box.x,this->box.y + newLineSpace*(options.size()-1),true,false);
    if(options.size() == 1){
        options[currentOption]->SetColor(TEXT_WHITE);
        options[currentOption]->SetStyle(SHADED);
    }
}

