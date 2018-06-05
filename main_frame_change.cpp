#ifndef MAIN_FRAME_CAST_CPP
#define MAIN_FRAME_CAST_CPP

                        // do not forget to add source file
#include "main_frame.h"
#include "frame_inscription.h"
#include "frame_fulfillment.h"

string Frame_properties::unique_name()
{
    string tmp;

    Main_frame* tmp_main_frame;
    Main_frame::Frame* tmp_frame;
    Frame_inscription* tmp_inscription;
    Frame_fulfillment* tmp_fulfillment;

    // do not touch
    tmp+=ILLEGAL_CHAR;
    if((tmp_frame=dynamic_cast<Main_frame::Frame*>(this))!=nullptr)
    {
        tmp=tmp_frame->name;
    }
    else
    if((tmp_main_frame=dynamic_cast<Main_frame*>(this))!=nullptr)
    {
        tmp=tmp_main_frame->name;
    }
    // do not touch


    tmp+=ILLEGAL_CHAR;
    if((tmp_inscription=dynamic_cast<Frame_inscription*>(this))!=nullptr)
    {
        tmp+=tmp_inscription->name;
    }
    else
    if((tmp_fulfillment=dynamic_cast<Frame_fulfillment*>(this))!=nullptr)           // add only here after new else
    {
        tmp+=tmp_fulfillment->name;
    }

    return tmp;
}

void recursion_cast(Main_frame::Frame* frame)       // add dynamic_cast casting if a new type added
{
    /* */
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

    /* */

    // do not touch
    //
    frame->Main_frame::Frame::cast();
    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        recursion_cast(frame->children[i]);
    }
    //
    //
}

void Main_frame::recursion_save_to_file_objects(Main_frame::Frame* frame, ofstream& saving)
{

    //
    string tmp;// important clear string before cast

    Frame_inscription* tmp_inscription;
    Frame_fulfillment* tmp_fulfillment;

    // add here
    if((tmp_inscription=dynamic_cast<Frame_inscription*>(frame))!=nullptr)
    {
        tmp_inscription->save_file(saving, tmp, true);
    }
    else
    if((tmp_fulfillment=dynamic_cast<Frame_fulfillment*>(frame))!=nullptr)      // add else if new class appear. Set the please_set_here_true on true and tmp must be clear!!
    {
        tmp_fulfillment->save_file(saving, tmp, true);
    }
    // add here


    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        this->recursion_save_to_file_objects(frame->children[i], saving);
    }
}


#endif // MAIN_FRAME_CAST_CPP
