#ifndef CRUMBLING_HH
#define CRUMBLING_HH

#include "geometry.hh"
#include "window.hh"
#include <vector>
#include <string>

class Crumbling {
 private:
    int left_, right_, top_, bottom_;
    std::string state_;
    int   timer_;

    static const std::vector<std::vector<int>> crumbling_texture_;

    static const int SHAKE_FRAMES   = 60;  // 1.25 sec
    static const int FALL_FRAMES    = 30;  // 0.6 sec
    static const int FALLEN_FRAMES  = 96;  // 2 sec

 public:


    Crumbling(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom),
          state_("normal"), timer_(0) {}


    void update() {
        if (state_ == "shaking") {
            timer_++;
            if (timer_ >= SHAKE_FRAMES) {
                state_ = "falling";
                timer_ = 0;
            }
        } else if (state_ == "falling") {
            timer_++;
            if (timer_ >= FALL_FRAMES) {
                state_ = "fallen";
                timer_ = 0;
            }
        } else if (state_ == "fallen") {
            timer_++;
            if (timer_ >= FALLEN_FRAMES) {
                state_ = "normal";
                timer_ = 0;
            }
        }
    }


    void mario_on_top() {
        if (state_ == "normal") {
            state_ = "shaking";
            timer_ = 0;
        }
    }


    bool is_solid() const {
        return state_ == "normal" || state_ == "shaking";
    }

    std::string state() const {
        return state_;
    }

    pro2::Rect get_rect() const {
        if (state_ == "fallen") return {0, 0, 0, 0};
        return {left_, top_, right_, bottom_};
    }

    bool has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
        if (!is_solid()) return false;
        return (left_ <= plast.x && plast.x <= right_) &&
               (left_ <= pcurr.x && pcurr.x <= right_) &&
               (plast.y <= top_ && pcurr.y >= top_);
    }

    void paint(pro2::Window& window) const;

    int top(){
      return top_;
    }
};

#endif
