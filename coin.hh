#ifndef COIN_HH
#define COIN_HH

#include <vector>
#include <cmath>
#include "geometry.hh"
#include "window.hh"
#include "utils.hh"

class Coin{
    private:
        static const std::vector<std::vector<int> > coin_sprite_;

        pro2::Pt pos_;
        double initial_y;
        bool collected_;

    public:
        Coin(pro2::Pt pos) : pos_(pos), collected_(false), initial_y(pos.y) {}

        void update(int frame_count){
            pos_.y = initial_y + (3* sin(frame_count)*0.0001);
        }

        void collect(){
            collected_ = true;
        }

        void paint_coin(pro2::Window& window) const{
            pro2::paint_sprite(window, pos_, coin_sprite_, false);
        }

        bool is_collected() const{
            return collected_;
        }

        pro2::Rect get_rect() const{
            // {left, top, right, bottom}
            return {pos_.x - 4, pos_.y - 4, pos_.x + 4, pos_.y + 4};
        }
};

#endif
