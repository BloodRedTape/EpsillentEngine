#ifndef DISPLAY_SERVER_H
#define DISPLAY_SERVER_H

#include <SFML/Graphics.hpp>


typedef sf::RenderWindow RenderWindow;
/*

Used to serve game window and avoid through-objects references to it via
get_display_target()

*/
class DisplayServer{  
    private:
        sf::RenderWindow* mp_display_target;
        static DisplayServer* smp_singleton;



    public:
        DisplayServer();
        ~DisplayServer();

        DisplayServer& operator=(const DisplayServer&)=delete;
        DisplayServer(const DisplayServer&)=delete;

        static DisplayServer* get_singleton(){return smp_singleton;}
        RenderWindow& get_display_target();
        //void set_display_targer(DisplayTarget& p_dt){get_singleton()->display_target=p_dt;}
        RenderWindow& init_window();



};


#endif