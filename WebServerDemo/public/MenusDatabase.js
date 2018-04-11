$(document).ready(function()
{


    var rootRef=firebase.database().ref().child("Menus");

    rootRef.on('value', function(snapshot1) 
    {
        $("#tableBody").empty();
        snapshot1.forEach(function(snapshot2) 
        {
            var year=snapshot2.key;
            snapshot2.forEach(function(snapshot3) 
            {
                var month=snapshot3.key;
                snapshot3.forEach(function(chieldSnapShot) 
                {
                    var day=chieldSnapShot.key;
                    var dateString=day+"/"+month+"/"+year;

                    var _1=chieldSnapShot.child("1").val();
                    var _2=chieldSnapShot.child("2").val();
                    var _3=chieldSnapShot.child("3").val();
                    var _4=chieldSnapShot.child("4").val();
                    var _5=chieldSnapShot.child("5").val();
                
                    $("#tableBody").append
                    (
                        "<tr><td>"
                        +dateString+
                        "</td><td class=\"text-center\">"
                        +_1+
                        "</td><td class=\"text-center\">"
                        +_2+
                        "</td><td class=\"text-center\">"
                        +_3+
                        "</td><td class=\"text-center\">"
                        +_4+
                        "</td><td class=\"text-center\">"
                        +_5+
                        "</td></td>/tr>"
                    );
                 });
            });
        });
    });
});

    /*rootRef.on("value", snap => 
    {
        var name=snap.child("Name").val();
        var email=snap.child("Email").val();
        $("#tableBody").append("<tr><td>"+name+"</td><td>"+email+
        "</td><td><button>Remove</button></td>/tr>");
    }
);*/



   /* rootRef.on("child_added", snap => 
    {
        var name=snap.child("Name").val();
        var email=snap.child("Email").val();
        $("#tableBody").append("<tr><td>"+name+"</td><td>"+email+
        "</td><td><button>Remove</button></td>/tr>");
    }
    );*/






 
















// var mainText=document.getElementById("mainText");
// var submitBtn=document.getElementById("submitBtn");
// var getDataBtn=document.getElementById("getDataBtn");
// var demoP=document.getElementById("demoP");
// var heading=document.getElementById("heading");


// var fireBaseRefForRetriving=firebase.database().ref("Heading");
// fireBaseRefForRetriving.on('value',function(datasnapshot)
// {
//     heading.innerText=datasnapshot.val();
// });


// function submitClick()
// {
//     var firebaseRef=firebase.database().ref();
//     demoP.innerHTML=new Date().getHours()+":"+new Date().getMinutes()+":"+new Date().getSeconds();

//     var timeStamp=new Date().getHours()+":"+new Date().getMinutes()+":"+new Date().getSeconds();
//     firebaseRef.child(timeStamp).set(mainText.value);

//     mainText.value="";



// }

// function getDataClick()
// {

// }



// function addValueKeyClick()
// {
//     var firebaseRef=firebase.database().ref();
    
//     var key=document.getElementById("txtKey").value;
//     var value=document.getElementById("txtValue").value;

//     firebaseRef.child(key).set(value);

//     mainText.value="";
// }