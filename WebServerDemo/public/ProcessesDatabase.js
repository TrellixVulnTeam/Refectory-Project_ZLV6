$(document).ready(function()
{


    var rootRef=firebase.database().ref().child("Processes");

    rootRef.on('value', function(snapshot1) 
    {
        $("#tableBody").empty();
        snapshot1.forEach(function(snapshot2) 
        {
            var year=snapshot2.key;
            snapshot2.forEach(function(snapshot3) 
            {
                var month=snapshot3.key;
                snapshot3.forEach(function(snapshot4) 
                {
                    var day=snapshot4.key;
                    snapshot4.forEach(function(chieldSnapShot) 
                    {
                        var accountID=chieldSnapShot.key;
                        var dateString=day+"/"+month+"/"+year;

                        var choiceCode=chieldSnapShot.child("choiceCode").val();
                        var timeString=chieldSnapShot.child("timeString").val();
                    
                        $("#tableBody").append
                        (
                            "<tr><td>"
                            +dateString+
                            "</td><td class=\"text-center\">"
                            +timeString+
                            "</td><td class=\"text-center\">"
                            +accountID+
                            "</td><td class=\"text-center\">"
                            +choiceCode+
                            "</td></td>/tr>"
                        );
                    });
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