#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__

#include "sdl2include.h"
namespace engine{

class Input{
    public:
        enum keys{
            A = SDL_SCANCODE_A,
            B = SDL_SCANCODE_B,
            C = SDL_SCANCODE_C,
            D = SDL_SCANCODE_D,
            E = SDL_SCANCODE_E,
            F = SDL_SCANCODE_F,
            G = SDL_SCANCODE_G,
            H = SDL_SCANCODE_H,
            I = SDL_SCANCODE_I,
            J = SDL_SCANCODE_J,
            K = SDL_SCANCODE_K,
            L = SDL_SCANCODE_L,
            M = SDL_SCANCODE_M,
            N = SDL_SCANCODE_N,
            O = SDL_SCANCODE_O,
            P = SDL_SCANCODE_P,
            Q = SDL_SCANCODE_Q,
            R = SDL_SCANCODE_R,
            S = SDL_SCANCODE_S,
            T = SDL_SCANCODE_T,
            U = SDL_SCANCODE_U,
            V = SDL_SCANCODE_V,
            W = SDL_SCANCODE_W,
            X = SDL_SCANCODE_X,
            Y = SDL_SCANCODE_Y,
            Z = SDL_SCANCODE_Z,
            UP = SDL_SCANCODE_UP,
            DOWN = SDL_SCANCODE_DOWN,
            LEFT = SDL_SCANCODE_LEFT,
            RIGHT = SDL_SCANCODE_RIGHT,
        };
        static bool keyPressed(int key){
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            return currentKeyStates[key];
        }
        
    };
}
#endif
