#ifndef FRAME_INSCRIPTION_H
#define FRAME_INSCRIPTION_H

#include "main_frame.h"


/*const char Frame_properties::DEFAULT_VOID;
const char Frame_properties::DEFAULT_AREA;
const char Frame_properties::DEFAULT_BORDER;
const string UNDEFINED="UNDEFINED";*/


class Frame_inscription: public Main_frame::Frame       // width and height are relative to frame
{
protected:
    string inscription;

public:
    Frame_inscription(Main_frame* window, Main_frame::Frame* f_frame, string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
        string f_name, const char& filling_edges_x=DEFAULT_VOID,  const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, \
        const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);
    Frame_inscription(Main_frame* window, nullptr_t ,string inscript, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, \
        string frame_name, const char& filling_edges_x=DEFAULT_VOID,  const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, \
        const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);
    virtual ~Frame_inscription();

    virtual bool cast();
};



#endif // FRAME_INSCRIPTION_H
