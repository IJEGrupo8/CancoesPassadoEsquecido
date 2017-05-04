#ifndef __ENGINE_COMPONENTS_COMPONENT__
#define __ENGINE_COMPONENTS_COMPONENT__

namespace engine {

class GameObject;

class Component {
public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    Component() : m_game_object(NULL), m_state(State::invalid) {}
    Component(GameObject & game_object)
        : m_game_object(&game_object), m_state(State::enabled) {}

    virtual ~Component() {}

    virtual bool init() { return true; }
    virtual bool shutdown() { return true; }

    inline State state() { return m_state; }

protected:
    GameObject * m_game_object;
    State        m_state;
};

}

#endif
