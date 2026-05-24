#include "crumbling.hh"
#include <vector>
using namespace std;


const int _ = 0;           // transparent
const int r = pro2::red;
const int y = pro2::yellow;
const int w = pro2::white;

const vector<vector<int>> Crumbling::crumbling_texture_ = {
    {w, w, w, w, w, w, _},
    {w, y, y, w, y, y, _},
    {y, y, r, y, y, r, _},
    {_, _, _, _, _, _, _},
    {w, w, _, w, w, w, _},
    {y, y, y, _, y, y, y},
    {y, r, y, y, _, r, y},
    {_, _, _, _, _, _, _},
};
// clang-format on

void Crumbling::paint(pro2::Window& window) const {
    if (state_ == "fallen") return;

    const int txH = static_cast<int>(crumbling_texture_.size());
    const int txW = static_cast<int>(crumbling_texture_[0].size());

    // shaking: wobble left/right using timer
    int offset_x = 0;
    if (state_ == "shaking") {
        offset_x = (timer_ % 4 < 2) ? 1 : -1;
    }

    // falling: platform drops down progressively
    int offset_y = 0;
    if (state_ == "falling") {
        offset_y = timer_ * 4;  // 4px per frame downward
    }

    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            int color = crumbling_texture_[(i - top_ - 1) % txH][(j - left_) % txW];
            if (color != 0) {
                window.set_pixel({j + offset_x, i + offset_y}, color);
            }
        }
    }
}
