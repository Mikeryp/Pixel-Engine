#pragma once



// This headers contain some of the functions which are not provided
// by the C++ standard library. (such as toRadians)

#define PX_toRadians(degrees) ((degrees) * PX_PI / 180)
#define PX_toDegrees(radians) ((radians) * 180 / PX_PI)
#define PX_Square(x) ((x) * (x)) 


// Constants
#define PX_PI (3.14159265359)
#define PX_E (2.7182818284590452353602874713527) // Eulers constant. link:- https://www.google.co.in/url?sa=t&rct=j&q=&esrc=s&source=web&cd=11&cad=rja&uact=8&ved=0ahUKEwi5_IyAwNfXAhXMLY8KHaQqCwEQFghWMAo&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FE_(mathematical_constant)&usg=AOvVaw2FKjVgs9TIedkOjacq64DS
#define PX_K (2.6854520010) //Khinchin's constant link:- https://en.wikipedia.org/wiki/Khinchin%27s_constant
#define PX_GOLDEN_RATIO (1.6180339887498948482) // link:- https://en.wikipedia.org/wiki/Golden_ratio

// Physics constants
#define PX_C 299792458	 // Speed of light
#define PX_g 9.80667 // Acceleration due to gravity
#define PX_PLANCK_CONSTANT 0.00000000000000626