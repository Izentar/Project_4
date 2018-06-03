/*
- zamiana ojcow, dzieci - OK?
- czy zmniejszenie ramki nie spowoduje wyjscia dzieci - OK
- stworzenie all_cast - OK
- stworzenie hierarchii dla uzytkownika, moze juz byc w wektorze children - OK
- wypisanie hierarchii - OK
- dostanie wymiarow na cout - OK
- lista, czy nie uzyto wczesniej takiej nazwy w srodku ramki - OK
- tworzenie unikalnych nazw na podstawie hierarchii nazw, zapis do pliku

*/

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <typeinfo>
//#include <set>
//#include <typeinfo>
//#include <cstddef>
//#include <exception>

using namespace std;

ostream& sizes(ostream& outgo);

class Frame_properties
{
    virtual bool cast()=0;

protected:
    static const char DEFAULT_VOID=3;
    static const char DEFAULT_AREA=' ';
    static const char DEFAULT_BORDER='*';
    static const char ILLEGAL_CHAR='~';
    static const char ILLEGAL_CHAR2='^';
    static const unsigned int MAX_CHAR=255;
    static const string UNDEFINED;

protected:
    int x, y, width, height;
    char edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl;
    string name;

    int absolute_x, absolute_y;

    virtual bool check_data(const int& f_width, const int& f_height, const char& f_edges_x, const char& f_edges_y, const char& f_corner_ur, const char& f_corner_dr, \
                            const char& f_corner_ul, const char& f_corner_dl);
    virtual string unique_name();
    virtual void save_file(ofstream& saving);
    //virtual void read_file();     // to implementation

public:
    Frame_properties(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, string f_name, const char& filling_edges_x=DEFAULT_VOID, \
                     const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID, \
                     const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);
    virtual ~Frame_properties();

    virtual int get_x();
    virtual int get_y();
    virtual int f_height();
    virtual int f_width();
};


const string UNDEFINED="UNDEFINED";


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

        bool check_names(string& this_name);
        friend void recursion_cast(Main_frame::Frame*);

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

    protected:
        Main_frame *anchor;
        Frame* father;
        vector <Frame*> children;

        virtual bool check_expand(const int&, const int&);
        virtual bool check_data(const int&, const int&, const int&, const int&);
        virtual bool check_shrink(const int&, const int&);
        virtual void save_file(ofstream& saving, string& name_save, bool please_set_here_true=false);

        friend class Array;
        friend class Main_frame;

        virtual Array operator[] (const int&);

    public:

        Frame (Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, string f_name, \
             const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID,\
             const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);
        Frame(Main_frame* window, Frame* f_frame, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, string f_name, \
              const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, const char& filling_corner_dr=DEFAULT_VOID, \
              const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID);

        virtual ~Frame();
        Frame(const Frame&);

        virtual bool cast();
        virtual bool move(const int&, const int&);
        virtual bool resize(const int&, const int&);
        virtual bool move_to(Frame*, const int&);
        virtual bool move_to(Main_frame*, const int&);

        friend bool swap(Main_frame::Frame*, Main_frame::Frame*);


        friend ostream& operator <<(ostream&, const Main_frame&);
        friend ostream& operator <<(ostream&, const Main_frame::Frame&);

    private:
        list <string> name_list;
    };

private:
    static bool ostream_flag;

    friend int find_frame_in_children(Main_frame*);
    friend int find_frame_in_father(Frame*);
    friend void recursion_output(ostream&, const Frame*, int);
    friend class Frame;
    void recursion_save_to_file_objects(Main_frame::Frame* frame, ofstream& saving);

    char filling;
    deque <deque <char>> Board;
    vector <Frame*> children;

protected:
    virtual bool check_data(const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&, const char&);
    virtual bool check_shrink(const int&, const int&);
    virtual void save_file(ofstream& saving, string& name_save, bool please_set_here_true=false);
    friend bool swap(Frame*, Frame*);


public:
    Main_frame(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, string f_name, \
               const char& filling_edges_x=DEFAULT_VOID, const char& filling_edges_y=DEFAULT_VOID, const char& filling_corner_ur=DEFAULT_VOID, \
               const char& filling_corner_dr=DEFAULT_VOID, const char& filling_corner_ul=DEFAULT_VOID, const char& filling_corner_dl=DEFAULT_VOID, \
               const char& main_filling=DEFAULT_VOID);
    virtual ~Main_frame();
    //Main_frame(const Main_frame&);

    virtual void show();
    virtual bool cast();
    virtual void all_cast();
    virtual bool move(const int&, const int&);
    virtual bool resize(const int&, const int&);

    virtual bool save_to_file_all();

    friend ostream& operator <<(ostream& outgo, const Main_frame& frame);
    friend ostream& sizes(ostream& outgo);
    friend ostream& operator <<(ostream& outgo, const Main_frame::Frame& frame);

private:
    list <string> name_list;

};


#endif // MAIN_FRAME_H
