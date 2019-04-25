const int LOCKED = 0;
const int WAITING_1 = 1;
const int WAITING_2 = -1;
const int UNLOCKED = 2;
const int CHECKING = 3;

int state = LOCKED;
int push_handled = 0;

int seq[2] = {0,0};
const int pass[2] = {1,2};

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  
  switch(state) {
    case LOCKED: {
    	analogWrite(11, 255);
    
    int close = digitalRead(2);
    
    if(close == HIGH) {
     analogWrite(11, 0);
     state = WAITING_1;
    }
  
  break;
  }
 
    case WAITING_1: {
   analogWrite(12, 255);
   
   int btn1 = digitalRead(6);
   int btn2 = digitalRead(3);
      
    if(btn1 == LOW && btn2 == LOW) {
       	push_handled = 0; 
      }
      
      if(btn1 == HIGH) {
      	seq[0] = 1;
        push_handled = 1;
        state = WAITING_2;
      } else if (btn2 == HIGH) {
        seq[0] = 2;
        push_handled = 1;
        state = WAITING_2;
      }      
   break;
  }
    case WAITING_2 : {
  
     analogWrite(12,255); 
     int btn1 = digitalRead(6);
   	 int btn2 = digitalRead(3);
     
      if(btn1 == LOW && btn2 == LOW) {
       	push_handled = 0; 
      }
      if((btn1 == HIGH) && (!push_handled)) {
       	push_handled = 1;
        seq[1] = 1;
        state = CHECKING;
      } else if((btn2 == HIGH) && (!push_handled)){
        push_handled = 1;
        seq[1] = 2;
        state = CHECKING;	 
      }
      break;
    }
    
    case CHECKING : {
      analogWrite(12,0);
      
      if((seq[0] == pass[0]) && (seq[1] == pass[1])) {
        state = UNLOCKED;
      } else {
        for(int i = 0; i < 3; i++ ) {
          analogWrite(11,255);
          delay(500);
          analogWrite(11,0);
          delay(500);
      }
        state = LOCKED;
      }
      break;
    }
    
    case UNLOCKED: {
      analogWrite(13, 255);
      delay(5000);
      analogWrite(13,0);
      state = LOCKED;
      break;
    }
}
}


