#ifndef __ENGINE_ASSET_MANAGER__
#define __ENGINE_ASSET_MANAGER__

#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include "sdl2include.h"

namespace engine {
struct Image {
		SDL_Texture * texture;
		unsigned int w, h;
};

class AssetManager {
	public:
		AssetManager(std::string base_path="assets/"):m_base_path(base_path) {}

		bool shutdown();
		Image * load_image(std::string path, bool use_base=true);
		TTF_Font *  load_font(std::string path, int size, bool use_base=true);
    	Mix_Music * load_music(std::string path, bool use_base=true);
    	Mix_Chunk * load_sound(std::string path, bool use_base=true);

	private:
		std::string m_base_path;
		std::unordered_map<std::string, Image *> m_images;
		std::map<std::pair<std::string, int>, TTF_Font * > m_fonts;
    	std::unordered_map<std::string, Mix_Music *> m_musics;
    	std::unordered_map<std::string, Mix_Chunk *> m_sounds;
};
}

#endif
