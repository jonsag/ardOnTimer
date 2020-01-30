
void setTime() {
  

}


unsigned long buttontimeout;
unsigned long repeatbutton;
int button;   //variable to hold the button press
int oldbutton; 
int leftbuttons;  //analog read on the buttons input

void setup(){
  Serial.begin(9600);
}

void loop(){
  button = Pushbutton();  //read the button function.
  if (button != 0) {
    Serial.print("Button ");
    Serial.print(button);
    Serial.println(" was pressed");
  }
}


int Pushbutton(){ 
  if (millis() - buttontimeout >20){   //only read the analog line every 20ms. I had problems reading it more frequently.
    buttontimeout = millis();
    leftbuttons = analogRead(A5);  //read the analog line with buttons attached

    button = 0;  //If no button is pressed, this function will return 0.
    if (leftbuttons <785 && leftbuttons>745) button = 1; //LH Button 1 is pushed
    if (leftbuttons <630 && leftbuttons>590) button = 2; //LH Button 2 is pushed

    //this block will return a button press immediately after it is pressed. That way you can do 
    //rapid taps and it will send each one.   
    if (button != oldbutton){  
      oldbutton = button;
      if ( button !=0){
        repeatbutton = millis();
        return button;  
      }
    }

    //500ms after the button is pressed, if it is still held down, it will resend the button state.
    if (millis()- repeatbutton > 500){  
      repeatbutton = millis();
      return button;
    } 
  }
}
