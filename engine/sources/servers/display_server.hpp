#ifndef DISPLAY_SERVER_H
#define DISPLAY_SERVER_H

#include <SFML/Graphics.hpp>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include <mutex>
typedef sf::RenderWindow RenderWindow;
/*

Used to serve game window and avoid through-objects references to it via
get_display_target()

*/
class Engine;

class ENGINE_API DisplayServer{
private:
    static std::mutex *p_sync_mutex;
    static sf::RenderWindow* mp_display_target;

    friend class Engine;
public:
    DisplayServer() = default;
    ~DisplayServer() = default;

    DisplayServer& operator=(const DisplayServer&)=delete;
    DisplayServer(const DisplayServer&)=delete;

    //void set_display_targer(DisplayTarget& p_dt){get_singleton()->display_target=p_dt;}
    static void initialize(std::mutex *sync_mutex,sf::VideoMode mode, const char* p_title, uint32 style);
    static void finalize();
    static sf::Vector2i window_size();
    static void set_frame_rate_limit(int fps);
    static void clear_display();
    static void swap_buffers();

};


#endif