// Defining Triggers and Echos
const int echoPin_1 = 5;  //__D1
const int trigPin_1 = 4;  //__D2
const int echoPin_2 = 0;  //__D3
const int trigPin_2 = 2;  //__D4

const int thres = 50; //in centimeter

int d1, d2;
int enter = 0;
int xit = 0;
int count = 0;

void setup() {
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  Serial.begin(9600);
}

float get_distance(int trigPin, int echoPin){ //gets the distance from the sensor
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance= duration*0.034/2;
  return(distance);
}

bool await_removal(int trigPin, int echoPin){ //waits till the objects moves from the sensor
  while(get_distance(trigPin, echoPin) < thres){
        delay(10);
     }
  return true;
}
bool is_triggered(int d){ //checks if the distance is lesser than that of the threshold
  if(d<thres){
    return true;
  }
  else{
    return false;
  }
}
void entry(int d1, int d2){ //function for the evaluation of the count
  if(is_triggered(d1)){
    while(!is_triggered(get_distance(trigPin_2, echoPin_2))){
      delay(10);
    }
    if(await_removal(trigPin_2, echoPin_2)){
      count++;  
    }
    
  }

  else if(is_triggered(d2)){
    while(!is_triggered(get_distance(trigPin_1, echoPin_1))){
      delay(10);
    }
    if(await_removal(trigPin_1, echoPin_1)){
      count--;  
    }
  }
}
void loop() {
  d1=get_distance(trigPin_1, echoPin_1);
  d2=get_distance(trigPin_2, echoPin_2);
  entry(d1, d2);
//  Serial.print("Distance 1 is");
//  Serial.println(d1);
//  Serial.print("Distance 2 is");
//  Serial.println(d2);
  Serial.print("Count is");
  Serial.println(count);
  delay(200);
}
