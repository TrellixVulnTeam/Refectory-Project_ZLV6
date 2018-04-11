
var accountObjects=[];


$(document).ready(function()
{
    var rootRef=firebase.database().ref().child("Accounts");


    rootRef.on('value', function(snapshot) 
    {
        var counter=0;
        
        $("#tableBody").empty();
        snapshot.forEach(function(childSnapshot) 
        {
            var ID=childSnapshot.key;
            var cardID=childSnapshot.child("cardID").val();
            var firstName=childSnapshot.child("firstName").val();
            var lastName=childSnapshot.child("lastName").val();
            var number=childSnapshot.child("number").val();

            

            var accountObject = 
            { 
                "ID":ID,
                "cardID":cardID, 
                "firstName":firstName ,
                "lastName":lastName ,
                "number":number 
            };
            accountObjects[counter]=accountObject;
            counter++;

            
          $("#tableBody").append(
            "<tr><td>"
            +ID+
            "</td><td>"
            +firstName+
            "</td><td>"
            +lastName+
            "</td><td>"
            +number+
            "</td><td>"
            +cardID+
            "</td><td class=\"text-center\"><button type=\"button\" class=\"btn btn-danger btn-xs \">Remove</button></td>/tr>");
          
        });
      });

});





function getData()
{
    var parameter=document.getElementById("txtForQuery");
    var parameterValue=parameter.value;
    parameter.value="";

    var index=-1;
    for (i = 0; i <accountObjects.length; i++) 
    {
        if (accountObjects[i].cardID === parameterValue ) 
        { 
            index=i;
            break; 
        }
    }

    if(index===-1) 
    {
        
    }

    else
    {

    }
}











// function processForm(e) 
// {
//     if (e.preventDefault) e.preventDefault();

//     /* do what you want with the form */

//     alert(document.getElementById("frm1text").value);

//     form.submit();




//     // You must return false to prevent the default form behavior
//     return false;
// }

// var form = document.getElementById('getDataForm1');
// if (form.attachEvent) 
// {
//     form.attachEvent("submit", processForm);
// } else 
// {
//     form.addEventListener("submit", processForm);
// }












var mainText=document.getElementById("mainText");
var submitBtn=document.getElementById("submitBtn");
var getDataBtn=document.getElementById("getDataBtn");
var demoP=document.getElementById("demoP");
var heading=document.getElementById("heading");


var fireBaseRefForRetriving=firebase.database().ref("Heading");
fireBaseRefForRetriving.on('value',function(datasnapshot)
{
    heading.innerText=datasnapshot.val();
});


function submitClick()
{
    var firebaseRef=firebase.database().ref();
    demoP.innerHTML=new Date().getHours()+":"+new Date().getMinutes()+":"+new Date().getSeconds();

    var timeStamp=new Date().getHours()+":"+new Date().getMinutes()+":"+new Date().getSeconds();
    firebaseRef.child(timeStamp).set(mainText.value);

    mainText.value="";



}

function getDataClick()
{

}



function addValueKeyClick()
{
    var firebaseRef=firebase.database().ref();
    
    var key=document.getElementById("txtKey").value;
    var value=document.getElementById("txtValue").value;

    firebaseRef.child(key).set(value);

    mainText.value="";
}