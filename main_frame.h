/*
- zamiana ojcow, dzieci - OK?
- czy zmniejszenie ramki nie spowoduje wyjscia dzieci - OK
- stworzenie all_cast
- stworzenie hierarchii dla uzytkownika, moze juz byc w wektorze children - OK
- wypisanie hierarchii - OK


*/

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <iostream>
#include <deque>
#include <vector>
#include <set>
#include <typeinfo>
#include <cstddef>
#include <exception>

using namespace std;


class Frame_properties
{
public:
    static const char DEFAULT_VOID=3;
    static const char DEFAULT_AREA=' ';
    static const char DEFAULT_BORDER='*';
    static const unsigned int MAX_CHAR=100;

protected:
    int x, y, width, height;
    char edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl;
    string name;

    int absolute_x, absolute_y;

    virtual bool check_data(const int& f_width, const int& f_height, const char& f_edges_x, const char& f_edges_y, const char& f_corner_ur, const char& f_corner_dr, \
                            const char& f_corner_ul, const char& f_corner_dl);

public:
    Frame_properties(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x=DEFAULT_VOID, \
                     const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID, \
                     const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID, string f_name="UNDEFINED");
    virtual ~Frame_properties();

    virtual int size_x();
    virtual int size_y();
};

class Main_frame: public Frame_properties
{
public:

    class Frame: public Frame_properties
    {
    private:
        friend int find_frame_in_father(Main_frame::Frame*);
        friend int find_frame_in_children(Main_frame::Frame*);
        friend int find_frame_in_children(Main_frame*);
        friend void parent_child_fitting(Frame*, const int&, const int&);
        friend void recursion_output(ostream&, const Frame*, int);



    public:
        class Array
        {
            deque<char>::iterator tmp;
            int absolute_y;
        public:
            Array(deque<char>::iterator, const int&);
            virtual ~Array() {};
            virtual char& operator[] (const int&);
        };

    //protected:
        Main_frame *anchor;
        Frame* father;
        vector <Frame*> children;

        virtual bool check_expand(const int&, const int&);
        virtual bool check_data(const int&, const int&, const int&, const int&);
        virtual bool check_shrink(const int&, const int&);
        virtual Array operator[] (const int&);

        friend class Array;
        friend class Main_frame;

    public:

        Frame (Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x=DEFAULT_VOID, \
             const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID,\
             const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID, string f_name="UNDEFINED");
        Frame(Main_frame* window, Frame* f_frame, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x=DEFAULT_VOID, \
              const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID, \
              const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID, string f_name="UNDEFINED");

        virtual ~Frame();
        Frame(const Frame&);

        virtual void cast();
        virtual bool move(const int&, const int&);
        virtual bool resize(const int&, const int&);
        virtual bool move_to(Frame*, const int&);
        virtual bool move_to(Main_frame*, const int&);
        friend bool swap(Main_frame::Frame*, Main_frame::Frame*);
        friend void recursion_cast(Main_frame::Frame*);

        friend ostream& operator <<(ostream&, const Main_frame&);
        friend ostream& operator <<(ostream&, const Main_frame::Frame&);
    };


private:
    friend int find_frame_in_children(Main_frame*);
    friend bool swap(Frame*, Frame*);
    friend int find_frame_in_father(Frame*);
    friend void recursion_output(ostream&, const Frame*, int);
    friend class Frame;

protected:
    char filling;
    deque <deque <char>> Board;
    vector <Frame*> children;

    virtual bool check_data(const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);
    virtual bool check_shrink(const int&, const int&);

public:

    Main_frame(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, \
               const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, \
               const char& filling_corner_dl=DEFAULT_VOID, const char& main_filling=DEFAULT_VOID, string f_name="UNDEFINED");
    virtual ~Main_frame();
    Main_frame(const Main_frame&);

    virtual void show();
    virtual void cast();
    virtual void all_cast();
    virtual void move(const int&, const int&);
    virtual bool resize(const int&, const int&);

    friend ostream& operator <<(ostream& outgo, const Main_frame& frame);

};



#endif // MAIN_FRAME_H
