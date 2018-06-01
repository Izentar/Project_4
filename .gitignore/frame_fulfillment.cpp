#ifndef FRAME_FULFILLMENT_CPP
#define FRAME_FULFILLMENT_CPP

#include "frame_fulfillment.h"

bool Frame_fulfillment::cast()
{
    Main_frame::Frame* tmp=this;
    for (int i=1; i<tmp->f_height()-1; i++)
    {
        for (int j=1; j<tmp->f_width()-1; j++)
        {
            (*tmp)[j][i]=character;
        }
    }

    return false;
}

Frame_fulfillment::Frame_fulfillment(Main_frame* window, Frame* f_frame, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact, \
     string frame_name, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, const char& filling_corner_ul, \
     const char& filling_corner_dl)
: Frame(window, f_frame, pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl, frame_name), \
character(charact) {}

Frame_fulfillment::Frame_fulfillment(Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact, \
     string frame_name, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, const char& filling_corner_ul, \
     const char& filling_corner_dl)
:Frame(window, nullptr, pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl, frame_name), \
character(charact) {}

Frame_fulfillment::~Frame_fulfillment() {}



#endif // FRAME_FULFILLMENT_CPP
