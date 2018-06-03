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

    tmp+=ILLEGAL_CHAR;
    if((tmp_inscription=dynamic_cast<Frame_inscription*>(this))!=nullptr)
    {
        tmp+=tmp_inscription->name;
    }
    else
    if((tmp_fulfillment=dynamic_cast<Frame_fulfillment*>(this))!=nullptr)
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
}

void Main_frame::recursion_save_to_file_objects(Main_frame::Frame* frame, ofstream& saving)
{

    //
    string tmp;
    frame->save_file(saving, tmp, true);

    /*Frame_inscription* tmp_inscription;       // unused
    Frame_fulfillment* tmp_fulfillment;

    if((tmp_inscription=dynamic_cast<Frame_inscription*>(frame))!=nullptr)
    {
        saving.write((char*)tmp_inscription, sizeof(*tmp_inscription));
    }
    else
    if((tmp_fulfillment=dynamic_cast<Frame_fulfillment*>(frame))!=nullptr)
    {
        saving.write((char*)tmp_fulfillment, sizeof(*tmp_fulfillment));
    }*/
    //

    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        this->recursion_save_to_file_objects(frame->children[i], saving);
    }
}

/*void Main_frame::recursion_save_to_file_hierarchy(Main_frame::Frame* frame, ofstream& saving, int number)
{
    saving.write((char*)&number, sizeof(int));


}*/

bool Main_frame::save_to_file_all()
{
    ofstream saving;
    string name_frame;
    saving.open("objects.bin", ios_base::trunc|ios_base::binary);
    if(!saving.good())
    {
        return true;
    }
    //

    //saving.write((char*)ILLEGAL_CHAR2, sizeof(char));   // begin


    //
    this->save_file(saving, name_frame, true);
    //name_frame=this->name;
    //saving.write(name_frame.c_str(), name_frame.size()+1);
    for (unsigned int i=0; i<children.size(); i++)
    {
        this->recursion_save_to_file_objects(children[i], saving);
    }
    //

    //saving.write((char*)ILLEGAL_CHAR2, sizeof(char));       // middle

    saving.close();
    /*saving.open("hierarchy.bin", ios_base::trunc|ios_base::binary);
    if(!saving.good())
    {
        return true;
    }

    //
    name_frame=this->name;
    saving.write(name_frame.c_str(), name_frame.size()+1);
    for (unsigned int i=0; i<children.size(); i++)
    {
        this->recursion_save_to_file_hierarchy(children[i], saving, 1);
    }
    //


    //saving.write((char*)ILLEGAL_CHAR2, sizeof(char));   // end
*/
    return false;
}


#endif // MAIN_FRAME_CAST_CPP
