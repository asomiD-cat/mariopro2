#include "game.hh"
#include "assert.hh"
#include "coin.hh"
#include "crumbling.hh"
#include "geometry.hh"
#include "platform.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false),
      score_(1) {
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < 20; i++) {
        if (i % 3 == 0) {
            crumbling_platforms_.push_back(Crumbling(250 + i*200, 400 + i*200, 150, 161));
        } else {
            platforms_.push_back(Platform(250 + i*200, 400 + i*200, 150, 161));
        }
        coins_.push_back(Coin({250 + i * 200, 140}));
        coins_.push_back(Coin({250 + i * 200 - 60, 140}));
        coins_.push_back(Coin({250 + i * 200 + 60, 140}));
    }
    for (const auto& p : platforms_)          platform_finder_.add(&p);
    for (const auto& cp : crumbling_platforms_) crumbling_finder_.add(&cp);
    for (const auto& c : coins_)              coin_finder_.add(&c);
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    std::vector<Platform> nearby;
    Rect aux = mario_.get_rect();
    aux.left -= 480; aux.right += 480;
    aux.top -= 480; aux.bottom += 480;

    for (const Platform* p : platform_finder_.query(aux))
        nearby.push_back(*p);

    for (Crumbling& cp : crumbling_platforms_) {
        if (cp.is_solid())
            nearby.push_back(Platform(cp.get_rect().left, cp.get_rect().right,
                                      cp.top(), cp.top() + 11));
    }

    mario_.update(window, nearby);

    Rect mariorect = mario_.get_rect();
    for (Crumbling& cp : crumbling_platforms_) {
        if (mario_.is_grounded() && overlaps(mariorect, cp.get_rect()))
            cp.mario_on_top();
        cp.update();
    }

    Rect visible = window.camera_rect();
    for (Coin& c : coins_) {
        if (!c.is_collected() && overlaps(c.get_rect(), visible)) {
            c.update(window.frame_count());
            if (overlaps(c.get_rect(), mariorect)) {
                c.collect();
                coin_finder_.remove(&c);
                std::cout << "You have " << score_++ << " coins.\n";
            }
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();
    const int left   = cam.x - window.width()  / 4;
    const int right  = cam.x + window.width()  / 4;
    const int top    = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;
    int dx = 0, dy = 0;
    if (pos.x > right)       dx = pos.x - right;
    else if (pos.x < left)   dx = pos.x - left;
    if (pos.y < top)         dy = pos.y - top;
    else if (pos.y > bottom) dy = pos.y - bottom;
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    Rect visible = window.camera_rect();
    for (const Platform* p : platform_finder_.query(visible))
        p->paint(window);
    for (const Crumbling* cp : crumbling_finder_.query(visible))
        cp->paint(window);
    for (const Coin* c : coin_finder_.query(visible))
        c->paint_coin(window);
    mario_.paint(window);
}
