#ifndef MAIN_FRAME_CAST_CPP
#define MAIN_FRAME_CAST_CPP

                        // do not forget to add source file
#include "main_frame.h"
#include "frame_inscription.h"
#include "frame_fulfillment.h"

void recursion_cast(Main_frame::Frame* frame)       // add dynamic_cast casting if a new type added
{
    Frame_inscription* tmp_inscription;
    Frame_fulfillment* tmp_fulfillment;

    if((tmp_inscription=dynamic_cast<Frame_inscription*>(frame))!=nullptr)
    {
        tmp_inscription->Frame_inscription::cast();
    }
    else
    if((tmp_fulfillment=dynamic_cast<Frame_fulfillment*>(frame))!=nullptr)
    {
        tmp_fulfillment->Frame_fulfillment::cast();
    }

    // do not touch
    //
    frame->Main_frame::Frame::cast();
    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        recursion_cast(frame->children[i]);
    }

    //
}



#endif // MAIN_FRAME_CAST_CPP
