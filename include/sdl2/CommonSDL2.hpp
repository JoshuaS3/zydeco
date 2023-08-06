#ifndef SDL2_HPP_
#define SDL2_HPP_


#include <SDL2/SDL.h>

#include "ZydecoCommon.hpp"


#define SDL_CallErrorReturningFunction(FUNC_NAME, PARAMS...) if (FUNC_NAME(PARAMS) < 0) { ZydecoFault(#FUNC_NAME " error: {}", SDL_GetError()); }

#define SDL_CallPointerReturningFunction(FUNC_NAME, NEW_PTR, PARAMS...) NEW_PTR = FUNC_NAME(PARAMS); \
    if (NEW_PTR == nullptr) { ZydecoFault(#FUNC_NAME " error: {}", SDL_GetError()); }


#endif /* SDL2_HPP_ */
