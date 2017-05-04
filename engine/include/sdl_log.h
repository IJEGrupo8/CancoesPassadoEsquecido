#ifndef SDL_LOG_MACROS_H
#define SDL_LOG_MACROS_H

#include <iostream>
#include <cstdlib>


#ifndef NSDL_ERROR
#   define SDL_ERROR(...)                                                     \
        std::cout << "[SDL ERROR] [" << SDL_GetError() << "] :: " <<          \
                     __VA_ARGS__ << std::endl;
#else
#   define SDL_ERROR(...)
#endif



#ifndef NSDL_IMG_ERROR
#   define SDL_IMG_ERROR(...)                                                 \
        std::cout << "[IMG ERROR] [" << IMG_GetError() << "] :: " <<          \
                     __VA_ARGS__ << std::endl;
#else
#   define SDL_IMG_ERROR(...)
#endif



#ifndef NSDL_TTF_ERROR
#   define SDL_TTF_ERROR(...)                                                 \
        std::cout << "[TTF ERROR] [" << TTF_GetError() << "] :: " <<          \
                     __VA_ARGS__ << std::endl;
#else
#   define SDL_TTF_ERROR(...)
#endif



#ifndef NSDL_MIX_ERROR
#   define SDL_MIX_ERROR(...)                                                 \
        std::cout << "[MIX ERROR] [" << Mix_GetError() << "] :: " <<          \
                     __VA_ARGS__ << std::endl;
#else
#   define SDL_MIX_ERROR(...)
#endif


#endif
