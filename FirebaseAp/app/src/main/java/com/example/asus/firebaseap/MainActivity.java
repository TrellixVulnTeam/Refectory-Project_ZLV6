package com.example.asus.firebaseap;

import android.os.*;
import android.support.v4.content.Loader;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity
{
    Button button;
    TextView txtView;
    ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=(Button) findViewById(R.id.button2);
        listView=(ListView)findViewById(R.id.listView1);

        final FirebaseDatabase db=FirebaseDatabase.getInstance();
        final DatabaseReference refProcesses=db.getReference("Processes");
        final DatabaseReference refAccounts=db.getReference("Accounts");
        final DatabaseReference refMenus=db.getReference("Menus");

        final RefectoryDatabase rfDB=new RefectoryDatabase();


        Log.d("FDG_1a",String.valueOf(rfDB.accounts.size()));
        Log.d("FDG_1p",String.valueOf(rfDB.processes.size()));
        Log.d("FDG_1m",String.valueOf(rfDB.menus.size()));

        refProcesses.addValueEventListener(new ValueEventListener()
        {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot)
            {
                rfDB.processes.clear();

                for(DataSnapshot snapshot1:dataSnapshot.getChildren())
                {
                    Process process=new Process();
                    process.year=Integer.parseInt(snapshot1.getKey());
                    for(DataSnapshot snapshot2:snapshot1.getChildren())
                    {
                        process.month=Integer.parseInt(snapshot2.getKey());
                        for(DataSnapshot snapshot3:snapshot2.getChildren())
                        {
                            process.day=Integer.parseInt(snapshot3.getKey());
                            for(DataSnapshot snapshot4:snapshot3.getChildren())
                            {
                                process.accountID=Integer.parseInt(snapshot4.getKey());
                                process.choiceCode=snapshot4.child("choiceCode").getValue().toString();
                                process.timeString=snapshot4.child("timeString").getValue().toString();
                                rfDB.processes.add(process);
                            }
                        }
                    }
                }
                Log.d("FDG_2p",String.valueOf(rfDB.processes.size()));
            }

            @Override
            public void onCancelled(DatabaseError databaseError)
            {

            }
        });



        refAccounts.addValueEventListener(new ValueEventListener()
        {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot)
            {
                rfDB.accounts.clear();

                for(DataSnapshot snapshot1:dataSnapshot.getChildren())
                {
                    Account account=new Account();
                    account.id=Integer.parseInt(snapshot1.getKey());
                    account.cardID=snapshot1.child("cardID").getValue().toString();
                    account.firstName=snapshot1.child("firstName").getValue().toString();
                    account.lastName=snapshot1.child("lastName").getValue().toString();
                    account.number=snapshot1.child("number").getValue().toString();

                    rfDB.accounts.add(account);
                }
                Log.d("FDG_2ac",String.valueOf(rfDB.accounts.size()));
            }

            @Override
            public void onCancelled(DatabaseError databaseError)
            {

            }
        });



        refMenus.addValueEventListener(new ValueEventListener()
        {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot)
            {
                rfDB.menus.clear();

                for(DataSnapshot snapshot1:dataSnapshot.getChildren())
                {
                    Menu menu=new Menu();
                    menu.year=Integer.parseInt(snapshot1.getKey());
                    for(DataSnapshot snapshot2:snapshot1.getChildren())
                    {
                        menu.month=Integer.parseInt(snapshot2.getKey());
                        for(DataSnapshot snapshot3:snapshot2.getChildren())
                        {
                            menu.day=Integer.parseInt(snapshot3.getKey());
                            for(DataSnapshot snapshot4:snapshot3.getChildren())
                            {
                                menu.items.add(snapshot4.getValue().toString());
                            }
                            rfDB.menus.add(menu);
                        }
                    }
                }
                Log.d("FDG_2m",String.valueOf(rfDB.menus.size()));
            }

            @Override
            public void onCancelled(DatabaseError databaseError)
            {

            }
        });





        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Log.d("FDG_3",String.valueOf(rfDB.accounts.size()));
            }
        });
    }
}





























/*RefectoryDatabase tmpDB=new RefectoryDatabase();
        tmpDB.accounts.add(new Account(0,"0","0","0"));
        tmpDB.accounts.add(new Account(1,"Enes","ŞANAL","G1312.99999"));
        tmpDB.accounts.add(new Account(2,"Emirhan","ÖZSOY","B1312.88888"));
        tmpDB.accounts.add(new Account(3,"Enes","İDRİSOĞLU","B1312.77777"));
        tmpDB.accounts.add(new Account(4,"Gülferide","CANDANER","G1449.11662"));
        tmpDB.accounts.add(new Account(5,"Oğuzbala","KARAHAN","B1568.17487"));
        tmpDB.accounts.add(new Account(6,"Ekinci","CİNDEMİR","B1419.19258"));
        tmpDB.accounts.add(new Account(7,"Hülâgü","GÜLDAMLA","G1835.18945"));
        tmpDB.accounts.add(new Account(8,"Lina","ALTAŞ","B1762.16899"));
        tmpDB.accounts.add(new Account(9,"Visam","BARBAROS","B1622.11183"));
        tmpDB.accounts.add(new Account(10,"Aça","KAMACI","G1185.18195"));
        tmpDB.accounts.add(new Account(11,"Gülten","TUNCER","G1925.18496"));
        tmpDB.accounts.add(new Account(12,"Güçmen","TARLAN","B1743.13243"));
        tmpDB.accounts.add(new Account(13,"Eşe","SAYGIN","G1835.19393"));
        tmpDB.accounts.add(new Account(14,"Öncel","TOKTAŞ","B1277.12395"));
        tmpDB.accounts.add(new Account(15,"Nurbolat","NACAROĞLU","B1973.11645"));
        tmpDB.accounts.add(new Account(16,"Idıkut","ULAŞ","B1582.19621"));
        tmpDB.accounts.add(new Account(17,"Nurhak","KARADAVUT","G1251.14668"));
        tmpDB.accounts.add(new Account(18,"Ayyarkın","GÖRÜNMEZ","G1282.13272"));
        tmpDB.accounts.add(new Account(19,"Mecburiye","ARACI","G1653.15685"));
        tmpDB.accounts.add(new Account(20,"Toku","EYLEN","G1866.18844"));
        tmpDB.accounts.add(new Account(21,"Nurzat","YÜCEL","B1578.13737"));
        tmpDB.accounts.add(new Account(22,"Bulca","KESER","G1316.14151"));
        tmpDB.accounts.add(new Account(23,"Boz","ARSLAN","G1912.18258"));
        tmpDB.accounts.add(new Account(24,"Mensup","ARIK","G1341.14219"));
        tmpDB.accounts.add(new Account(25,"Başat","TÜRKSOY","B1473.12187"));
        tmpDB.accounts.add(new Account(26,"Ülkinar","TİLBE","G1198.19215"));
        tmpDB.accounts.add(new Account(27,"Elmas","KIZANOĞLU","G1216.12762"));
        tmpDB.accounts.add(new Account(28,"Arzi","YILMAZ","B1716.18696"));
        tmpDB.accounts.add(new Account(29,"Temre","SÜMER","B1953.17563"));
        tmpDB.accounts.add(new Account(30,"Şahabeddin","BATGİ AZARKAN","G1856.19127"));
        tmpDB.accounts.add(new Account(31,"Turkay","KANDEMİR","G1712.15199"));
        tmpDB.accounts.add(new Account(32,"Odyak","YALÇIN","B1343.13515"));
        tmpDB.accounts.add(new Account(33,"Beser","CILIZ BASHEER","G1722.18773"));
        tmpDB.accounts.add(new Account(34,"Atilkan","ÇİFTÇİ","G1785.11884"));
        tmpDB.accounts.add(new Account(35,"Aliihsan","SARIÇİÇEK","B1112.11455"));
        tmpDB.accounts.add(new Account(36,"Rurten","ERDOĞAN","B1798.11641"));
        tmpDB.accounts.add(new Account(37,"Mükail","TOKER","B1737.14184"));
        tmpDB.accounts.add(new Account(38,"Temir","YURTLU","B1494.14642"));
        tmpDB.accounts.add(new Account(39,"Emrehan","YILDIRIM","G1568.19673"));
        tmpDB.accounts.add(new Account(40,"Sinangül","COŞKUNER","G1913.11334"));
        tmpDB.accounts.add(new Account(41,"Sonbay","ŞAHAN","G1494.16491"));
        tmpDB.accounts.add(new Account(42,"Miyasa","KAÇER","G1956.14122"));
        tmpDB.accounts.add(new Account(43,"Kütezziban","BEREKET","B1525.18375"));
        tmpDB.accounts.add(new Account(44,"Araz","AKTAŞ","G1992.12462"));
        tmpDB.accounts.add(new Account(45,"Kınalp","YÜKSEL","B1686.12437"));
        tmpDB.accounts.add(new Account(46,"Eznur","SOYER","G1615.13796"));
        tmpDB.accounts.add(new Account(47,"Muhbet","AKHUN","B1187.12846"));
        tmpDB.accounts.add(new Account(48,"Ruknettin","AKPINAR","G1653.17632"));
        tmpDB.accounts.add(new Account(49,"Koygun","KAYA","G1354.15941"));
        tmpDB.accounts.add(new Account(50,"Baturay","AKBAŞ","B1373.18135"));
        tmpDB.accounts.add(new Account(51,"Çökermiş","AKBULUT","B1161.15966"));
        tmpDB.accounts.add(new Account(52,"Dorukan","SARAÇ","B1261.17925"));
        tmpDB.accounts.add(new Account(53,"Hür","AKBAŞ","G1312.12659"));
        tmpDB.accounts.add(new Account(54,"Karatün","KARADEMİR","B1621.17168"));
        tmpDB.accounts.add(new Account(55,"Abdulkadir","KUŞKU","B1643.14414"));
        tmpDB.accounts.add(new Account(56,"Ertekin","KONURALP","B1821.13142"));
        tmpDB.accounts.add(new Account(57,"Durana","TAŞ","G1957.13417"));
        tmpDB.accounts.add(new Account(58,"Keser","GÜLLÜ","B1244.16929"));
        tmpDB.accounts.add(new Account(59,"Coşkun","DADLI","G1889.18465"));
        tmpDB.accounts.add(new Account(60,"Orkide","YENİLMEZ","B1497.14124"));
        tmpDB.accounts.add(new Account(61,"Tuğsan","DİNLER","G1218.19728"));
        tmpDB.accounts.add(new Account(62,"Ürpek","GÜLTEKİN","B1645.13522"));
        tmpDB.accounts.add(new Account(63,"Arsoy","BOZKURT","B1739.14544"));
        tmpDB.accounts.add(new Account(64,"Köksan","AYTAÇ","G1874.15744"));
        tmpDB.accounts.add(new Account(65,"Tacim","AL","G1221.18919"));
        tmpDB.accounts.add(new Account(66,"Hilmiye","ÖZER","B1229.13591"));
        tmpDB.accounts.add(new Account(67,"Uğurtan","SAĞLAM","G1676.19445"));
        tmpDB.accounts.add(new Account(68,"Nüvide","ÇELİK","G1774.19261"));
        tmpDB.accounts.add(new Account(69,"Yüsra","ALIM","G1268.17169"));
        tmpDB.accounts.add(new Account(70,"Senger","TAŞ","G1978.11572"));
        tmpDB.accounts.add(new Account(71,"Hadra","ALICI","B1637.12187"));
        tmpDB.accounts.add(new Account(72,"Gülsena","OĞUZ","G1746.17515"));
        tmpDB.accounts.add(new Account(73,"Memnune","ÖZDEMİR","B1391.13538"));
        tmpDB.accounts.add(new Account(74,"Yasime","ÇETİN","B1389.19883"));
        tmpDB.accounts.add(new Account(75,"Famile","SAÇLI","B1318.11512"));
        tmpDB.accounts.add(new Account(76,"İnalbey","HALICI","B1548.14184"));
        tmpDB.accounts.add(new Account(77,"Heyvetullah","ADISANLI","B1186.18457"));
        tmpDB.accounts.add(new Account(78,"Ruhişen","KOPTUR","G1414.15747"));
        tmpDB.accounts.add(new Account(79,"Hayel","KELEŞ","G1891.13743"));
        tmpDB.accounts.add(new Account(80,"Soyupak","ÖZKAN","G1758.16586"));
        tmpDB.accounts.add(new Account(81,"Tezol","BÜKÜLMEZ","G1836.16363"));
        tmpDB.accounts.add(new Account(82,"Nazente","KARATOPRAK","B1445.19365"));
        tmpDB.accounts.add(new Account(83,"Demirtaş","İNCE","G1893.16834"));
        tmpDB.accounts.add(new Account(84,"Gençalp","KARA","G1666.19682"));
        tmpDB.accounts.add(new Account(85,"Hürmüs","MEMİŞ","B1375.16331"));
        tmpDB.accounts.add(new Account(86,"Ergönen","AYDIN","B1523.19791"));
        tmpDB.accounts.add(new Account(87,"Veda","CAMGÖZ","B1613.18818"));
        tmpDB.accounts.add(new Account(88,"Ülküme","İNSELÖZ","G1753.15985"));
        tmpDB.accounts.add(new Account(89,"Mumtas","GÜLER","G1422.13753"));
        tmpDB.accounts.add(new Account(90,"Savniye","BAKLACI","G1395.12754"));
        tmpDB.accounts.add(new Account(91,"Samet","İNAN","B1814.12474"));
        tmpDB.accounts.add(new Account(92,"Ğanim","KARSLI","G1112.15237"));
        tmpDB.accounts.add(new Account(93,"Aşur","KÖKSOY","G1797.11269"));
        tmpDB.accounts.add(new Account(94,"Melissa","KORKUT","B1486.19641"));
        tmpDB.accounts.add(new Account(95,"Şahhanım","ÖZDEMİR","B1823.11273"));
        tmpDB.accounts.add(new Account(96,"Tavlı","İZGİ","B1526.13874"));
        tmpDB.accounts.add(new Account(97,"Ümmügülsüm","GÜLŞAN","B1796.12988"));
        tmpDB.accounts.add(new Account(98,"Nesrin","SELÇUK","B1297.12391"));
        tmpDB.accounts.add(new Account(99,"Yücealp","ALTAŞ","G1929.12472"));
        tmpDB.accounts.add(new Account(100,"İzel","ÖZER","B1818.12277"));


        for(int i=1;i<101;i++)
        {
            final DatabaseReference accountRef=db.getReference("Accounts/"+i);
            accountRef.child("firstName").setValue(tmpDB.accounts.get(i).firstName);
            accountRef.child("lastName").setValue(tmpDB.accounts.get(i).lastName);
            accountRef.child("cardID").setValue(tmpDB.accounts.get(i).cardID);
            accountRef.child("number").setValue(tmpDB.accounts.get(i).number);
        }*/








/*RefectoryDatabase tmpDB=new RefectoryDatabase();
        tmpDB.menus.add(new Menu(1,new String[]{"Antep Çorba","Sebze Musakka","Fırın Baget","Spagetti","Şöbiyet"}));
        tmpDB.menus.add(new Menu(2,new String[]{"Ispanaklı Çorba","Patlıcan Kebap","İzmir Köfte","Nohutlu P. Pilav","Yoğurt"}));
        tmpDB.menus.add(new Menu(3,new String[]{"Mercimek Ç.","Mantarlı Et Sote","Tavuk But Şiş","Pey. Su Böreği","Yoğurt"}));
        tmpDB.menus.add(new Menu(4,new String[]{"Sebze Çorba","Etli Kuru Fasulye","Etli Nohut","Pirinç Pilavı","Mevsim Salata"}));
        tmpDB.menus.add(new Menu(5,new String[]{"Domates Ç.","Mezgit Fish Finger","Kabak Graten","Mısırlı Pilav","Yoğurt"}));
        tmpDB.menus.add(new Menu(6,new String[]{"Ezogelin Ç.","Hindi Kavurma","Taskebabı","Soslu Spagetti","Ayran"}));
        tmpDB.menus.add(new Menu(7,new String[]{"Yayla Çorba","Sebze Musakka","Fırın Köfte","Pirinç Pilavı","Ayran"}));
        tmpDB.menus.add(new Menu(8,new String[]{"Mercimek Ç.","Selanik Köfte","Tavuk Nuget","Mantı","Yoğurt"}));
        tmpDB.menus.add(new Menu(9,new String[]{"Tutmaç Çorba","Piliç Topkapı","Kuru Köfte","Cevizli Erişte","Yoğurt"}));
        tmpDB.menus.add(new Menu(10,new String[]{"Antep Çorba","Arnavut Ciğeri","Tavuk Nuget","Spagetti","Kalburabastı"}));
        tmpDB.menus.add(new Menu(11,new String[]{"Domates Ç.","Orman Kebabı","Köri  Tavuk","Yoğ. Mantı","Ayran"}));
        tmpDB.menus.add(new Menu(12,new String[]{"Tutmaç Çorba","Kıymalı Ispanak","Köri  Tavuk","Nohutlu Pilav","Ayran"}));
        tmpDB.menus.add(new Menu(13,new String[]{"Mahluta Çorba","Etli Türlü","Tavuk But Şiş","Barbunya Pilaki","Turşu"}));
        tmpDB.menus.add(new Menu(14,new String[]{"Mercimek Ç.","Tavuk Baget","Tavuk Cordon","Pirinç Pilavı","Akdeniz Gülü Tatlısı"}));
        tmpDB.menus.add(new Menu(15,new String[]{"Ezogelin Ç.","Etli Kuru Fasulye","Kırkağaç Köfte","Bulgur Pilavı","Şöbiyet"}));
        tmpDB.menus.add(new Menu(16,new String[]{"Sebze Çorba","Piliç Topkapı","Kabak Graten","Mısırlı Pilav","Akdeniz Gülü Tatlısı"}));
        tmpDB.menus.add(new Menu(17,new String[]{"Mercimek Ç.","Kıymalı Yumurta","İzmir Köfte","Pirinç Pilavı","Vişne Kompostosu"}));
        tmpDB.menus.add(new Menu(18,new String[]{"Mahluta Çorba","Mezgit Tava","Tavuk Şinitzel","Bulgur Pilavı","Mandalina"}));
        tmpDB.menus.add(new Menu(19,new String[]{"Mercimek Ç.","Kıymalı Ispanak","Mantarlı Piliç","Mantı","Meyve"}));
        tmpDB.menus.add(new Menu(20,new String[]{"Ispanaklı Çorba","Orman Kebabı","Tavuk Nuget","Bulgur Pilavı","Yoğurt"}));
        tmpDB.menus.add(new Menu(21,new String[]{"Sebze Çorba","Etli Kuru Fasulye","Tavuk Cordon","Pey. Su Böreği","Kalburabastı"}));
        tmpDB.menus.add(new Menu(22,new String[]{"Mahluta Çorba","Etli Taze Fasulye","Mantarlı Piliç Roti","Bulgur Pilavı","Ankara Sarması"}));
        tmpDB.menus.add(new Menu(23,new String[]{"Domates Ç.","Kıymalı Yumurta","Köri  Tavuk","Mısırlı Pilav","Ayran"}));
        tmpDB.menus.add(new Menu(24,new String[]{"Köylü Çorba","Kıymalı Ispanak","Kabak Graten","Bulgur Pilavı","Mandalina"}));
        tmpDB.menus.add(new Menu(25,new String[]{"Mercimek Ç.","Tavuk Baget","İzmir Köfte","Su Böreği","Ayran"}));
        tmpDB.menus.add(new Menu(26,new String[]{"Mercimek Ç.","Kadınbudu Köfte","Misket Köfte","Pirinç Pilavı","Ayran"}));
        tmpDB.menus.add(new Menu(27,new String[]{"Tarhana Ç.","Mantarlı Et Sote","Etli Taze Fasulye","Mantı","Ayran"}));
        tmpDB.menus.add(new Menu(28,new String[]{"Ezogelin Ç.","Selanik Köfte","Misket Köfte","Pirinç Pilavı","Şöbiyet"}));
        tmpDB.menus.add(new Menu(29,new String[]{"Sebze Çorba","Orman Kebabı","Kuru Köfte","Bulgur Pilavı","Yoğurt"}));
        tmpDB.menus.add(new Menu(30,new String[]{"Ispanaklı Çorba","Tavuk Baget","Kırkağaç Köfte","Pirinç Pilavı","Ayran"}));
        tmpDB.menus.add(new Menu(31,new String[]{"Şehriye Çorbası","Selanik Köfte","Tavuk Kızartma","Barbunya Pilaki","Ayran"}));



        for(int i=0;i<tmpDB.menus.size();i++)
        {
            final DatabaseReference accountRef=db.getReference("Menus/2017/12/"+(i+1));
            accountRef.child("1").setValue(tmpDB.menus.get(i).items[0]);
            accountRef.child("2").setValue(tmpDB.menus.get(i).items[1]);
            accountRef.child("3").setValue(tmpDB.menus.get(i).items[2]);
            accountRef.child("4").setValue(tmpDB.menus.get(i).items[3]);
            accountRef.child("5").setValue(tmpDB.menus.get(i).items[4]);
        }*/