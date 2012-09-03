#include <SDL/SDL_ttf.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8

enum textquality {solid, shaded, blended};

// Loads a font, nothing fancy.
// Put sensible error handling code in. If you pass the NULL in later on,
// SDL_ttf dies pretty horribly.
TTF_Font* loadfont(char* file, int ptsize)
{
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL) {
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		// Handle the error here.
	}
	return tmpfont;
}

// SDL_ttf has a few modes you can draw with, check its documentation.
SDL_Surface *drawtext(TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA, 
		char bgR, char bgG, char bgB, char bgA, char text[], enum textquality quality)
{
	SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
	SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
	SDL_Surface* resulting_text;

	if (quality == solid) {
		resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
	}
	else if (quality == shaded) {
		resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
	}
	else if (quality == blended) {
		resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
	}

	return resulting_text;
}


int main(int argc, char** argv) {
	// Must call initialise first.
	TTF_Init();

	// This loads courier, but any font will do.
	TTF_Font* font = loadfont("DejaVuSans.ttf", 20);
	SDL_Surface* surface = drawtext(font, 255, 255, 255, 70, 0, 0, 0, 0, "test", blended);

	// End of SDL_ttf stuff, this is just SDL to display the text we made.
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);
	SDL_BlitSurface(surface, NULL, screen, NULL);
	SDL_Flip(screen);
	SDL_Delay(1000);
	return 0;
}
