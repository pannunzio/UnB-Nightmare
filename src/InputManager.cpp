#include "InputManager.h"

using std::cout;
using std::endl;

//construtor
InputManager::InputManager() {
    this->quitRequested = false;
    this->updateCounter = 0;
    SDL_GetMouseState(&this->mouseX, &this->mouseY);
    //inicializa o mouse state e update. nao é necessario fazer para os keys por motivos de tabela hash
    for(int i = 0; i < 6; i++){
        mouseState.push_back(false);
        mouseUpdate.emplace_back(0);
    }
}

InputManager::~InputManager() {

}

//chamada uma vez a cada state
void InputManager::Update(){
    SDL_Event event;

    SDL_GetMouseState(&this->mouseX, &this->mouseY);
    this->quitRequested = false;
    this->updateCounter++;

    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            this->quitRequested = true;
        }
        //sequencia de captar momentos de teclado e mouse
        if(event.type == SDL_KEYDOWN){
            //com o key repeat não pode segurar a tecla infinitamente
            //sem o key repeat pode
            //removido para fins de facilitar os testes
            if(event.key.repeat == 0){
                this->keyState[event.key.keysym.sym] = true;
                this->keyUpdate[event.key.keysym.sym] = this->updateCounter;

//                if( event.key.keysym.sym == ESCAPE_KEY ) {
//                    quitRequested = true;
//                }
            }
        }
        if(event.type == SDL_KEYUP){
            this->keyState[event.key.keysym.sym] = false;
            this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            this->mouseState[event.button.button] = true;
            this->mouseUpdate[event.button.button] = this->updateCounter;
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            this->mouseState[event.button.button] = false;
            this->mouseUpdate[event.button.button] = this->updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key){
    return (this->keyState[key] && this->keyUpdate[key] >= this->updateCounter) and !this->KeyRelease(key);
}

bool InputManager::KeyRelease(int key){
    return !this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::IsKeyDown(int key){
    return this->keyState[key];
}

bool InputManager::MousePress(int button){
    return this->mouseState[button] && this->mouseUpdate[button] >= this->updateCounter;
}

bool InputManager::MouseRelease(int button){
    return !this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::IsMouseDown(int button){
    return this->mouseState[button];
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

int InputManager::GetMouseX(){
    return this->mouseX;
}

int InputManager::GetMouseY(){
    return this->mouseY;
}

bool InputManager::QuitRequested(){
    return this->quitRequested;
}
