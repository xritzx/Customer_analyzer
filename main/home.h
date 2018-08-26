const char landingPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Customer</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="main.css" />
</head>
<body>
    
    <h4 id="just">Khali</h4>


    <script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
    <script src="https://www.gstatic.com/firebasejs/5.3.1/firebase.js"></script>
    <script src="https://www.gstatic.com/firebasejs/5.2.0/firebase-app.js"></script>
    <script src="https://www.gstatic.com/firebasejs/5.2.0/firebase-database.js"></script>  
    <script>
    // Initialize Firebase


    var config = {
        apiKey: "AIzaSyCz-d9gKv657C08LUHpE_z0DMlYoYHZAG8",
        authDomain: "customer-analyze.firebaseapp.com",
        databaseURL: "https://customer-analyze.firebaseio.com",
        projectId: "customer-analyze",
        storageBucket: "customer-analyze.appspot.com",
        messagingSenderId: "679397497955"
    };
    firebase.initializeApp(config);


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

    setInterval(function() {
        getData("count");
        }, 2000);




    </script>
</body>
</html>

    )=====";