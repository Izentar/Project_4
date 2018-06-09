#ifndef MAIN_FRAME_CPP
#define MAIN_FRAME_CPP

#include "main_frame.h"

const char Frame_properties::DEFAULT_VOID;
const char Frame_properties::DEFAULT_AREA;
const char Frame_properties::DEFAULT_BORDER;
const char Frame_properties::ILLEGAL_CHAR;
const char Frame_properties::ILLEGAL_CHAR2;
bool Main_frame::ostream_flag=false;

void Frame_properties::save_file(ofstream& saving)
{
    saving.write((char*)&x, sizeof(int));
    saving.write((char*)&y, sizeof(int));
    saving.write((char*)&width, sizeof(int));
    saving.write((char*)&height, sizeof(int));
    saving.write((char*)&edges_x, sizeof(char));

    saving.write((char*)&edges_y, sizeof(char));
    saving.write((char*)&corner_ur, sizeof(char));
    saving.write((char*)&corner_dr, sizeof(char));
    saving.write((char*)&corner_ul, sizeof(char));
    saving.write((char*)&corner_dl, sizeof(char));

    saving.write(name.c_str(), name.size()+1);
    saving.write((char*)&absolute_x, sizeof(int));
    saving.write((char*)&absolute_y, sizeof(int));
}

void Main_frame::save_file(ofstream& saving, string& name_save, bool please_set_here_true)
{
    string name_frame;
    unsigned int number;

    if(please_set_here_true)
    {
        name_save=this->Frame_properties::unique_name();
        saving.write(name_save.c_str(), name_save.size()+1);
        name_frame=typeid(*this).name();
        saving.write(name_frame.c_str(), name_frame.size()+1);
    }

    this->Frame_properties::save_file(saving);

    saving.write((char*)&filling, sizeof(char));
    number=Board.size();
    saving.write((char*)&number, sizeof(unsigned int));
    number=Board[0].size();
    saving.write((char*)&number, sizeof(unsigned int));
    for (unsigned int i=0; i<Board.size(); i++)
    {
        for (unsigned int j=0; j<number; j++)
        {
            saving.write((char*)&Board[i][j], sizeof(char));
        }
    }

    number=children.size();
    saving.write((char*)&number, sizeof(unsigned int));

    for (unsigned int i=0; i<number; i++)
    {
        name_frame=children[i]->Frame_properties::unique_name();
        saving.write(name_frame.c_str(), name_frame.size()+1);
    }
}

void Main_frame::Frame::save_file(ofstream& saving, string& name_save, bool please_set_here_true)
{
    string name_frame;
    unsigned int number;

    if(please_set_here_true)
    {
        name_save=this->Frame_properties::unique_name();
        saving.write(name_save.c_str(), name_save.size()+1);
        name_frame=typeid(*this).name();
        saving.write(name_frame.c_str(), name_frame.size()+1);
    }

    this->Frame_properties::save_file(saving);

    name_frame=anchor->Frame_properties::unique_name();     // automatic conversion of the pointer
    saving.write(name_frame.c_str(), name_frame.size()+1);

    if(father!=nullptr)
    {
        name_frame=father->Frame_properties::unique_name();
        saving.write(name_frame.c_str(), name_frame.size()+1);
    }
    else
    {
        saving.write(name_frame.c_str(), name_frame.size()+1);      // if father is nullptr it`s saving the anchor name
    }

    number=children.size();
    saving.write((char*)&number, sizeof(unsigned int));
    for (unsigned int i=0; i<number; i++)
    {
        name_frame=children[i]->Frame_properties::unique_name();
        saving.write((char*)&name_frame, sizeof(unsigned int));
    }

    // name_list can be deduced from the pointers
}


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


//////////////////////////////

ostream& sizes(ostream& outgo)
{
    Main_frame::ostream_flag=true;
    return outgo;
}

void recursion_output(ostream& outgo, const Main_frame::Frame* frame, int number)
{
    number++;

    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        outgo << endl;
        for (int i=0; i<number; i++)
        {
            outgo << "  ";
        }
        outgo << "- " << frame->children[i]->name;
        if(Main_frame::ostream_flag)
        {
            outgo << " -> x: " << frame->children[i]->x << " y: " << frame->children[i]->y << " width: " << frame->children[i]->width \
                << " height: " << frame->children[i]->height;
        }
        recursion_output(outgo, frame->children[i], number);
    }
}

ostream& operator <<(ostream& outgo, const Main_frame::Frame& frame)
{
    outgo << "- " << frame.name;
    if(Main_frame::ostream_flag)
    {
        outgo << " -> x: " << frame.x << " y: " << frame.y << " width: " << frame.width << " height: " << frame.height;
    }

    recursion_output(outgo, &frame, 1);

    Main_frame::ostream_flag=false;
    return outgo;
}

ostream& operator <<(ostream& outgo, const Main_frame& frame)
{
    outgo << "- " << frame.name;
    if(Main_frame::ostream_flag)
    {
        outgo << " -> x: " << frame.x << " y: " << frame.y << " width: " << frame.width << " height: " << frame.height;
    }

    for (unsigned int i=0; i<frame.children.size(); i++)
    {
        outgo << endl;
        outgo << "  - " << frame.children[i]->name;
        if(Main_frame::ostream_flag)
        {
            outgo << " -> x: " << frame.children[i]->x << " y: " << frame.children[i]->y << " width: " << frame.children[i]->width \
                << " height: " << frame.children[i]->height;
        }
        recursion_output(outgo, frame.children[i], 1);
    }

    Main_frame::ostream_flag=false;
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

bool Main_frame::cast()
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

    return false;
}

bool Main_frame::Frame::cast()
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

    return false;
}

/*void recursion_cast(Main_frame::Frame* frame) // definition in different, changeable file
{
    frame->cast();
    for (unsigned int i=0; i<frame->children.size(); i++)
    {
        recursion_cast(frame->children[i]);
    }
}*/

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
    for (unsigned int i=0; i<f_frame->children.size(); i++)
    {
        if((f_frame->children[i])->father==f_frame)
        {
            return i;
        }
    }
    return -1;
}

int find_frame_in_children(Main_frame* m_frame)
{
    for (unsigned int i=0; i<m_frame->children.size(); i++)
    {
        if((m_frame->children[i])->anchor==m_frame)
        {
            return i;
        }
    }
    return -1;
}

bool Frame_properties::check_data \
(const int& pos_x, const int& pos_y, const int& f_width, const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl)
{
    if(pos_x<0||pos_y<0) return true;
    if(f_width<=0||f_height<=0) return true;
    if((f_edges_x!=DEFAULT_VOID&&f_edges_x<32)||(f_edges_y!=DEFAULT_VOID&&f_edges_y<32)) return true;
    if((f_corner_ur!=DEFAULT_VOID&&f_corner_ur<32)||(f_corner_dr!=DEFAULT_VOID&&f_corner_dr<32)) return true;
    if((f_corner_ul!=DEFAULT_VOID&&f_corner_ul<32)||(f_corner_dl!=DEFAULT_VOID&&f_corner_dl<32)) return true;

    return false;
}

bool Main_frame::Frame::check_shrink(const int& f_width, const int& f_height)
{
     if(f_width<=0||f_height<=0) return true;
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
    if(f_width<=0||f_height<=0) return true;
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
    if(f_width<=0||f_height<=0) return true;
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
    if(new_x<0||new_y<0)
    {
        return true;
    }
    if(father==nullptr)
    {
        if((new_x+f_width>anchor->width)||(new_y+f_height>anchor->height))
        {
            return true;
        }
    }
    else
    {
        if((new_x+f_width>father->width)||(new_y+f_height>father->height))
        {
            return true;
        }
    }

    return check_expand(f_width, f_height)||check_shrink(f_width, f_height);
}

bool Main_frame::Frame::check_names(string& this_name)
{
    if(this_name.size()==0)
    {
        return true;
    }
    bool OK=true;
    for (unsigned int i=0; i<this_name.size(); i++)
    {
        if(this_name[i]==ILLEGAL_CHAR||this_name[i]==ILLEGAL_CHAR2)
        {
            return true;
        }
        if(this_name[i]!=' ') OK=false;
    }
    if(OK)
    {
        return true;
    }
    if(father!=nullptr)
    {
        auto it=find(father->name_list.begin(), father->name_list.end(), this_name);
        if((!father->name_list.empty())&&it!=father->name_list.end())
        {
            return true;
        }

    }
    else
    {
        auto it=find(anchor->name_list.begin(), anchor->name_list.end(), this_name);
        if((!anchor->name_list.empty())&&it!=anchor->name_list.end())
        {
            return true;
        }
    }
    return false;
}

bool Main_frame::check_data \
(const int& pos_x, const int& pos_y, const int& f_width,const int& f_height, const char& f_edges_x, const char& f_edges_y, \
const char& f_corner_ur, const char& f_corner_dr, const char& f_corner_ul, const char& f_corner_dl, const char& f_filling)
{
    if(f_filling!=DEFAULT_VOID&&f_filling<32)
    {
        return true;
    }
    return Frame_properties::check_data(pos_x, pos_y, f_width, f_height, f_edges_x, f_edges_y, f_corner_ur, f_corner_dr, f_corner_ul, f_corner_dl)||check_shrink(f_width, f_height);
}

//constructor
Frame_properties::Frame_properties \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, string f_name, const char& filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl)
:x(position_x), y(position_y), width(M_f_width), height(M_f_height), edges_x(filling_edges_x), edges_y(filling_edges_y), corner_ur(filling_corner_ur), \
corner_dr(filling_corner_dr), corner_ul(filling_corner_ul), corner_dl(filling_corner_dl), name(f_name) {}

Frame_properties::~Frame_properties() {};

//constructor
Main_frame::Main_frame \
(const int& position_x, const int& position_y, const int& M_f_width, const int& M_f_height, string f_name, \
const char&filling_edges_x, const char& filling_edges_y, const char& filling_corner_ur, \
const char& filling_corner_dr, const char& filling_corner_ul, const char& filling_corner_dl, \
const char& main_filling)
:Frame_properties(position_x, position_y, M_f_width, M_f_height, f_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, \
filling_corner_ul, filling_corner_dl), filling(main_filling)
{
    if(check_data(x, y, width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl, filling))
    {
        width=0;
        height=0;
        x=0;
        y=0;
        absolute_x=0;
        absolute_y=0;
        throw invalid_argument("Wrong data");
        //throw this;
    }

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

    absolute_x=0;       // must be because of saving file
    absolute_y=0;
}

Main_frame::~Main_frame()
{
    while(children.size()!=0)
    {
        delete children[0];
    }
}

Main_frame::Frame::~Frame()
{
    while(children.size()!=0)
    {
        delete children[0];
    }

    if(father==nullptr)
    {
        auto it=find(anchor->name_list.begin(), anchor->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==anchor->name_list.end())
        {
            clog << "ERROR: Main_frame::Frame::~Frame(). No name in name_list found" << this->name << endl;
        }
        #endif // DEBUG
        anchor->name_list.erase(it);

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
        auto it=find(father->name_list.begin(), father->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==father->name_list.end())
        {
            clog << "ERROR: Main_frame::Frame::~Frame(). No name in name_list found" << this->name << endl;
        }
        #endif // DEBUG
        father->name_list.erase(it);

        for (unsigned int i=0; i<father->children.size(); i++)
        {
            if(father->children[i]==this)
            {
                father->children.erase((father->children.begin()+i));
                break;
            }
        }
    }

    while(children.size()!=0)
    {
        delete children[0];
    }

}

// Copy constructor
/*Main_frame::Main_frame (const Main_frame& main_frame)
:Frame_properties(main_frame.x, main_frame.y, main_frame.width, main_frame.height, main_frame.name, main_frame.edges_x, main_frame.edges_y, \
main_frame.corner_ur, main_frame.corner_dr, main_frame.corner_ul, main_frame.corner_dl), filling(main_frame.filling) {}*/

//constructor
Main_frame::Frame::Frame \
(Main_frame* window, nullptr_t, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, string f_name, const char& filling_edges_x, \
 const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, \
 const char& filling_corner_ul, const char& filling_corner_dl)
:Frame_properties(pos_x, pos_y, F_width, F_height, f_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, \
filling_corner_dl), anchor(window), father(nullptr)
{
    if(Frame_properties::check_data(x, y, width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl)||check_data(pos_x, pos_y, F_width, F_height)||check_names(name))
    {
        /*(anchor->children).push_back(this);
        anchor->name_list.push_back(name);*/
        throw invalid_argument("Wrong data");
        //throw this;
    }
    else
    {
        absolute_x=x;
        absolute_y=y;

        (anchor->children).push_back(this);
        anchor->name_list.push_back(name);
    }
}

//constructor
Main_frame::Frame::Frame \
(Main_frame* window, Frame* f_father, const int& pos_x, const int& pos_y, const int& F_width, const int& F_height, string f_name, const char& filling_edges_x, \
 const char& filling_edges_y, const char& filling_corner_ur, const char& filling_corner_dr, \
 const char& filling_corner_ul, const char& filling_corner_dl)
:Frame_properties(pos_x, pos_y, F_width, F_height, f_name, filling_edges_x, filling_edges_y, filling_corner_ur, filling_corner_dr, filling_corner_ul, \
filling_corner_dl), anchor(window), father(f_father)
{
    if(Frame_properties::check_data(x, y, width, height, edges_x, edges_y, corner_ur, corner_dr, corner_ul, corner_dl)||check_data(pos_x, pos_y, F_width, F_height)||check_names(name))
    {
        /*(father->children).push_back(this);
        father->name_list.push_back(name);*/
        throw invalid_argument("Wrong data");
        //throw this;
    }
    else
    {
        absolute_x=father->absolute_x+x;
        absolute_y=father->absolute_y+y;

        (father->children).push_back(this);
        father->name_list.push_back(name);
    }
}

//Copy constructor
/*Main_frame::Frame::Frame(const Frame& frame)
:Frame_properties(frame.x, frame.y, frame.width, frame.height, frame.name, frame.edges_x, frame.edges_y, frame.corner_ur, frame.corner_dr, frame.corner_ul, \
frame.corner_dl), anchor(frame.anchor)
{
    for (unsigned int i=0; i<)
}*/

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
    };
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

bool Main_frame::move(const int& shift_x, const int& shift_y)  // relative path, it can be negative
{
    if(x+shift_x<0||y+shift_y<0)
    {
        return true;
    }

    x=x+shift_x;
    y=y+shift_y;

    return false;
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

int Frame_properties::get_x()
{
    return x;
}

int Frame_properties::get_y()
{
    return y;
}

int Frame_properties::f_width()
{
    return width;
}

int Frame_properties::f_height()
{
    return height;
}

bool Frame_properties::change_name(string& new_name)
{
    name=new_name;
    return false;
}

bool check_swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame)
{
    if(f_frame->father!=nullptr)
    {
        for (unsigned int i=0; i<f_frame->father->name_list.size(); i++)  // if no name conflict in neighborhood
        {
            if(find(f_frame->father->name_list.begin(), f_frame->father->name_list.end(), s_frame->name)==f_frame->father->name_list.end())
            {
                return true;
            }
        }
    }
    else
    {
        for (unsigned int i=0; i<f_frame->anchor->name_list.size(); i++)  // if no name conflict in neighborhood
        {
            if(find(f_frame->anchor->name_list.begin(), f_frame->anchor->name_list.end(), s_frame->name)==f_frame->anchor->name_list.end())
            {
                return true;
            }
        }
    }

    if(s_frame->father!=nullptr)
    {
        for (unsigned int i=0; i<s_frame->father->name_list.size(); i++)  // if no name conflict in neighborhood
        {
            if(find(s_frame->father->name_list.begin(), s_frame->father->name_list.end(), f_frame->name)==s_frame->father->name_list.end())
            {
                return true;
            }
        }
    }
    else
    {
        for (unsigned int i=0; i<s_frame->anchor->name_list.size(); i++)  // if no name conflict in neighborhood
        {
            if(find(s_frame->anchor->name_list.begin(), s_frame->anchor->name_list.end(), f_frame->name)==s_frame->anchor->name_list.end())
            {

                return true;
            }
        }
    }

    if(f_frame==s_frame)
    {
        return true;
    }
    if(f_frame->check_expand(s_frame->width, s_frame->height)||s_frame->check_expand(f_frame->width, f_frame->height))
    {
        return true;
    }
    if(f_frame->check_shrink(s_frame->width, s_frame->height)||s_frame->check_shrink(f_frame->width, f_frame->height))
    {
        return true;
    }
    return false;
}

void change_fatherChildren_name_list_swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, const int& father1, const int& father2)
{
    list<string>::iterator it;
    Main_frame::Frame* tmp_frame;
    Main_frame* tmp_mframe;
    //string s_tmp, s_tmp2;

    if(f_frame->father==nullptr)
    {
        tmp_mframe=f_frame->anchor;
        tmp_mframe->children[father1]=s_frame;

        it=find(tmp_mframe->name_list.begin(), tmp_mframe->name_list.end(), f_frame->name);
        #ifdef DEBUG
        if(it!=tmp_mframe->name_list.end())
        {
            #endif
            tmp_mframe->name_list.erase(it);
            #ifdef DEBUG
        }
        else
        {
            clog << "Error in: bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, bool all_children_too). Do not find name in name_list of anchor " << s_frame->name << endl;
        }
        #endif
    }
    else
    {
        tmp_frame=f_frame->father;
        tmp_frame->children[father1]=s_frame;

        it=find(tmp_frame->name_list.begin(), tmp_frame->name_list.end(), f_frame->name);
        #ifdef DEBUG
        if(it!=tmp_frame->name_list.end())
        {
            #endif
            tmp_frame->name_list.erase(it);
            #ifdef DEBUG
        }
        else
        {
            clog << "Error in: bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, bool all_children_too). Do not find name in name_list of father " << s_frame->name << endl;
        }
        #endif

    }

    if(s_frame->father==nullptr)
    {
        tmp_mframe=s_frame->anchor;
        tmp_mframe->children[father2]=f_frame;

        it=find(tmp_mframe->name_list.begin(), tmp_mframe->name_list.end(), s_frame->name);
        #ifdef DEBUG
        if(it!=tmp_mframe->name_list.end())
        {
            #endif
            tmp_mframe->name_list.push_back(f_frame->name);
            tmp_mframe->name_list.erase(it);
            #ifdef DEBUG
        }
        else
        {
            clog << "Error in: bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, bool all_children_too). Do not find name in name_list of anchor " << f_frame->name << endl;
        }
        #endif

    }
    else
    {
        tmp_frame=s_frame->father;
        tmp_frame->children[father2]=f_frame;

        it=find(tmp_frame->name_list.begin(), tmp_frame->name_list.end(), s_frame->name);
        #ifdef DEBUG
        if(it!=tmp_frame->name_list.end())
        {
            #endif
            tmp_frame->name_list.push_back(f_frame->name);
            tmp_frame->name_list.erase(it);
            #ifdef DEBUG
        }
        else
        {
            clog << "Error in: bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, bool all_children_too). Do not find name in name_list of anchor " << f_frame->name << endl;
        }
        #endif

    }

    if(f_frame->father==nullptr)
    {
        f_frame->anchor->name_list.push_back(s_frame->name);
    }
    else
    {
        f_frame->father->name_list.push_back(s_frame->name);
    }
    /*if(s_frame->father==nullptr)
    {
        s_frame->anchor->name_list.push_back(f_frame->name);
    }
    else
    {
        s_frame->father->name_list.push_back(f_frame->name);
    }*/

    //change fathers
    if(f_frame->father==nullptr)
    {
        if(s_frame->father!=nullptr)
        {
            f_frame->father=s_frame->father;
            s_frame->father=nullptr;
        }
        // else: all father are nullptr
    }
    else
    {
        if(s_frame->father==nullptr)
        {
            s_frame->father=f_frame->father;
            f_frame->father=nullptr;
        }
        else
        {
            tmp_frame=s_frame->father;
            s_frame->father=f_frame->father;
            f_frame->father=tmp_frame;
        }
    }
}

bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame)   // important method, end in (0,0), reset position
{
    int tmp=find_frame_in_father(f_frame), tmp2=find_frame_in_father(s_frame);
    int shift_x1, shift_x2, shift_y1, shift_y2;
    list<string>::iterator it;
    string s_tmp;

    #ifdef DEBUG
    if(tmp==-1||tmp2==-1)
    {
        clog << "ERROR: bool swap(Main_frame::Frame* f_frame, Main_frame::Frame* s_frame, bool all_children_too). No father found" << endl;
        return true;
    }
    #endif

    if(check_swap(f_frame, s_frame))
    {
        return true;
    }

    change_fatherChildren_name_list_swap(f_frame, s_frame, tmp, tmp2);

    tmp=f_frame->absolute_x;
    tmp2=f_frame->absolute_y;

    /*shift_x1=(s_frame->x-s_frame->absolute_x)-(f_frame->x);
    shift_y1=(s_frame->y-s_frame->absolute_y)-(f_frame->y);
    shift_x2=(f_frame->x-f_frame->absolute_x)-(s_frame->x);
    shift_y2=(f_frame->y-f_frame->absolute_y)-(s_frame->y);
*/

    shift_x1=(s_frame->absolute_x-f_frame->absolute_x)-(s_frame->x);
    shift_y1=(s_frame->absolute_y-f_frame->absolute_y)-(s_frame->y);
    shift_x2=(f_frame->absolute_x-s_frame->absolute_x)-(f_frame->x);
    shift_y2=(f_frame->absolute_y-s_frame->absolute_y)-(f_frame->y);

    #ifdef DEBUG
    cout << "swap, shift_x and shift_y" << endl;
    cout << f_frame->absolute_x-s_frame->absolute_x-f_frame->x << " " << f_frame->absolute_y-s_frame->absolute_y-f_frame->y << endl;
    cout << s_frame->absolute_x-tmp-s_frame->x << " " << s_frame->absolute_y-tmp2-s_frame->y << endl;
    #endif
    //parent_child_fitting(f_frame, f_frame->absolute_x-s_frame->absolute_x-f_frame->x, f_frame->absolute_y-s_frame->absolute_y-f_frame->y);
    //parent_child_fitting(s_frame, s_frame->absolute_x-tmp-s_frame->x, s_frame->absolute_y-tmp2-s_frame->y);
    parent_child_fitting(f_frame, shift_x1, shift_y1);
    parent_child_fitting(s_frame, shift_x2, shift_y2);

    f_frame->x=0;
    f_frame->y=0;
    s_frame->x=0;
    s_frame->y=0;

    return false;
}

bool Main_frame::Frame::move_to(Main_frame::Frame* here, const int& where)        // add at to the pointer children, reset to (0,0)
{
    if(this==here)
    {
        return true;
    }

    int itmp=find_frame_in_father(this);
    int shift_x, shift_y;
    list<string>::iterator it;

    #ifdef DEBUG
    if(itmp==-1)
    {
        return true;
    }
    #endif

    if(here->width<width||here->height<height)
    {
        return true;
    }

    // move frame
    if(father!=nullptr)
    {
        it=find(father->name_list.begin(), father->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==father->name_list.end())
        {
            clog << "ERROR: bool Main_frame::Frame::move_to(Main_frame* here, const int& where=-1). Unable to find name in name_list" << this->name << endl;
        }
        #endif // DEBUG
        father->name_list.erase(it);
        father->children.erase((father->children).begin()+itmp);
    }
    else
    {
        it=find(anchor->name_list.begin(), anchor->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==anchor->name_list.end())
        {
            clog << "ERROR: bool Main_frame::Frame::move_to(Main_frame* here, const int& where=-1). Unable to find name in name_list" << this->name << endl;
        }
        #endif // DEBUG
        anchor->name_list.erase(it);
        anchor->children.erase((anchor->children).begin()+itmp);
    }

    father=here;
    itmp=where;

    if(itmp<0||(unsigned int)itmp>=here->children.size())
    {
        itmp=here->children.size()-1;
    }

    if(itmp<0)     // may be ch.size=0
    {
        (here->children).push_back(this);
    }
    else
    {
        (here->children).insert(here->children.begin()+itmp, this);
    }
    here->name_list.push_back(this->name);
    this->father=here;

    shift_x=here->absolute_x-absolute_x;
    shift_y=here->absolute_y-absolute_y;

    // reset position
    parent_child_fitting(this, shift_x, shift_y);
    x=0;
    y=0;

    return false;

}

bool Main_frame::Frame::move_to(Main_frame* here, const int& where)
{
    int itmp=where, itmp2=find_frame_in_father(this);
    int shift_x, shift_y;
    list<string>::iterator it;

    #ifdef DEBUG
    if(itmp2==-1)
    {
        return true;
    }
    #endif

    if(here->width<width||here->height<height)
    {
        return true;
    }

    // erase info
    if(father!=nullptr)
    {
        it=find(father->name_list.begin(), father->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==father->name_list.end())
        {
            clog << "ERROR: bool Main_frame::Frame::move_to(Main_frame* here, const int& where=-1). Unable to find name in name_list" << this->name << endl;
        }
        #endif // DEBUG
        father->name_list.erase(it);
        father->children.erase((father->children).begin()+itmp2);
    }
    else
    {
        it=find(anchor->name_list.begin(), anchor->name_list.end(), this->name);
        #ifdef DEBUG
        if(it==anchor->name_list.end())
        {
            clog << "ERROR: bool Main_frame::Frame::move_to(Main_frame* here, const int& where=-1). Unable to find name in name_list" << this->name << endl;
        }
        #endif // DEBUG
        anchor->name_list.erase(it);
        anchor->children.erase((anchor->children).begin()+itmp2);
    }

    if(itmp<0||(unsigned int)where>=here->children.size())
    {
        itmp=here->children.size()-1;
    }

    if(itmp<0)     // may be ch.size=0
    {
        itmp=0;
    }


    (here->children).insert(here->children.begin()+itmp, this);
    here->name_list.push_back(this->name);
    this->father=nullptr;
    this->anchor=here;

    shift_x=-absolute_x;
    shift_y=-absolute_y;

    // reset position
    parent_child_fitting(this, shift_x, shift_y);
    x=0;
    y=0;

    return false;
}

bool Main_frame::change_name(string& new_name)
{
    for (unsigned int i=0; i<new_name.size(); i++)
    {
				if(new_name[i]==ILLEGAL_CHAR||new_name[i]==ILLEGAL_CHAR2)
				{
						return true;
				}
    }

    name=new_name;
    return false;
}

bool Main_frame::Frame::change_name(string& new_name)
{
    if(new_name==name)
    {
        return true;
    }

		for (unsigned int i=0; i<new_name.size(); i++)
		{
				if(new_name[i]==ILLEGAL_CHAR||new_name[i]==ILLEGAL_CHAR2)
				{
						return true;
				}
		}

		list<string>::iterator it;

    if(father!=nullptr)
    {
        if(find(father->name_list.begin(), father->name_list.end(), new_name)!=father->name_list.end())
        {
            return true;
        }

        if((it=find(father->name_list.begin(), father->name_list.end(), this->name))!=father->name_list.end())
        {
						father->name_list.erase(it);
						father->name_list.push_back(new_name);
        }
        #ifdef DEBUG
        else
        {
            clog << "ERROR: bool Main_frame::Frame::change_name(string& new_name). Cannot find name in father->namelist" << endl;
        }
        #endif
    }
    else
    {
        if(find(anchor->name_list.begin(), anchor->name_list.end(), new_name)!=anchor->name_list.end())
        {
            return true;
        }

        if((it=find(anchor->name_list.begin(), anchor->name_list.end(), this->name))!=anchor->name_list.end())
        {
						anchor->name_list.erase(it);
						anchor->name_list.push_back(new_name);
        }
        #ifdef DEBUG
        else
        {
            clog << "ERROR: bool Main_frame::Frame::change_name(string& new_name). Cannot find name in father->namelist" << endl;
        }
        #endif
    }

    this->name=new_name;

    return false;
}

Main_frame::Frame* find_by_string(Main_frame* frame, string& str)
{
    if(frame==nullptr)
    {
        return nullptr;
    }
    for(unsigned int i=0; i<frame->children.size(); i++)
    {
        if(frame->children[i]->name==str)
        {
            return frame->children[i];
        }
    }
    return nullptr;
}

Main_frame::Frame* find_by_string(Main_frame::Frame* frame, string& str)
{
    if(frame==nullptr)
    {
        return nullptr;
    }
    for(unsigned int i=0; i<frame->children.size(); i++)
    {
        if(frame->children[i]->name==str)
        {
            return frame->children[i];
        }
    }
    return nullptr;
}

Main_frame::Frame* go_back_frame(Main_frame::Frame* frame)
{
    if(frame==nullptr)
    {
        return nullptr;
    }
    return frame->father;
}

Main_frame* go_back_mFrame(Main_frame::Frame* frame)
{
    if(frame==nullptr)
    {
        return nullptr;
    }
    if(frame->father==nullptr)
    {
        return frame->anchor;
    }
    else
    {
        return nullptr;
    }
}

void Main_frame::Frame::where_are_you()
{
    cout << this->name << "~";
    if(this->father!=nullptr)
    {
        this->father->where_are_you();
    }
    else
    {
        cout << this->anchor->name << endl;
    }
}


#endif // MAIN_FRAME_CPP
