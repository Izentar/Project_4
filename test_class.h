#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include "frame_inscription.h"
#include "frame_fulfillment.h"

#include <iostream>
using namespace std;

class Menu
{
    Main_frame* basic_frame=nullptr;
    Main_frame::Frame* actual_frame=nullptr;
    Main_frame* act_basic_frame=nullptr;


    string buff, tmp, tmp1;
    char c, c1, c2, c3, c4, c5, c6;
    int i, i1, i2, i3;
    vector<Main_frame::Frame*> frame_buff;


    Main_frame* new_basic_frame=nullptr;
    Main_frame* remember_basic_frame=nullptr;

    Main_frame::Frame* new_frame=nullptr;
    Main_frame::Frame* remember_frame=nullptr;

    bool give_data(int& pos_x, int& pos_y, int& width, int& height, string& name, char& edges_x, char& edges_y, char& ur, char& dr, char &ul, char& dl);
public:
    void menu_start();
    Menu() {};
    ~Menu() {};

private:
    bool go();  // go down to hierarchy
    bool back();    // back to father
    bool lack_main_frame();     // if main frame exist
    bool move_from();           // move object to  the remembered position
    bool move();            // move x, y
    bool resize();          // resize
    bool remember_frame_func();     // remember position
    bool show();        // show board
    bool save();        // save to file
    bool delete_this();     // delete object and all children
    bool hierarchy();       // show hierarchy
    bool where();           // show where are you now
    bool swap_menu();       // method swap
    bool inscription();     // new frame with inscription
    bool fulfillment();        // new frame with fulfillment
    bool frame();           // new clear frame
    void cleaning();        // method to eliminate some errors
    bool hierarchy_sizes();       // show hierarchy with sizes


    friend void cut_string(string& name);       // cut space at the end of string
};

#endif
