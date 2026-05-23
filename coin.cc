#include <vector>
#include "window.hh"
#include "coin.hh"

const int b = pro2::black;
const int m = 0x5c4033;
const int y = pro2::yellow;
const int _ = 0x5c94fc;

const std::vector<std::vector<int> > Coin::coin_sprite_ = {
    {_, _, b, b, b, b, _, _},
    {_, b, y, y, y, y, b, _},
    {b, y, y, b, m, y, y, b},
    {b, y, y, b, m, y, y, b},
    {b, y, y, b, m, y, y, b},
    {b, y, y, b, m, y, y, b},
    {_, b, y, y, y, y, b, _},
	{_, _, b, b, b, b, _, _},
};
