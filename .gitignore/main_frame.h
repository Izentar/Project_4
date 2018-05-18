#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <iostream>
#include <deque>
#include <list>

using namespace std;

class Main_frame
{
    int  x, y, width, height;
    char edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling;
    deque <deque <char>> Board;

    bool check_data(const int& ,const int& , const char& , const char& , const char& , const char& , const char& , const char& , const char&, const char&);

public:
    static const char DEFAULT_CHECK_MAIN_FRAME=3;
    static const char DEFAULT_VOID_MAIN_FRAME=' ';

    Main_frame(const int&, const int&, const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);
    ~Main_frame();

    void cast();

    friend ostream& operator <<(ostream& outgo, const Main_frame& frame);



    friend class Frame;

    class Frame
    {
        int x, y, width, height;
        char edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling;
        Main_frame *anchor;
        list<Frame*> children;

        bool check_data(const int&,const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);

    public:
        static const char DEFAULT_CHECK_FRAME=3;
        static const char DEFAULT_VOID_FRAME=' ';

        Frame(Main_frame&, const int&, const int&, const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);
        ~Frame();

        void cast();
        bool move();
        bool change_size();

    };

};






#endif // MAIN_FRAME_H
