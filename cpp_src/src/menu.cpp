#include <SDL2/SDL.h>
#include <functional>

class Button {
public:
    Button(int x, int y, int w, int h, SDL_Renderer* renderer)
        : rect{x, y, w, h}, clickedCallback(nullptr) {
        // Load button texture
    }

    void handleEvent(SDL_Event* event) {
        if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
            int x, y;
            Uint32 buttons;
            SDL_GetMouseState(&x, &y);
            if (rect.x <= x && x <= rect.x + rect.w && rect.y <= y && y <= rect.y + rect.h) {
                if (clickedCallback) {
                    clickedCallback();
                }
            }
        }
    }

    void render(SDL_Renderer* renderer) {
        // Render button texture
    }

    void setClickedCallback(std::function<void()> callback) {
        clickedCallback = callback;
    }

private:
    SDL_Rect rect;
    std::function<void()> clickedCallback;
};
