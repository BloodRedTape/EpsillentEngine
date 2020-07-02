#ifndef DISPLAY_SERVER_H
#define DISPLAY_SERVER_H

#include <SFML/Graphics.hpp>
#include "engine/core/typedefs.hpp"
#include <mutex>
typedef sf::RenderWindow RenderWindow;
/*

Used to serve game window and avoid through-objects references to it via
get_display_target()

*/
class Engine;
class Renderer2D;


class DisplayServer{  
    private:
        std::mutex& mutex;
        sf::RenderWindow* mp_display_target;
        static DisplayServer* smp_singleton;

        int draw_calls;

    public:
        DisplayServer(std::mutex&);
        ~DisplayServer();

        DisplayServer& operator=(const DisplayServer&)=delete;
        DisplayServer(const DisplayServer&)=delete;

        _ALWAYS_INLINE_ static DisplayServer* get_singleton(){
            return smp_singleton;
        }
        //void set_display_targer(DisplayTarget& p_dt){get_singleton()->display_target=p_dt;}
        void init_window(sf::VideoMode mode, const char* p_title);
        void set_frame_rate_limit(int fps);
        void clear_display();
        void swap_buffers();

    friend class Renderer2D;
    friend class Engine;

};


#endif