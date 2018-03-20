
static int time_s = 0;
int liang = 0;



void setup() {
  // put your setup code here, to run once:
  //arduino clock runs at 16MHz
  //timer 0/2 8 bits ----255
  //timer 1   16bits ----65535
  //timer speed (Hz)=16mHz/prescaler
  //interrupt frequency =16MHz/(prescaler*compare match register + 1)
  //compare match register=[16MHz/(prescale * desired interrupt frequency)] - 1
  //desired frequency = 1 every 3mins
  //                  = 1 / 180 (Hz)
  // max interval allowed by arduino uno is 4s
  //thus choose the interval tobe 1Hz and count to 180 times  trigger the interrupt
  // counting how many seconds has past
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  

  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  
  sei();//allow interrupts

  }

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  if (time_s < 4){
    if(time_s % 2 == 0){
      digitalWrite(13,HIGH);
      }
      else{
        
        digitalWrite(13,LOW);
        }
    time_s ++;
  }
  else{
    //BME 280 measure
    //VCNL4040 measure
    //zigbee transmit
    //for test two led (green and yellow) represent 1s and 180s
    //G == pin 13
    //Y == pin 8 
    if( liang % 2 == 0){
      digitalWrite(8,HIGH);
      }
     else{
       digitalWrite(8,LOW);
       }
    liang ++; 
    time_s = 0;
  }
}
