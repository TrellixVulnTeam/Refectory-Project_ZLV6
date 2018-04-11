package com.example.asus.firebaseap;

import java.util.ArrayList;

/**
 * Created by ASUS on 22-Nov-17.
 */

public class RefectoryDatabase
{
    public ArrayList<Account> accounts;
    public ArrayList<Process> processes;
    public ArrayList<Menu> menus;



    public RefectoryDatabase()
    {
        accounts=new ArrayList<Account>();
        processes=new ArrayList<Process>();
        menus=new ArrayList<Menu>();
    }
}
