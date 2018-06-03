#ifndef FRAME_INSCRIPTION_CPP
#define FRAME_INSCRIPTION_CPP

#include "frame_inscription.h"

void Frame_inscription::save_file(ofstream& saving, string& name_save, bool please_set_here_true)
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

    saving.write(inscription.c_str(), inscription.size()+1);
}

bool Frame_inscription::cast()
{
    if(width<3&&height<3)
    {
        return true;
    }
    int counter=0;

    for (int k=1; k<this->f_height()-1&&counter<(int)inscription.size(); k++)
    {
        for (int j=1; j<this->f_width()-1&&counter<(int)inscription.size(); j++)
        {
            (*this)[j][k]=inscription[counter++];
        }
    }

    return false;
}

Frame_inscription::Frame_inscription(Main_frame* window, Main_frame::Frame* f_frame, string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
    string frame_name, const char& filling_edges_x,  const char& filling_edges_y, const char& filling_corner_ur, \
    const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl)
: Frame(window, f_frame, pos_x, pos_y, F_width, F_height, frame_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl), \
inscription(inscript) {}

Frame_inscription::Frame_inscription(Main_frame* window, nullptr_t, string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
    string frame_name, const char& filling_edges_x,  const char& filling_edges_y, const char& filling_corner_ur, \
    const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl)
: Frame(window, nullptr, pos_x, pos_y, F_width, F_height, frame_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, filling_corner_dl), \
inscription(inscript) {}

Frame_inscription::~Frame_inscription() {}




#endif // FRAME_INSCRIPTION_CPP
