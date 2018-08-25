MONTH = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC'];
DAY = ['SUN', 'MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT'];

var db = firebase.firestore();

function updateCount(count,density){
    var date = new Date();
    var obj ={
        [date.getFullYear()]: {
            [MONTH[date.getMonth()]]:{
                [date.getDate()]:{
                    Day:DAY[date.getDay()],
                    Customer_visted:count,
                    Customer_present:density
                }
            }
        }
    };
    db.doc("count/year").set(obj,{merge:true}).then(() => {
        console.log("Document written");
    }).catch((err) => {
        console.error("Error adding document: ", err);
    });
}
function readData(){
   db.doc("count/year").get().then((dat)=>{
    $("#just").text(JSON.stringify(dat.data()));
    console.log(dat.data());
    });


}
updateCount(10,5);
readData();