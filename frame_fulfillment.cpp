#ifndef FRAME_FULFILLMENT_CPP
#define FRAME_FULFILLMENT_CPP

#include "frame_fulfillment.h"


void Frame_fulfillment::save_file(ofstream& saving, string& name_save, bool please_set_here_true)
{
    if(please_set_here_true)
    {
        string name_frame;
        name_save=this->Frame_properties::unique_name();
        saving.write(name_save.c_str(), name_save.size()+1);
        name_frame=typeid(*this).name();
        saving.write(name_frame.c_str(), name_frame.size()+1);
    }

    this->Main_frame::Frame::save_file(saving, name);

    saving.write((char*)&character, sizeof(char));
}

bool Frame_fulfillment::cast()
{
    for (int i=1; i<this->f_height()-1; i++)
    {
        for (int j=1; j<this->f_width()-1; j++)
        {
            (*this)[j][i]=character;
        }
    }

    return false;
}

Frame_fulfillment::Frame_fulfillment(Main_frame* window, Frame* f_frame, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact, \
     string frame_name, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, const char& filling_corner_ul, \
     const char& filling_corner_dl)
: Frame(window, f_frame, pos_x, pos_y, F_width, F_height, frame_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl), \
character(charact) {}

Frame_fulfillment::Frame_fulfillment(Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact, \
     string frame_name, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, const char& filling_corner_ul, \
     const char& filling_corner_dl)
:Frame(window, nullptr, pos_x, pos_y, F_width, F_height, frame_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl), \
character(charact) {}

Frame_fulfillment::~Frame_fulfillment() {}



#endif // FRAME_FULFILLMENT_CPP
