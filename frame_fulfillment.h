#ifndef FRAME_FULFILLMENT_H
#define FRAME_FULFILLMENT_H

#include "main_frame.h"

class Frame_fulfillment: public Main_frame::Frame
{
private:
    char character;

public:

    Frame_fulfillment(Main_frame* window, Frame* f_frame, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact=DEFAULT_AREA, \
     string frame_name=UNDEFINED, const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, \
     const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);

    Frame_fulfillment(Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& charact=DEFAULT_AREA, \
     string frame_name=UNDEFINED, const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, \
     const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);

    virtual ~Frame_fulfillment();

    virtual bool cast();
};



#endif // FRAME_FULFILLMENT_H
