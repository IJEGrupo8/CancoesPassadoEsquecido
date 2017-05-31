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
    
class Component;

class GameObject {
public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    GameObject() : GameObject("",0,0, State::invalid) {}
    GameObject(std::string _name,int _x,int _y, State _state=State::enabled)
        : w(0), h(0), rotation(0), physics(*this,_x,_y), m_name(_name),xI(_x),yI(_y),
          m_state(_state), i_state(_state){}

    ~GameObject() {}

    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    virtual void setup();


    bool add_component(Component & component);

    inline std::string name()  const { return m_name; }
    inline State       state() const { return m_state; }
    template<typename T>
    T * get_component()
    {
        return dynamic_cast<T *>(m_components[std::type_index(typeid(T))].front());
    }
    void setState(State new_state) { m_state = new_state; }
    inline void set_size(int _w, int _h) { w = _w; h = _h; }
    int getInitialX();
    int getInitialY();
    void resetState(){m_state = i_state;}
    
    int    w, h;
    int    xF,yF;
    double rotation;
    PhysicsComponent physics;

protected:
    std::string m_name;
    int    xI,yI;
    State       m_state;
    State i_state;
    std::unordered_map<std::type_index, std::list<Component *> > m_components;
    
};

}

#endif
