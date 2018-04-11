package com.example.asus.firebaseap;

import java.util.ArrayList;

/**
 * Created by ASUS on 22-Nov-17.
 */

public class Menu
{
    public int year;
    public int month;
    public int day;

    public ArrayList<String> items=new ArrayList<String>();


    public Menu()
    {

    }

    public Menu(int day,String[] items)
    {
        this.day=day;
        this.items.clear();

        for (int i=0;i<5;i++)
        {
            this.items.add(items[i]);
        }
    }
}
