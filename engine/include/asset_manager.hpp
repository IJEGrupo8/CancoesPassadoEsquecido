#ifndef __ENGINE_ASSET_MANAGER__
#define __ENGINE_ASSET_MANAGER__

#include <unordered_map>
#include <string>
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
	private:
		std::string m_base_path;
		std::unordered_map<std::string, Image *> m_images;	
};
}

#endif
