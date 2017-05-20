#ifndef __ENGINE_SCENE__
#define __ENGINE_SCENE__

#include <string>
#include <unordered_map>

#include "gameobject.hpp"
#include "asset_manager.hpp"

namespace engine {

class Scene {
public:
    enum class State {
        created,
        loaded,
        playing,
        invalid
    };

    Scene() : Scene("", State::invalid) {}
    Scene(std::string name, State _state=State::created)
        : m_name(name), m_state(_state) {}

    virtual ~Scene() {}

    bool add_game_object(GameObject & obj);
    GameObject * get_game_object(const std::string & id);
    bool remove_game_object(const std::string & id);

    virtual bool init();
    virtual bool shutdown();
    virtual bool draw();
    virtual bool update();

    inline AssetManager & asset_manager() { return m_asset_manager; }
    inline std::string name() const { return m_name; }

protected:
    std::string                                 m_name;
    std::unordered_map<std::string, GameObject *> m_objects;
    AssetManager m_asset_manager;
    State m_state;
};

}

#endif
