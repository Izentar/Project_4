#ifndef TEST_CLASS_CPP
#define TEST_CLASS_CPP

#include "test_class.h"

void cut_string(string& name)
{
    for (int i=name.size()-1; i>=0; i--)
    {
        if(name[i]==' ')
        {
            name.pop_back();
        }
        else
        {
            break;
        }
    }
}

bool Menu::give_data(int& pos_x, int& pos_y, int& width, int& height, string& name, char& edges_x, char& edges_y, char& ur, char& dr, char &ul, char& dl)
{
    cout << "Give pos_x: ";
    cin >> pos_x;
    cout << "Give pos_y: ";
    cin >> pos_y;
    cout <<"Give width: ";
    cin >> width;
    cout << "Give height: ";
    cin >> height;
    cout << "Give name to frame: ";
    //cin.sync();
    //cin.clear();

    cin >> name;
    //getline(cin, name);
    //cin.ignore(1000, '\n');
    cut_string(name);
    /*if(name.size()==0)
    {
        return true;
    }*/
    cout << "Give edges_x: ";
    cin >> edges_x;
    cout << "Give edges_y: ";
    cin >> edges_y;
    cout << "Give upper right corner: ";
    cin >> ur;
    cout << "Give bottom right corner: ";
    cin >> dr;
    cout << "Give upper left corner: ";
    cin >> ul;
    cout << "Give bottom left corner: ";
    cin >> dl;

    return false;
}

bool Menu::lack_main_frame()
{
    if(basic_frame==nullptr)
    {
        cout << "First create a main frame" << endl;
        return true;
    }
    return false;
}

bool Menu::go()
{
    if(lack_main_frame())
    {
        return true;
    }
    cout << "Where? ";
    cin >> tmp;
    //getline(cin, tmp);
    cut_string(tmp);

    if(actual_frame!=nullptr)
    {
        if((new_frame=find_by_string(actual_frame, tmp))!=nullptr)
        {
            actual_frame=new_frame;
            act_basic_frame=nullptr;
        }
        else
        if((new_frame=find_by_string(act_basic_frame, tmp))!=nullptr)
        {
            actual_frame=new_frame;
            act_basic_frame=nullptr;
        }
        else
        {
            cout << "There is no this frame" << endl;
            return true;
        }
    }
    else
    {
        if((new_frame=find_by_string(act_basic_frame, tmp))!=nullptr)
        {
            actual_frame=new_frame;
            act_basic_frame=nullptr;
        }
        else
        if((new_frame=find_by_string(act_basic_frame, tmp))!=nullptr)
        {
            actual_frame=new_frame;
            act_basic_frame=nullptr;
        }
        else
        {
            cout << "There is no this frame" << endl;
            return true;
        }
    }
    return false;
}

bool Menu::back()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(actual_frame!=nullptr)
    {
        if((new_frame=go_back_frame(actual_frame))!=nullptr)
        {
            actual_frame=new_frame;
            act_basic_frame=nullptr;
        }
        else
        {
            new_basic_frame=go_back_mFrame(actual_frame);
            act_basic_frame=new_basic_frame;
            actual_frame=nullptr;
        }
    }
    else
    {
        act_basic_frame=basic_frame;
    }
    return false;
}

bool Menu::move_from()
{
    if(lack_main_frame())
    {
        return true;
    }
    cout << "In which position? ";
    cin >> i2;
    if(remember_frame!=nullptr)
    {
        if(actual_frame!=nullptr)
        {
            if(actual_frame->move_to(remember_frame, i2))
            {
                cout << "BAD MOVE_TO" << endl;
                return true;
            }
        }
        else
        {
            cout << "You cannot move the main frame" << endl;
            return true;
        }
    }
    else
    if(remember_basic_frame!=nullptr)
    {
        if(actual_frame!=nullptr)
        {
            if(actual_frame->move_to(remember_basic_frame, i2))
            {
                cout << "BAD MOVE_TO" << endl;
                return true;
            }
        }
        else
        {
            cout << "You cannot move the main frame" << endl;
            return true;
        }
    }
    else
    {
        cout << "Cannot do it. There is not any remembered pointer" << endl;
        return true;
    }
    return false;
}

bool Menu::move()
{
    if(lack_main_frame())
    {
        return true;
    }
    cout << "Relative position x: ";
    cin >> i;
    cout << "Relative position y: ";
    cin >> i2;
    if(actual_frame!=nullptr)
    {
        if(actual_frame->move(i, i2))
        {
            cout << "BAD MOVE" << endl;
            return true;
        }
    }
    else
    {
        if(act_basic_frame->move(i, i2))
        {
            cout << "BAD MOVE" << endl;
            return true;
        }
    }
    return false;
}

bool Menu::resize()
{
    if(lack_main_frame())
    {
        return true;
    }
    cout << "New width: ";
    cin >> i;
    cout << "New height: ";
    cin >> i2;
    if(actual_frame!=nullptr)
    {
        if(actual_frame->resize(i, i2))
        {
            cout << "BAD RESIZE" << endl;
            return true;
        }
    }
    else
    {
        if(act_basic_frame->resize(i, i2))
        {
            cout << "BAD RESIZE" << endl;
            return true;
        }
    }
    return false;
}

bool Menu::remember_frame_func()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(actual_frame!=nullptr)
    {
        remember_frame=actual_frame;
        remember_basic_frame=nullptr;
    }
    else
    {
        remember_basic_frame=act_basic_frame;
        remember_frame=nullptr;
    }
    return false;
}

bool Menu::show()
{
    if(lack_main_frame())
    {
        return true;
    }

    basic_frame->all_cast();
    basic_frame->show();

    return false;
}

bool Menu::save()
{
    if(lack_main_frame())
    {
        return true;
    }

    if(basic_frame->save_to_file_all())
    {
        cout << "BAD SAVE" << endl;
        return true;
    }

    return false;
}

bool Menu::delete_this()
{
    if(actual_frame!=nullptr)
    {
        if((new_frame=go_back_frame(actual_frame))!=nullptr)
        {
            delete actual_frame;
            actual_frame=new_frame;

        }
        else
        {
            new_basic_frame=go_back_mFrame(actual_frame);
            delete actual_frame;
            actual_frame=nullptr;
            act_basic_frame=new_basic_frame;
        }

    }
    else
    {
        delete act_basic_frame;
        basic_frame=nullptr;
        act_basic_frame=nullptr;
        actual_frame=nullptr;

    }
    remember_basic_frame=nullptr;
    remember_frame=nullptr;
    return false;
}

bool Menu::hierarchy()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(actual_frame!=nullptr)
    {
        cout << *actual_frame << endl;
    }
    else
    {
        cout <<*act_basic_frame << endl;
    }
    return false;
}

bool Menu::hierarchy_sizes()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(actual_frame!=nullptr)
    {
        cout << sizes << *actual_frame << endl;
    }
    else
    {
        cout << sizes << *act_basic_frame << endl;
    }
    return false;
}

bool Menu::where()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(actual_frame!=nullptr)
    {
        actual_frame->where_are_you();
    }
    else
    {
        cout << "You are in main frame" << endl;
    }
    return false;
}

bool Menu::swap_menu()
{
    if(lack_main_frame())
    {
        return true;
    }
    if(remember_frame!=nullptr&&actual_frame!=nullptr)
    {
        new_frame=actual_frame;
        if(swap(remember_frame, actual_frame))
        {
            cout << "BAD SWAP" << endl;
            return true;
        }
        actual_frame=new_frame;
    }
    else
    {
        cout << "Remember the frame or change destination!" << endl;
        return true;
    }
    return false;
}

bool Menu::inscription()
{
    if(lack_main_frame())
    {
        return true;
    }

    cout << "Create new frame:" << endl;
    if(give_data(i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6))
    {
        cout << "Wrong data" << endl;
        return true;
    }
    cout << "What kind of inscription to fill in?" << endl;
    cin >> tmp1;
    //getline(cin, tmp1);
    cut_string(tmp1);

    try
    {
        if(actual_frame!=nullptr) new_frame=new Frame_inscription(basic_frame, actual_frame, tmp1, i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6);
        else new_frame=new Frame_inscription(basic_frame, nullptr, tmp1, i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6);
    }
    catch(invalid_argument invalid)
    {
        cout << "Something went wrong in creating frame " << invalid.what() << endl;
        //delete new_frame;
        new_frame=nullptr;
        return true;
    }
    if(new_frame!=nullptr) frame_buff.push_back(new_frame);

    return false;
}

bool Menu::fulfillment()// !!!!
{
    if(lack_main_frame())
    {
        return true;
    }

    cout << "Create new frame:" << endl;
    if(give_data(i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6))
    {
        cout << "Wrong data" << endl;
        return true;
    }
    cout << "What kind of sign to fill in?" << endl;
    cin >> c;

    try
    {
        if(actual_frame!=nullptr)
        {
            new_frame=new Frame_fulfillment(basic_frame, actual_frame,  i, i1, i2, i3, c, tmp, c1, c2, c3, c4, c5, c6);
        }
        else
        {
            new_frame=new Frame_fulfillment(basic_frame, nullptr,  i, i1, i2, i3, c, tmp, c1, c2, c3, c4, c5, c6); // lost??????
        }
    }
    catch(invalid_argument invalid)
    {
        cout << "Something went wrong in creating frame " << invalid.what() << endl;
        //delete new_frame;
        new_frame=nullptr;
        return true;
    }
    if(new_frame!=nullptr) frame_buff.push_back(new_frame);

    return false;
}

bool Menu::frame()
{
    if(basic_frame==nullptr)
    {
        cout << "Need to create new board. Give data:" << endl;
        if(give_data(i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6))
        {
            cout << "Wrong data" << endl;
            return true;
        }
        try
        {
            basic_frame=new Main_frame(i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6);
        }
        catch(invalid_argument& invalid)
        {
            cout << "Something went wrong in creating frame " << invalid.what() << endl;
            //delete basic_frame;
            basic_frame=nullptr;
            return true;
        }
        act_basic_frame=basic_frame;
    }
    else
    {
        cout << "Create new frame:" << endl;
        if(give_data(i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6))
        {
            cout << "Wrong data" << endl;
            return true;;
        }

        try
        {
            if(actual_frame!=nullptr)
            {
                new_frame=new Main_frame::Frame(basic_frame, actual_frame,  i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6);
            }
            else
            {
                new_frame=new Main_frame::Frame(basic_frame, nullptr,  i, i1, i2, i3, tmp, c1, c2, c3, c4, c5, c6);
            }
        }
        catch(invalid_argument invalid)
        {
            cout << "Something went wrong in creating frame " << invalid.what() << endl;
            //delete new_frame;
            new_frame=nullptr;
            return true;
        }
        if(new_frame!=nullptr) frame_buff.push_back(new_frame);
    }
    return false;
}

void Menu::cleaning()
{
    if(lack_main_frame())
    {
        actual_frame=nullptr;
        act_basic_frame=nullptr;
        return;
    }
    if(actual_frame==nullptr)
    {
        if(act_basic_frame==nullptr)
        {
            clog<< "ERROR: void Menu::cleaning(). All actual pointers are nullptr" << endl;
        }
    }
    else
    {
        if(act_basic_frame!=nullptr)
        {
            clog<< "ERROR: void Menu::cleaning(). All actual pointers point to something" << endl;
        }
    }
    new_basic_frame=nullptr;
    new_frame=nullptr;

    buff.clear();
    tmp.clear();
    tmp1.clear();
}



void Menu::menu_start()
{
    /*
    if actual_frame!=nullptr => act_basic_frame=nullptr
    if act_basic_frame!=nullptr => actual_frame=nullptr
    */
    while(1)
    {
        cout << endl;
        cout << "# ";

        cin >> buff;
        //getline(cin, buff);
        cut_string(buff);

        if(buff=="Frame"||buff=="frame"||buff=="new_frame")
        {
            frame();
        }
        else
        if(buff=="Full frame"||buff=="full frame"||buff=="ful"||buff=="fulfillment")
        {
            fulfillment();
        }
        else
        if(buff=="Inscription"||buff=="inscription"||buff=="label")
        {
            inscription();
        }
        else
        if(buff=="swap")
        {
            swap_menu();
        }
        else
        if(buff=="move_from")
        {
            move_from();
        }
        else
        if(buff=="go")
        {
            go();
        }
        else
        if(buff=="back")
        {
            back();
        }
        else
        if(buff=="move")
        {
            move();
        }
        else
        if(buff=="resize")
        {
            resize();
        }
        else
        if(buff=="remember_frame")
        {
            remember_frame_func();
        }
        else
        if(buff=="show")
        {
            show();
        }
        else
        if(buff=="save")
        {
            save();
        }
        else
        if(buff=="delete")
        {
            delete_this();
        }
        else
        if(buff=="hierarchy")
        {
            hierarchy();
        }
        else
        if(buff=="where")
        {
            where();
        }
        else
        if(buff=="exit")
        {
            break;
        }
        else
        if(buff=="hier_sizes")
        {
            hierarchy_sizes();
        }
        else
        {
            cout << "Unknown command" << endl;
        }
        cleaning();

    }

    if(basic_frame!=nullptr)
    {
        delete basic_frame;
    }
}


#endif
