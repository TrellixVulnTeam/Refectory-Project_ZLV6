const firebaseFunctionsModule = require('firebase-functions');  
const firebaseAdminModule = require('firebase-admin');
firebaseAdminModule.initializeApp(firebaseFunctionsModule.config().firebase);

const appAccounts = require('express')(); 
const appMenus = require('express')(); 
const appProcesses = require('express')();
const appDateTime = require('express')();
const appQueryCardID = require('express')();



appAccounts.get('/:cardID', (request, response) => 
{  
    firebaseAdminModule.database().ref('/Accounts').orderByChild('cardID').equalTo(request.params.cardID).once('value',snapshot => 
    {
        var account=snapshot.val();
        response.send(account);
    });
});

appMenus.get('/:year/:month/:day', (request, response) => 
{  
    firebaseAdminModule.database().ref(`/Menus/${request.params.year}/${request.params.month}/${request.params.day}`).once('value',snapshot => 
    {
        var menu=snapshot.val();
        response.send(menu);
    });
});

appProcesses.get('/:year/:month/:day/:cardID', (request, response) => 
{  
    firebaseAdminModule.database().ref(`/Processes/${request.params.year}/${request.params.month}/${request.params.day}`).
    orderByChild('cardID').equalTo(request.params.cardID).once('value',snapshot => 
    {
        var processes=snapshot.val();
        response.send(processes);
    });
});

appDateTime.get('/',(request, response) => 
{
    response.send(new Date());
});

appQueryCardID.get('/:year/:month/:day/:cardID',(request, response) => 
{
    firebaseAdminModule.database().ref('/Accounts').orderByChild('cardID').equalTo(request.params.cardID).once('value',snapshot => 
    {
        var account=snapshot.val();
        if(account==null) response.send("No Account!");
        else
        {
            firebaseAdminModule.database().ref(`/Processes/${request.params.year}/${request.params.month}/${request.params.day}`).
            orderByChild('cardID').equalTo(request.params.cardID).once('value',snapshot => 
            {
                var processes=snapshot.val();
                if(processes!=null) response.send("Can't Pass!");
                else response.send("OK");
            });
        }
    });
});


exports.Accounts = firebaseFunctionsModule.https.onRequest(appAccounts); 
exports.Menus = firebaseFunctionsModule.https.onRequest(appMenus); 
exports.Processes = firebaseFunctionsModule.https.onRequest(appProcesses);

exports.DateTime=firebaseFunctionsModule.https.onRequest(appDateTime); 
exports.QueryCardID=firebaseFunctionsModule.https.onRequest(appQueryCardID); 








// appProcesses.get('/:year/:month/:day/:cardID', (request, response) => 
// {  
//         //response.send(`Processes => ${request.params.ID}`);
// });


// exports.GetAccount = functions.https.onRequest((req, res) => {
//     // Grab the text parameter.
//     const original = req.query.text;
//     // Push the new message into the Realtime Database using the Firebase Admin SDK.
//     admin.database().ref('/Accounts').orderByChild('cardID').equalTo(original).once('value',snapshot => {
//       var gel=snapshot.val();
//       res.send(gel);
//     });
//   });

