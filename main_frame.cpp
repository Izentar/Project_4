#ifndef MAIN_FRAME_CPP
#define MAIN_FRAME_CPP

#include "main_frame.h"

const char Frame_properties::DEFAULT_VOID;
const char Frame_properties::DEFAULT_AREA;
const char Frame_properties::DEFAULT_BORDER;
const unsigned int Frame_properties::MAX_CHAR;

void recursion_output(ostream& outgo, const Main_frame::Frame* frame, int number)
{
    number++;
    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        for (int i=0; i<number; i++)
        {
            outgo << "  ";
        }
        outgo << "- " << frame->children[i]->name << endl;
        recursion_output(outgo, frame->children[i], number);
    }
}

ostream& operator <<(ostream& outgo, const Main_frame::Frame& frame)
{
    outgo << "- " << frame.name << endl;
    recursion_output(outgo, &frame, 1);
    return outgo;
}

ostream& operator <<(ostream& outgo, const Main_frame& frame)
{
    outgo << "- " << frame.name << endl;
    for (unsigned int i=0; i<frame.children.size(); i++)
    {
        outgo << "  - " << frame.children[i]->name << endl;
        recursion_output(outgo, frame.children[i], 2);
    }
    return outgo;
}

Main_frame::Frame::Array Main_frame::Frame::operator[] (const int& val)
{
    Main_frame *tmp=this->anchor;
    auto tmp_char=(tmp->Board.begin()+val+absolute_x)->begin();
    return Array(tmp_char, absolute_y);
}

Main_frame::Frame::Array::Array(deque<char>::iterator val, const int& pos_y)
:tmp(val), absolute_y(pos_y) {}

char& Main_frame::Frame::Array::operator[] (const int& val)
{
    return *(this->tmp+val+absolute_y);
}

void Main_frame::show()
{
    for (int i=0; i<y; i++)
    {
        cout << endl;
    }
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<x; j++)
        {
            cout << Frame_properties::DEFAULT_AREA;
        }
        for (int j=0; j<width; j++)
        {
            cout << Board[j][i];
        }
        cout << endl;
    }

}

void Main_frame::cast()
{
    if(edges_x!=DEFAULT_VOID)
    {
        for(int i=1; i<width-1; i++)
        {
            Board[i][0]=edges_x;
            Board[i][height-1]=edges_x;
        }
    }
    else
    {
        for(int i=1; i<width-1; i++)
        {
            Board[i][0]=DEFAULT_AREA;
            Board[i][height-1]=DEFAULT_AREA;
        }
    }


    if(edges_y!=DEFAULT_VOID)
    {
        for (int i=1; i<height-1; i++)
        {
            Board[0][i]=edges_y;
            Board[width-1][i]=edges_y;
        }
    }
    else
    {
        for (int i=1; i<height-1; i++)
        {
            Board[0][i]=DEFAULT_AREA;
            Board[width-1][i]=DEFAULT_AREA;
        }
    }


    if(corner_ul!=DEFAULT_VOID)
    {
        Board[0][0]=corner_ul;
    }
    else
    {
        Board[0][0]=DEFAULT_AREA;
    }

    if(corner_dl!=DEFAULT_VOID)
    {
        Board[0][height-1]=corner_dl;
    }
    else
    {
        Board[0][height-1]=DEFAULT_AREA;
    }

    if(corner_dr!=DEFAULT_VOID)
    {
        Board[width-1][height-1]=corner_dr;
    }
    else
    {
        Board[width-1][height-1]=DEFAULT_AREA;
    }

    if(corner_ur!=DEFAULT_VOID)
    {
        Board[width-1][0]=corner_ur;
    }
    else
    {
        Board[width-1][0]=DEFAULT_AREA;
    }
}

void Main_frame::Frame::cast()
{
    if(edges_x!=DEFAULT_VOID)
    {
        for (int i=absolute_x+1; i<absolute_x+width-1; i++)
        {
            anchor->Board[i][absolute_y]=edges_x;
            anchor->Board[i][absolute_y+height-1]=edges_x;
        }
    }

    if(edges_y!=DEFAULT_VOID)
    {
        for (int i=absolute_y+1; i<absolute_y+height-1; i++)
        {
            anchor->Board[absolute_x][i]=edges_y;
            anchor->Board[absolute_x+width-1][i]=edges_y;
        }
    }

    if(corner_ul!=DEFAULT_VOID)
    {
        anchor->Board[absolute_x][absolute_y]=corner_ul;
    }
    if(corner_dl!=DEFAULT_VOID)
    {
        anchor->Board[absolute_x][absolute_y+height-1]=corner_dl;
    }
    if(corner_ur!=DEFAULT_VOID)
    {
        anchor->Board[absolute_x+width-1][absolute_y]=corner_ur;
    }
    if(corner_dr!=DEFAULT_VOID)
    {
        anchor->Board[absolute_x+width-1][absolute_y+height-1]=corner_dr;
    }
}

void recursion_cast(Main_frame::Frame* frame)
{
    frame->cast();
    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        recursion_cast(frame->children[i]);
    }
}

void Main_frame::all_cast()
{
    for (unsigned int i=0; i<Board.size(); i++)
    {
        for (unsigned int j=0; j<Board[i].size(); j++)
        {
            Board[i][j]=DEFAULT_AREA;
        }
    }

    this->cast();
    for (unsigned int i=0; i<children.size(); i++)
    {
        recursion_cast(children[i]);
    }
}

int find_frame_in_father(Main_frame::Frame* f_frame)
{
    Main_frame::Frame *tmp=f_frame->father;
    Main_frame *tmp2=f_frame->anchor;
    if(tmp!=nullptr)
    {
        for (unsigned int i=0; i<tmp->children.size(); i++)
        {
            if(tmp->children[i]==f_frame)
            {
                return i;
            }
        }
    }
    else
    {
        for (unsigned int i=0; i<tmp2->children.size(); i++)
        {
            if(tmp2->children[i]==f_frame)
            {
                return i;
            }
        }
    }
    return -1;
}

int find_frame_in_children(Main_frame::Frame* f_frame)
{
    Main_frame::Frame *tmp;
    for (unsigned int i=0; i<f_frame->children.size(); i++)
    {
        tmp=f_frame->children[i];

        if(tmp->father==f_frame)
        {
            return i;
        }
    }
    return -1;
}

int find_frame_in_children(Main_frame* m_frame)
{
    Main_frame::Frame *tmp;
    for (unsigned int i=0; i<m_frame->children.size(); i++)
    {
        tmp=m_frame->children[i];

        if(tmp->anchor==m_frame)
        {
            return i;
        }
    }
    return -1;
}

bool Frame_properties::check_data \
(const int& f_width, const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl)
{
    if(f_width<=0||f_height<=0)
    {
        return true;
    }
    if((f_edges_x!=DEFAULT_VOID&&f_edges_x<32)||(f_edges_y!=DEFAULT_VOID&&f_edges_y<32))
    {
        return true;
    }
    if((f_corner_ur!=DEFAULT_VOID&&f_corner_ur<32)||(f_corner_dr!=DEFAULT_VOID&&f_corner_dr<32))
    {
        return true;
    }
    if((f_corner_ul!=DEFAULT_VOID&&f_corner_ul<32)||(f_corner_dl!=DEFAULT_VOID&&f_corner_dl<32))
    {
        return true;
    }
    return false;
}

bool Main_frame::Frame::check_shrink(const int& f_width, const int& f_height)
{
     for (unsigned int i=0; i<children.size(); i++)
     {
        if((children[i]->x+children[i]->width>f_width)||(children[i]->y+children[i]->height>f_height))
        {
            return true;
        }
     }
     return false;
}

bool Main_frame::check_shrink(const int& f_width, const int& f_height)
{
    for (unsigned int i=0; i<children.size(); i++)
    {
        if((children[i]->x+children[i]->width>f_width)||(children[i]->y+children[i]->height>f_height))
        {
            return true;
        }
    }
    return false;
}

bool Main_frame::Frame::check_expand(const int& f_width, const int& f_height)
{
    if(this->father==nullptr)
    {
        Main_frame *tmp=this->anchor;
        if((tmp->width<x+width)||(tmp->height<y+height))
        {
            return true;
        }
    }
    else
    {
        if((x+f_width>father->x+father->width)||(y+f_height>father->y+father->height))
        {
            return true;
        }
    }

    return false;
}

bool Main_frame::Frame::check_data(const int& new_x, const int& new_y, const int& f_width, const int& f_height)
{
    if(father==nullptr)
    {
        return check_expand(f_width, f_height)||check_shrink(f_width, f_height);
    }

    if(new_x<0||new_y<0)
    {
        return true;
    }

    if((new_x+f_width>father->width)||(new_y+f_height>father->height))
    {
        return true;
    }
    return check_expand(f_width, f_height)||check_shrink(f_width, f_height);
}

bool Main_frame::check_data \
(const int& f_width,const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& f_filling)
{
    if(f_filling!=DEFAULT_VOID&&f_filling<32)
    {
        return true;
    }
    return Frame_properties::check_data(f_width, f_height, f_edges_x, f_edges_y, f_corner_ur, f_corner_dr, f_corner_ul, f_corner_dl)||check_shrink(f_width, f_height);
}

//constructor
Frame_properties::Frame_properties \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl, string f_name)
:x(position_x), y(position_y), width(M_f_width), height(M_f_height), edges_x(filling_edges_x), edges_y(filling_edges_y), corner_ur(filling_corner_ur), \
corner_dr(filling_corner_dr), corner_ul(filling_corner_ul), corner_dl(filling_corner_dl), name(f_name) {}

Frame_properties::~Frame_properties() {};

//constructor
Main_frame::Main_frame \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, \
const char&filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl, \
const char& main_filling, string f_name)
:Frame_properties(position_x, position_y, M_f_width, M_f_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, \
filling_corner_ul, filling_corner_dl, f_name), filling(main_filling)
{
    char tmp=DEFAULT_AREA;

    if(filling!=DEFAULT_VOID)
    {
        tmp=filling;
    }

    Board.resize(M_f_width);
    for (int i=0; i<M_f_width; i++)
    {
        Board[i].resize(M_f_height, tmp);
    }

    if(check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling))
    {
        throw this;
    }
}

Main_frame::Frame::~Frame()
{
    if(father==nullptr)
    {
        for (unsigned int i=0; i<anchor->children.size(); i++)
        {
            if(anchor->children[i]==this)
            {
                anchor->children.erase((anchor->children.begin()+i));
                break;
            }
        }
    }
    else
    {
        for (unsigned int i=0; i<father->children.size(); i++)
        {
            if(father->children[i]==this)
            {
                father->children.erase((father->children.begin()+i));
                break;
            }
        }
    }

    for (unsigned int i=0; i<children.size(); i++)
    {
        delete children[i];
    }
}

Main_frame::~Main_frame()
{
    for (unsigned int i=0; i<children.size(); i++)
    {
        delete children[i];
    }
}

// Copy constructor
Main_frame::Main_frame (const Main_frame& main_frame)
:Frame_properties(main_frame.x, main_frame.y, main_frame.width, main_frame.height, main_frame.edges_x, main_frame.edges_y, \
main_frame.corner_ur, main_frame.corner_dr, main_frame.corner_ul, main_frame.corner_dl, main_frame.name), filling(main_frame.filling) {}

//constructor
Main_frame::Frame::Frame \
(Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x, \
 const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, \
 const char& filling_corner_ul, const char& filling_corner_dl, string f_name)
:Frame_properties(pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, \
filling_corner_dl, f_name), anchor(window), father(nullptr)
{
    if(Frame_properties::check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl)||check_data(pos_x, pos_y, F_width, F_height))
    {
        throw this;
    }
    else
    {
        absolute_x=x;
        absolute_y=y;

        (anchor->children).push_back(this);
    }
}

//constructor
Main_frame::Frame::Frame \
(Main_frame* window, Frame* f_father, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, const char& filling_edges_x, \
 const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, \
 const char& filling_corner_ul, const char& filling_corner_dl, string f_name)
:Frame_properties(pos_x, pos_y, F_width, F_height, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, \
filling_corner_dl, f_name), anchor(window), father(f_father)
{
    if(Frame_properties::check_data(width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl)||check_data(pos_x, pos_y, F_width, F_height))
    {
        throw this;
    }
    else
    {
        absolute_x=father->absolute_x+x;
        absolute_y=father->absolute_y+y;

        (father->children).push_back(this);
    }
}

//Copy constructor
Main_frame::Frame::Frame(const Frame& frame)
:Frame_properties(frame.x, frame.y, frame.width, frame.height, frame.edges_x, frame.edges_y, frame.corner_ur, frame.corner_dr, frame.corner_ul, \
frame.corner_dl, frame.name), anchor(frame.anchor) {}

void parent_child_fitting(Main_frame::Frame* f_frame, const int& shift_x, const int& shift_y)
{
    f_frame->absolute_x=f_frame->absolute_x+shift_x;
    f_frame->absolute_y=f_frame->absolute_y+shift_y;

    for (unsigned int i=0; i<f_frame->children.size(); i++)
    {
        parent_child_fitting(f_frame->children[i], shift_x, shift_y);
    }
}

bool Main_frame::Frame::move(const int& shift_x, const int& shift_y)  // relative path, it can be negative
{
    if(check_data(x+shift_x, y+shift_y, width, height))
    {
        return true;
    }
    x=x+shift_x;
    y=y+shift_y;

    parent_child_fitting(this, shift_x, shift_y);

    return false;
}

bool Main_frame::Frame::resize(const int& f_width, const int& f_height)       // absolute path, relative to left edge
{
    if(check_data(x, y, f_width, f_height))
    {
        return true;
    }
    width=f_width;
    height=f_height;

    return false;
}

void Main_frame::move(const int& shift_x, const int& shift_y)  // relative path, it can be negative
{
    x=x+shift_x;
    y=y+shift_y;
}

bool Main_frame::resize(const int& f_width, const int& f_height)       // absolute path, relative to left edge
{
    if(check_shrink(f_width, f_height))
    {
        return true;
    }

    char tmp=DEFAULT_AREA;
    Board.resize(f_width);

    for (unsigned int i=0; i<Board.size(); i++)
    {
        Board[i].resize(f_height, tmp);
    }

    width=f_width;
    height=f_height;

    return false;
}

int Frame_properties::size_x()
{
    return width;
}

int Frame_properties::size_y()
{
    return height;
}

bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame)   // important method, end in (0,0)
{
    int tmp=find_frame_in_father(f_frame), tmp2=find_frame_in_father(s_frame);
    int tmp3=find_frame_in_children(f_frame), tmp4=find_frame_in_children(s_frame);
    //int dx, dy;

    if(tmp==-1||tmp2==-1||tmp3==-1||tmp4==-1)
    {
        return true;
    }

    if(f_frame!=nullptr)
    {
        if(f_frame->father->width<s_frame->width||f_frame->father->height<s_frame->height) return true;
    }
    else
    {
        if(f_frame->anchor->width<s_frame->width||f_frame->anchor->height<s_frame->height) return true;
    }

    if(s_frame!=nullptr)
    {
        if(s_frame->father->width<f_frame->width||s_frame->father->height<f_frame->height) return true;
    }
    else
    {
        if(s_frame->anchor->width<f_frame->width||s_frame->anchor->height<f_frame->height) return true;
    }

    if(f_frame->father==nullptr)
    {
        f_frame->anchor->children[tmp]=s_frame;
    }
    else
    {
        f_frame->father->children[tmp]=s_frame;
    }

    if(s_frame->father==nullptr)
    {
        s_frame->anchor->children[tmp2]=f_frame;
    }
    else
    {
        s_frame->father->children[tmp2]=f_frame;
    }

    f_frame->children[tmp3]=s_frame;
    s_frame->children[tmp4]=f_frame;


    // reset to (0,0) in father, both

    /*if(f_frame->absolute_x<=s_frame->absolute_x)
    {
        dx=s_frame->absolute_x-f_frame->absolute_x;
    }
    else
    {
        dx=f_frame->absolute_x-s_frame->absolute_x;
    }
    if(f_frame->absolute_y<=s_frame->absolute_y)
    {
        dy=s_frame->absolute_y-f_frame->absolute_y;
    }
    else
    {
        dy=f_frame->absolute_y-s_frame->absolute_y;
    }*/


    tmp=f_frame->absolute_x;
    tmp2=f_frame->absolute_y;

    //reset position
    parent_child_fitting(f_frame, (s_frame->absolute_x)-(f_frame->absolute_x-f_frame->x), (s_frame->absolute_y)-(f_frame->absolute_y-f_frame->y));
    parent_child_fitting(s_frame, (tmp)-(s_frame->absolute_x-s_frame->x), (tmp2)-(s_frame->absolute_y-s_frame->y));
    f_frame->x=0;
    f_frame->y=0;
    s_frame->x=0;
    s_frame->y=0;


    return false;
}

bool Main_frame::Frame::move_to(Main_frame::Frame* here, const int& where=-1)        // add at to the pointer children, reset to (0,0)
{
    int itmp=find_frame_in_father(this);

    if(itmp==-1)
    {
        return true;
    }

    if(here->width<width||here->height<height)
    {
        return true;
    }

    // move frame
    if(father!=nullptr)
    {
        father->children.erase((father->children).begin()+itmp);
    }
    else
    {
        anchor->children.erase((anchor->children).begin()+itmp);
    }

    father=here;
    itmp=where;

    if(itmp<0||(unsigned int)where>=here->children.size())
    {
        itmp=here->children.size()-1;
    }

    if(itmp<0)     // may be size=0
    {
        (here->children).push_back(this);
    }
    else
    {
        (here->children).insert(here->children.begin()+itmp, this);
    }

    // reset position
    parent_child_fitting(this, here->absolute_x-(absolute_x-x), here->absolute_y-(absolute_y-y));
    x=0;
    y=0;

    return false;

}

bool Main_frame::Frame::move_to(Main_frame* here, const int& where=-1)
{
    int itmp=where, itmp2=find_frame_in_father(this);

    if(itmp2==-1)
    {
        return true;
    }

    if(here->width<width||here->height<height)
    {
        return true;
    }

    if(itmp<0||(unsigned int)where>=here->children.size())
    {
        itmp=here->children.size()-1;
    }

    if(itmp<0)     // may be size=0
    {
        itmp=0;
    }

    // move frame
    if(father!=nullptr)
    {
        father->children.erase((father->children).begin()+itmp2);
    }
    else
    {
        anchor->children.erase((anchor->children).begin()+itmp2);
    }

    (here->children).insert(here->children.begin()+itmp, this);

    // reset position
    parent_child_fitting(this, here->absolute_x-(absolute_x-x), here->absolute_y-(absolute_y-y));
    x=0;
    y=0;

    return false;
}



#endif // MAIN_FRAME_CPP
