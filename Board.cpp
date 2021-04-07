#include <cstring>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <exception>
#include "Board.hpp"
#include "Direction.hpp"

using namespace std;
using ariel::Direction;

namespace ariel{
    const uint starting_size = 0;
    const uint max_size = UINT32_MAX;

    Board::Board(){
        this->firstX = max_size;
        this->firstY = max_size;
        this->lastX = starting_size;
        this->lastY = starting_size;

        board = vector<vector<char>>();        
    }

    void Board::post(uint X, uint Y, Direction dir, std::string message){
        uint msgLen = message.length();
        fitSize(X, Y, msgLen, dir);
        if (dir == Direction::Horizontal){
            if (Y + msgLen > max_size){
                msgLen = max_size - Y;
            }
            for (size_t i = 0; i < msgLen; i++){
                board[X][Y+i] = message.at(i);
            }
        }
        else{
            if (X + msgLen > max_size){
                msgLen = max_size - X;
            }
            for (size_t i = 0; i < msgLen; i++){
                board[X+i][Y] = message.at(i);
            }
        }
    }
    string Board::read(uint X, uint Y, Direction dir, uint len){
        string message;
        if (dir == Direction::Horizontal){
            for (size_t i = 0; i < len; i++){
                if (X <= this->lastX && X >= this->firstX && Y+i <= this->lastY && Y >= this->firstY){
                    message += board[X][Y+i];
                }
                else{
                    message += '_';
                }
            }  
        }
        else{
            for (size_t i = 0; i < len; i++){
                if (X+i <= this->lastX && X >= this->firstX && Y <= this->lastY && Y >= this->firstY){
                    message += board[X+i][Y];
                }
                else{
                    message += '_';
                }
                
            }
        }
        return message;
    }
    void Board::show(){
        if(this->lastX == starting_size){
            cout << "\n The board is empty. feel free to add some message\n" << endl;
        }
        else{
            uint XNum = this->firstX;
            uint totalY = (this->lastY) - (this->firstY) + 1;
            uint totalX = (this->lastX) - (this->firstX) + 1;

            for (size_t i = 0; i < totalX; i++){
                cout << XNum << ":" << read(XNum, this->firstY, Direction::Horizontal, totalY);
            }   
        }
    }

    void Board::fitSize(uint X, uint Y, uint len, Direction dir){
        this->firstX = min(X, firstX);
        this->firstY = min(Y, this->firstY);

        if(dir == Direction::Horizontal){
            this->lastY = max(this->lastY, Y+len);
            this->lastX = max(X+1, this->lastX);
        }
        else{
            this->lastX = max(this->lastX, X+len);
            this->lastY = max(Y+1, this->lastY);
        }
        board.resize(this->lastX);
        for (size_t i = 0; i < this->lastX; i++){
            board[i].resize(this->lastY, '_');
        }
    }
}