#ifndef MAIN_FRAME_CPP
#define MAIN_FRAME_CPP

#include "main_frame.h"

const char Frame_properties::DEFAULT_CHECK;
const char Frame_properties::DEFAULT_VOID;
const char Frame_properties::DEFAULT_AREA;
const char Frame_properties::DEFAULT_BORDER;

ostream& operator <<(ostream& outgo, const Main_frame& frame)
{
    for (int i=0; i<frame.y; i++)
    {
        outgo << endl;
    }
    for (int i=0; i<frame.height; i++)
    {
        for (int j=0; j<frame.x; j++)
        {
            outgo << Frame_properties::DEFAULT_AREA;
        }
        for (int j=0; j<frame.width; j++)
        {
            outgo << frame.Board[j][i];
        }
        outgo << endl;
    }
    return outgo;
}

Main_frame::Frame::Array Main_frame::Frame::operator[] (const int& val)
{
    Main_frame *tmp=this->anchor;
    auto tmp_char=(tmp->Board.begin()+val+x)->begin();
    return Array(tmp_char, y);
}

Main_frame::Frame::Array::Array(deque<char>::iterator val, const int& pos_y)
:tmp(val), y(pos_y) {}

char& Main_frame::Frame::Array::operator[] (const int& val)
{

    return *(this->tmp+val+y);
}

void Main_frame::cast()
{
    if(edges_x!=DEFAULT_CHECK)
    {
        for(int i=1; i<width-1; i++)
        {
            Board[i][0]=edges_x;
            Board[i][height-1]=edges_x;
        }
    }
    else
    {
        for(int i=1; i<width-1; i++)
        {
            Board[i][0]=DEFAULT_VOID;
            Board[i][height-1]=DEFAULT_VOID;
        }
    }


    if(edges_y!=DEFAULT_CHECK)
    {
        for (int i=1; i<height-1; i++)
        {
            Board[0][i]=edges_y;
            Board[width-1][i]=edges_y;
        }
    }
    else
    {
        for (int i=1; i<height-1; i++)
        {
            Board[0][i]=DEFAULT_VOID;
            Board[width-1][i]=DEFAULT_VOID;
        }
    }


    if(corner_ul!=DEFAULT_CHECK)
    {
        Board[0][0]=corner_ul;
    }
    else
    {
        Board[0][0]=DEFAULT_VOID;
    }

    if(corner_dl!=DEFAULT_CHECK)
    {
        Board[0][height-1]=corner_dl;
    }
    else
    {
        Board[0][height-1]=DEFAULT_VOID;
    }

    if(corner_dr!=DEFAULT_CHECK)
    {
        Board[width-1][height-1]=corner_dr;
    }
    else
    {
        Board[width-1][height-1]=DEFAULT_VOID;
    }

    if(corner_ur!=DEFAULT_CHECK)
    {
        Board[width-1][0]=corner_ur;
    }
    else
    {
        Board[width-1][0]=DEFAULT_VOID;
    }
}

void Main_frame::Frame::cast()
{
    if(edges_x!=DEFAULT_CHECK)
    {
        for (int i=x+1; i<x+width-1; i++)
        {
            anchor->Board[i][y]=edges_x;
            anchor->Board[i][y+height-1]=edges_x;
        }
    }
    else
    {
        for (int i=x+1; i<x+width-1; i++)
        {
            anchor->Board[i][y]=DEFAULT_VOID;
            anchor->Board[i][y+height-1]=DEFAULT_VOID;
        }
    }

    if(edges_y!=DEFAULT_CHECK)
    {
        for (int i=y+1; i<y+height-1; i++)
        {
            anchor->Board[x][i]=edges_y;
            anchor->Board[x+width-1][i]=edges_y;
        }
    }
    else
    {
        for (int i=y+1; i<y+height-1; i++)
        {
            anchor->Board[x][i]=DEFAULT_VOID;
            anchor->Board[x+width-1][i]=DEFAULT_VOID;
        }
    }

    if(corner_ul!=DEFAULT_CHECK)
    {
        anchor->Board[x][y]=corner_ul;
    }
    else
    {
        anchor->Board[x][y]=DEFAULT_VOID;
    }
    if(corner_dl!=DEFAULT_CHECK)
    {
        anchor->Board[x][y+height-1]=corner_dl;
    }
    else
    {
        anchor->Board[x][y+height-1]=DEFAULT_VOID;
    }
    if(corner_ur!=DEFAULT_CHECK)
    {
        anchor->Board[x+width-1][y]=corner_ur;
    }
    else
    {
        anchor->Board[x+width-1][y]=DEFAULT_VOID;
    }
    if(corner_dr!=DEFAULT_CHECK)
    {
        anchor->Board[x+width-1][y+height-1]=corner_dr;
    }
    else
    {
        anchor->Board[x+width-1][y+height-1]=DEFAULT_VOID;
    }

}

bool Frame_properties::check_data \
(const int& f_width, const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& exeption)
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
    return false;
}

bool Main_frame::Frame::check_data(const int& f_width, const int& f_height)
{
    if(this->father==nullptr)
    {
        Main_frame *tmp=this->anchor;
        if((tmp->width<x+width)||(tmp->height<y+height))
        {
            return true;
        }
    }
    else
    {
        if((x+f_width>father->x+father->width)||(y+f_height>father->y+father->height))
        {
            return true;
        }
    }

    return false;
}

bool Main_frame::Frame::check_data(const int& new_x, const int& new_y, const int& f_width, const int& f_height)
{
    if(father==nullptr)
    {
        return check_data(f_width, f_height);
    }

    if((new_x<father->x)||(new_y<father->y))
    {
        return true;
    }
    if((new_x+f_width>father->x+father->width)||(new_y+f_height>father->y+father->height))
    {
        return true;
    }
    return check_data(f_width, f_height);
}

bool Main_frame::check_data \
(const int& f_width,const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& f_filling, const char& exeption)
{
    if(f_filling<32&&f_filling!=exeption)
    {
        return true;
    }
    return Frame_properties::check_data(f_width, f_height, f_edges_x, f_edges_y, f_corner_ur, f_corner_dr, f_corner_ul, f_corner_dl, exeption);
}

//constructor
// checking DEFAULT_CHECK only
Frame_properties::Frame_properties \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, \
const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, \
const char& filling_corner_dl)
:x(position_x), y(position_y), width(M_f_width), height(M_f_height), edges_x(filling_edges_x==DEFAULT_CHECK ? DEFAULT_BORDER : filling_edges_x), \
edges_y(filling_edges_y==DEFAULT_CHECK ? DEFAULT_BORDER : filling_edges_y), corner_ur(filling_corner_ur==DEFAULT_CHECK ? DEFAULT_BORDER : filling_corner_ur), \
corner_dr(filling_corner_dr==DEFAULT_CHECK ? DEFAULT_BORDER : filling_corner_dr), corner_ul(filling_corner_ul==DEFAULT_CHECK ? \
DEFAULT_BORDER : filling_corner_ul), corner_dl(filling_corner_dl==DEFAULT_CHECK ? DEFAULT_BORDER : filling_corner_dl) {}

Frame_properties::~Frame_properties() {};

//constructor
Main_frame::Main_frame \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, \
const char&filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl, \
const char& main_filling)
:Frame_properties(position_x, position_y, M_f_width, M_f_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, \
filling_corner_ul, filling_corner_dl), filling(main_filling==DEFAULT_CHECK ? DEFAULT_VOID : main_filling)
{
    char tmp=DEFAULT_VOID;
    Board.resize(M_f_width);
    for (int i=0; i<M_f_width; i++)
    {
        Board[i].resize(M_f_height, filling);
    }

    tmp=DEFAULT_CHECK;
    if(check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling, tmp))
    {
        throw this;
    }
    else
    {
        cast();
    }
}

Main_frame::~Main_frame() {}

// Copy constructor
Main_frame::Main_frame (const Main_frame& main_frame)
:Frame_properties(main_frame.x, main_frame.y, main_frame.width, main_frame.height, main_frame.edges_x, main_frame.edges_y, \
main_frame.corner_ur, main_frame.corner_dr, main_frame.corner_ul, main_frame.corner_dl), filling(main_frame.filling) {}

//constructor
Main_frame::Frame::Frame \
(Main_frame* window, Frame* f_father, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x, \
 const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, \
 const char& filling_corner_ul, const char& filling_corner_dl)
:Frame_properties(pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, \
filling_corner_dl), anchor(window), father(f_father) //!!!!!!!!!!!
{
    char tmp=DEFAULT_CHECK;
    if(Frame_properties::check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, tmp)||check_data(pos_x, pos_y, F_width, F_height))
    {
        throw this;
    }
    else
    {
        cast();
    }
}

Main_frame::Frame::~Frame() {}

//Copy constructor
Main_frame::Frame::Frame(const Frame& frame)
:Frame_properties(frame.x, frame.y, frame.width, frame.height, frame.edges_x, frame.edges_y, frame.corner_ur, frame.corner_dr, frame.corner_ul, \
frame.corner_dl), anchor(frame.anchor) {}

bool Main_frame::Frame::move(const int& OX, const int& OY)  // relative path, it can be negative
{
    if(check_data(x+OX, y+OY, width, height))
    {
        return true;
    }
    x=x+OX;
    y=y+OY;
    return false;
}

bool Main_frame::Frame::resize(const int& f_width, const int& f_height)       // absolute path
{
    if(check_data(x, y, f_width, f_height))
    {
        return true;
    }
    width=f_width;
    height=f_height;
    return false;
}

void Main_frame::move(const int& OX, const int& OY)  // relative path, it can be negative
{
    x=x+OX;
    y=y+OY;
}

bool Main_frame::resize(const int& f_width, const int& f_height)       // absolute path
{

}

int Main_frame::size_x()
{
    return width;
}

int Main_frame::size_y()
{
    return height;
}

int Main_frame::Frame::size_x()
{
    return width;
}

int Main_frame::Frame::size_y()
{
    return height;
}


#endif // MAIN_FRAME_CPP
