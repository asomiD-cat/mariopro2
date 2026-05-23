#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "finder.hh"
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"

class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    int                   score_;
    std::vector<Coin>     coins_;
    Finder<Platform>      platform_finder_;
    Finder<Coin>          coin_finder_;

    bool finished_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif
