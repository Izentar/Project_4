#ifndef MAIN_FRAME_CPP
#define MAIN_FRAME_CPP

#include "main_frame.h"

ostream& operator <<(ostream& outgo, const Main_frame& frame)
{
    for (int i=0; i<frame.y; i++)
    {
        outgo << endl;
    }
    for (int i=0; i<frame.height-frame.y; i++)
    {
        for (int j=0; j<frame.x; j++)
        {
            outgo << " ";
        }
        for (int j=0; j<frame.width-frame.x; j++)
        {
            outgo << frame.Board[j][i];
        }
        outgo << endl;
    }
    return outgo;
}

void Main_frame::cast()
{
    if(edges_x!=DEFAULT_CHECK_MAIN_FRAME)
    {
        for(int i=1; i<x-1; i++)
        {
            Board[i][0]=edges_x;
            Board[i][y-1]=edges_x;
        }
    }
    else
    {
        for(int i=1; i<x-1; i++)
        {
            Board[i][0]=DEFAULT_VOID_MAIN_FRAME;
            Board[i][y-1]=DEFAULT_VOID_MAIN_FRAME;
        }
    }


    if(edges_y!=DEFAULT_CHECK_MAIN_FRAME)
    {
        for (int i=1; i<y-1; i++)
        {
            Board[0][i]=edges_y;
            Board[x-1][i]=edges_y;
        }
    }
    else
    {
        for (int i=1; i<y-1; i++)
        {
            Board[0][i]=DEFAULT_VOID_MAIN_FRAME;
            Board[x-1][i]=DEFAULT_VOID_MAIN_FRAME;
        }
    }


    if(corner_ul!=DEFAULT_CHECK_MAIN_FRAME)
    {
        Board[0][0]=corner_ul;
    }
    else
    {
        Board[0][0]=DEFAULT_VOID_MAIN_FRAME;
    }

    if(corner_dl!=DEFAULT_CHECK_MAIN_FRAME)
    {
        Board[0][y-1]=corner_dl;
    }
    else
    {
        Board[0][y-1]=DEFAULT_VOID_MAIN_FRAME;
    }

    if(corner_dr!=DEFAULT_CHECK_MAIN_FRAME)
    {
        Board[x-1][y-1]=corner_dr;
    }
    else
    {
        Board[x-1][y-1]=DEFAULT_VOID_MAIN_FRAME;
    }

    if(corner_ur!=DEFAULT_CHECK_MAIN_FRAME)
    {
        Board[x-1][0]=corner_ur;
    }
    else
    {
        Board[x-1][0]=DEFAULT_VOID_MAIN_FRAME;
    }
}

void Main_frame::Frame::cast()
{
    if(edges_x!=DEFAULT_CHECK_FRAME)
    {
        for (int i=1; i<width-1; i++)
        {
            anchor->Board[i][0]=edges_x;
            anchor->Board[i][height-1]=edges_x;
        }
    }
    else
    {
        for (int i=1; i<width-1; i++)
        {
            anchor->Board[i][0]=DEFAULT_VOID_FRAME;
            anchor->Board[i][height-1]=DEFAULT_VOID_FRAME;
        }
    }

    if(edges_y!=DEFAULT_CHECK_FRAME)
    {
        for (int i=1; i<height-1; i++)
        {
            anchor->Board[0][i]=edges_y;
            anchor->Board[width-1][i]=edges_y;
        }
    }
    else
    {
        for (int i=1; i<height-1; i++)
        {
            anchor->Board[0][i]=DEFAULT_VOID_FRAME;
            anchor->Board[width-1][i]=DEFAULT_VOID_FRAME;
        }
    }

    if(corner_ul!=DEFAULT_CHECK_FRAME)
    {
        anchor->Board[0][0]=corner_ul;
    }
    else
    {
        anchor->Board[0][0]=DEFAULT_VOID_FRAME;
    }
    if(corner_dl!=DEFAULT_CHECK_FRAME)
    {
        anchor->Board[0][height-1]=corner_dl;
    }
    else
    {
        anchor->Board[0][height-1]=DEFAULT_VOID_FRAME;
    }
    if(corner_ur!=DEFAULT_CHECK_FRAME)
    {
        anchor->Board[width-1][0]=corner_ur;
    }
    else
    {
        anchor->Board[width-1][0]=DEFAULT_VOID_FRAME;
    }
    if(corner_dr!=DEFAULT_CHECK_FRAME)
    {
        anchor->Board[width-1][height-1]=corner_dr;
    }
    else
    {
        anchor->Board[width-1][height-1]=DEFAULT_VOID_FRAME;
    }

}

bool Main_frame::check_data(const int& f_width,const int& f_height, const char& f_edges_x, const char& f_edges_y, const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& f_filling, const char& exeption)
{
    if(f_width<=0||f_height<=0)
    {
        return true;
    }
    if((f_edges_x<32&&f_edges_x!=exeption)||(f_edges_y<32&&f_edges_y!=exeption))
    {
        return true;
    }
    if((f_corner_ur<32&&f_corner_ur!=exeption)||(f_corner_dr<32&&f_corner_dr!=exeption))
    {
        return true;
    }
    if((f_corner_ul<32&&f_corner_ul!=exeption)||(f_corner_dl<32&&f_corner_dl!=exeption))
    {
        return true;
    }
    if(f_filling<32&&f_filling!=exeption)
    {
        return true;
    }
    return false;
}

bool Main_frame::Frame::check_data(const int& f_width,const int& f_height, const char& f_edges_x, const char& f_edges_y, const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& f_filling, const char& exeption)
{
    if(f_width<=0||f_height<=0)
    {
        return true;
    }
    if((f_edges_x<32&&f_edges_x!=exeption)||(f_edges_y<32&&f_edges_y!=exeption))
    {
        return true;
    }
    if((f_corner_ur<32&&f_corner_ur!=exeption)||(f_corner_dr<32&&f_corner_dr!=exeption))
    {
        return true;
    }
    if((f_corner_ul<32&&f_corner_ul!=exeption)||(f_corner_dl<32&&f_corner_dl!=exeption))
    {
        return true;
    }
    if(f_filling<32&&f_filling!=exeption)
    {
        return true;
    }
    return false;
}

Main_frame::Main_frame(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x=DEFAULT_CHECK_MAIN_FRAME, const char& filling_edges_y=DEFAULT_CHECK_MAIN_FRAME, const char& filling_corner_ur=DEFAULT_CHECK_MAIN_FRAME, const char& filling_corner_dr=DEFAULT_CHECK_MAIN_FRAME, const char& filling_corner_ul=DEFAULT_CHECK_MAIN_FRAME, const char& filling_corner_dl=DEFAULT_CHECK_MAIN_FRAME, const char& main_filling=DEFAULT_CHECK_MAIN_FRAME)
:x(position_x), y(position_y), width(M_f_width), height(M_f_height), edges_x(filling_edges_x), edges_y(filling_edges_y), corner_ur(filling_corner_ur), corner_dr(filling_corner_dr), corner_ul(filling_corner_ul), corner_dl(filling_corner_dl), filling(main_filling)
{
    Board.resize(M_f_width);
    for (int i=0; i<M_f_width; i++)
    {
        Board[i].resize(M_f_height);
    }

    char tmp=DEFAULT_CHECK_MAIN_FRAME;
    if(check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling, tmp))
    {
        throw 0;
    }
    else
    {
        cast();
    }
}

Main_frame::Frame::Frame(Main_frame& window, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x=DEFAULT_CHECK_FRAME, const char& filling_edges_y=DEFAULT_CHECK_FRAME, const char& filling_corner_ur=DEFAULT_CHECK_FRAME, const char& filling_corner_dr=DEFAULT_CHECK_FRAME, const char& filling_corner_ul=DEFAULT_CHECK_FRAME, const char& filling_corner_dl=DEFAULT_CHECK_FRAME, const char& main_filling=DEFAULT_CHECK_FRAME)
:x(pos_x), y(pos_y), width(F_width), height(F_height), edges_x(filling_edges_x), edges_y(filling_edges_y), corner_ur(filling_corner_ur), corner_dr(filling_corner_dr), corner_ul(filling_corner_ul), corner_dl(filling_corner_dl), filling(main_filling), anchor(&window)
{
    char tmp=DEFAULT_CHECK_FRAME;
    if(check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling, tmp))
    {
        throw 0;
    }
    else
    {
        cast();
    }
}

Main_frame::Frame::~Frame() {}


#endif // MAIN_FRAME_CPP
