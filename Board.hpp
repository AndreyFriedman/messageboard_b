#pragma once
#include <string>
#include "Direction.hpp"
using namespace std;

namespace ariel {
    typedef unsigned int uint;

    class Board{
        private:
        vector<vector<char>> board;
        void fitSize(uint x, uint y, uint len, Direction dir);
        uint firstX;
        uint firstY;
        uint lastX;
        uint lastY;

        public:
        Board();
        void post(uint x, uint y, Direction dir, string msg);
        string read(uint x, uint y, Direction dir, uint len);
        void show();
    };
}