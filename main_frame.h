/*
- zamiana ojcow, dzieci
- czy zmniejszenie ramki nie spowoduje wyjscia dzieci




*/

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <iostream>
#include <deque>
#include <vector>
#include <set>
#include <typeinfo>
#include <exception>

using namespace std;


class Frame_properties
{
protected:
    int x, y, width, height;
    char edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl;
    //vector <Frame*> children;
    string name;

    virtual bool check_data(const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);

public:
    Frame_properties(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x=DEFAULT_CHECK, \
                     const char& filling_edges_y=DEFAULT_CHECK, const char& filling_corner_ur=DEFAULT_CHECK, const char& filling_corner_dr=DEFAULT_CHECK, \
                     const char& filling_corner_ul=DEFAULT_CHECK, const char& filling_corner_dl=DEFAULT_CHECK);
    virtual ~Frame_properties();

    virtual int size_x()=0;
    virtual int size_y()=0;

    static const char DEFAULT_CHECK=3;
    static const char DEFAULT_VOID=' ';
    static const char DEFAULT_AREA=' ';
    static const char DEFAULT_BORDER='*';
};

class Main_frame: public Frame_properties
{
public:

    class Frame: public Frame_properties
    {
    public:
        class Array
        {
            deque<char>::iterator tmp;
            int y;
        public:
            Array(deque<char>::iterator, const int&);
            virtual ~Array() {};
            virtual char& operator[] (const int&);
        };

    protected:
        Main_frame *anchor;
        Frame* father;
        vector <Frame*> children;

        virtual bool check_expand(const int&, const int&);
        virtual bool check_data(const int&, const int&, const int&, const int&);
        virtual bool check_shrink(const int&, const int&);
        virtual Array operator[] (const int&);

        friend class Array;

    public:

        Frame(Main_frame* window, Frame*, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x=DEFAULT_CHECK, \
              const char& filling_edges_y=DEFAULT_CHECK, const char& filling_corner_ur=DEFAULT_CHECK, const char& filling_corner_dr=DEFAULT_CHECK, \
              const char& filling_corner_ul=DEFAULT_CHECK, const char& filling_corner_dl=DEFAULT_CHECK);
        virtual ~Frame();
        Frame(const Frame&);

        //virtual bool check_size(const int& f_width, const int& f_height);
        virtual void cast();
        virtual bool move(const int&, const int&);
        virtual bool resize(const int&, const int&);
        virtual int size_x();
        virtual int size_y();

    };
    friend class Frame;

protected:
    char filling;
    deque <deque <char>> Board;
    vector <Frame*> children;

    virtual bool check_data(const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);
    virtual bool check_shrink(const int&, const int&);

public:

    Main_frame(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x=DEFAULT_CHECK, const char& filling_edges_y=DEFAULT_CHECK, \
               const char& filling_corner_ur=DEFAULT_CHECK, const char& filling_corner_dr=DEFAULT_CHECK, const char& filling_corner_ul=DEFAULT_CHECK, \
               const char& filling_corner_dl=DEFAULT_CHECK, const char& main_filling=DEFAULT_CHECK);
    virtual ~Main_frame();
    Main_frame(const Main_frame&);

    virtual void cast();
    virtual int size_x();
    virtual int size_y();
    virtual void move(const int&, const int&);
    virtual bool resize(const int&, const int&);

    friend ostream& operator <<(ostream& outgo, const Main_frame& frame);

};



#endif // MAIN_FRAME_H
