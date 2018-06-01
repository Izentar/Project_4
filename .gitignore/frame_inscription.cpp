#ifndef FRAME_INSCRIPTION_CPP
#define FRAME_INSCRIPTION_CPP

#include "frame_inscription.h"
#include <typeinfo>

const int Frame_inscription::DEFAULT_FRAME;

bool Frame_inscription::cast()
{
    if(width<DEFAULT_FRAME&&height<DEFAULT_FRAME)
    {
        return true;
    }

    Main_frame::Frame *tmp=this;
    int counter=0;

    for (int k=1; k<this->f_height()-1&&counter<(int)inscription.size(); k++)
    {
        for (int j=1; j<this->f_width()-1&&counter<(int)inscription.size(); j++)
        {
            (*tmp)[j][k]=inscription[counter++];
        }
    }

    return false;
}

Frame_inscription::Frame_inscription(Main_frame* window, Main_frame::Frame* f_frame, string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
    string frame_name, const char& filling_edges_x,  const char& filling_edges_y, const char& filling_corner_ur, \
    const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl)
: Frame(window, f_frame, pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl, frame_name), \
inscription(inscript) {}

Frame_inscription::Frame_inscription(Main_frame* window, nullptr_t, string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
    string frame_name, const char& filling_edges_x,  const char& filling_edges_y, const char& filling_corner_ur, \
    const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl)
: Frame(window, nullptr, pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl, frame_name), \
inscription(inscript) {}

Frame_inscription::~Frame_inscription() {}




#endif // FRAME_INSCRIPTION_CPP
