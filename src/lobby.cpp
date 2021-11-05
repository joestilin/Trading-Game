#include "lobby.h"

Lobby::Lobby() { }

void Lobby::Run(Controller &controller, Renderer &renderer, std::size_t &target_frame_duration) {

     // timing
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    while (running && !chose) {
        frame_start = SDL_GetTicks();

        controller.HandleLobbyInput(running, chose);
        
        Update();

        renderer.RenderLobby();
        
        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;

        // calculate frames per second
        if (frame_end - title_timestamp > 1000) {
            renderer.UpdateWindow_Title(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // throttle the loop to target frame rate
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }

}

void Lobby::Update() {

}

bool Lobby::getState() {
    return running;
}

