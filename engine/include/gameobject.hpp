#ifndef __ENGINE_GAME_OBJECT__
#define __ENGINE_GAME_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "vector.hpp"
#include "components/component.hpp"
#include "physics.hpp"


namespace engine {

class GameObject {
public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    GameObject() : GameObject("",0,0, State::invalid) {}
    GameObject(std::string _name,int _x,int _y, State _state=State::enabled)
        : w(0), h(0), rotation(0), m_name(_name), physics(*this,_x,_y),
          m_state(_state) {}

    ~GameObject() {}

    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();


    bool add_component(Component & component);

    inline std::string name()  const { return m_name; }
    inline State       state() const { return m_state; }

    void setState(State state) { m_state = state; }
    inline void set_size(int _w, int _h) { w = _w; h = _h; }
    
    PhysicsComponent physics;

    int    w, h;
    int    xF,yF;
    double rotation;

protected:
    std::string m_name;
    State       m_state;
    std::unordered_map<std::type_index, std::list<Component *> > m_components;
    
};

}

#endif
