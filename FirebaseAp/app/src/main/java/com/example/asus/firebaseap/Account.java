package com.example.asus.firebaseap;

/**
 * Created by ASUS on 22-Nov-17.
 */

public class Account
{
    public int id;
    public String number;
    public String cardID;
    public String firstName;
    public String lastName;

    public Account()
    {

    }

    public Account(int id,String firstName,String lastName,String number )
    {
        this.id=id;
        this.number=number;
        this.cardID="";
        this.firstName=firstName;
        this.lastName=lastName;
    }

}
