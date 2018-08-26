const MONTH = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC'];
const DAY = ['SUN', 'MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT'];

var db = firebase.database();

function readData(year,month,date){
    // To read data Enter the parameter as eg. 2018,07,15 where each
    // argument is optional and is omitted to grab the parental JSON.

    year = year || 0;
    month = month || 0;
    date = date || 0;

    var query = "counts/";
    if(year!=0){
        query += String(year)+"/";
        if(month!=0){
            query += String(MONTH[month])+"/";
            if(date!=0){
                query += String(date);
            }
        }
    }
    var queryResponse = db.ref(query);

    queryResponse.on("value",(data)=>{
        // $("#just").html(JSON.stringify(data.val()));
        console.log(data.val() );
        
    }, ()=>{
        console.log("Failed Reading , DATA missing");
    });


}
function updateCount(count){
    // db.ref('counts/2018/AUG/15').set({day:"MON",visits:33})
    var date = new Date();
    var obj={
        day:DAY[date.getDay()],
        visits:count,
    }
    db.ref('counts/' +
     String(date.getFullYear()) + '/' +
        String(MONTH[date.getMonth()]) + '/' +
            String(date.getDate())).set(
            obj
    );
}
function getData(route) {
    var req_param=String(route);
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var value = String(this.responseText);
        $("#just").html(value);
      }
    };
    xhttp.open("GET", req_param, true);
    xhttp.send();
  }

// updateCount(39);
// readData();