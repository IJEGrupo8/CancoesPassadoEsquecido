#ifndef __ENGINE_COMPONENTS_ANIMATION__
#define __ENGINE_COMPONENTS_ANIMATION__

#include <string>

#include "components/image.hpp"
#include "timer.hpp"
#include "gameobject.hpp"
namespace engine {
class GameObject;
class AnimationComponent : public ImageComponent {
public:
    AnimationComponent(GameObject & game_object, std::string path,
                        int m_i, int m_j,int _duration,int _start,int _end,int _loop = -1)
        : ImageComponent(game_object,path,m_i,m_j), n_lines(m_i),
            n_cols(m_j), n_frames(_end-_start), duration(_duration),
            start_frame(_start), end_frame(_end),
            animationFrameTime(_duration/_end-_start),loop(_loop),m_loop(_loop) {}

    AnimationComponent() : ImageComponent() {}

    ~AnimationComponent() {}

    bool init();
    bool shutdown();
    void draw();
    bool setup();

	Timer clock;


	int n_lines, n_cols;
	int n_frames;
    int duration;
    int m_current_frame = 0;
    int start_frame, end_frame;
    int animationFrameTime;
    int loop, m_loop;
private:
    void drawFrame();
};

}

#endif
