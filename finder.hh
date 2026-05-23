#ifndef FINDER_HH
#define FINDER_HH

#include <cmath>  // floor()
#include <map>
#include <set>
#include "geometry.hh"

template <typename T>
class Finder {
 private:
    const int cellSize = 40;
    std::map<std::pair<int, int>, std::set<const T *> > grid;

    void gridRange(const pro2::Rect& element_rect, pro2::Rect& tiles) const {
        tiles.bottom = floor(element_rect.bottom / cellSize);
        tiles.top = floor(element_rect.top / cellSize);
        tiles.left = floor(element_rect.left / cellSize);
        tiles.right = floor(element_rect.right / cellSize);
    }

 public:
    Finder() {}

    // Add one
    void add(const T *t) {
        pro2::Rect tiles;
        gridRange(t->get_rect(), tiles);
        for (int y = tiles.top; y <= tiles.bottom; ++y) {
            for (int x = tiles.left; x <= tiles.right; ++x) {
                grid[{x, y}].insert(t);
            }
        }
    }

    // Remove one
    void remove(const T *t) {
        pro2::Rect tiles;
        gridRange(t->get_rect(), tiles);
        for (int y = tiles.top; y <= tiles.bottom; ++y) {
            for (int x = tiles.left; x <= tiles.right; ++x) {
                auto it = grid.find({x, y});
                if (it != grid.end()) {
                    it->second.erase(t);
                    if (it->second.empty()) {
                        grid.erase(it);
                    }
                }
            }
        }
    }

    void update(const T *t) {
        remove(t);
        add(t);
    }

    /**
     * @brief Retorna el conjunt d'objectes amb rectangles total o
     *        parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el cost
     * de l'algorisme ha de ser O(log n).
     *
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un rectangle
     *          parcial o totalment dins de `rect`
     */
    std::set<const T *> query(pro2::Rect window_rect) const {
        std::set<const T *> result;
        pro2::Rect tiles;
        gridRange(window_rect, tiles);
        for (int y = tiles.top; y <= tiles.bottom; ++y) {
            for (int x = tiles.left; x <= tiles.right; ++x) {
                auto it = grid.find({x,y});
                if (it != grid.end()){
                    for (const auto& p : it->second){
                        result.insert(p);
                    }
                }
            }
        }
        return result;
    }
};

#endif
