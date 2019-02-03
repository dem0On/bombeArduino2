#include <Keypad.h>
#include <LiquidCrystal.h>

const byte numRows= 4;
const byte numCols= 4;

int currentLength = 0;
char password[4];

byte newChar[8]={
  B00000,
  B00000,
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111
};

int chiffre = 0;

long secMillis = 0; // store last time for second add
long interval = 1000; // interval for seconds

char entered[4];
int Scount = 0; // count seconds
int Mcount = 0; // count minutes
int Hcount = 0; // count hours
int DefuseTimer = 0; // set timer to 0

String premierNb;
String deuxNb;
String nombre;


int tailleTemps = 0;
LiquidCrystal lcd(12,11,5,4,3,2);

char keymap[numRows][numCols]= { {'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'} };

byte rowPins[numRows] = {A0,A1,A2,A3}; //Rows 0 to 3
byte colPins[numCols]= {A4,A5,A6,A7}; //Columns 0 to 3

//initializes an instance of the Keypad class

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Entrez un code: ");
  while (currentLength < 4)
  {
   
    lcd.setCursor(currentLength + 6, 1);
    lcd.cursor();
    char key = myKeypad.getKey();
    key == NO_KEY;
    if (key != NO_KEY)
    {
      if ((key != '*')&&(key != '#'))
      { 
      lcd.print(key);
      password[currentLength] = key;
      currentLength++;
      }
    }
  }
  if (currentLength == 4)
  {
    delay(500);
    lcd.noCursor();
    lcd.clear();
    lcd.home();
    lcd.print("Votre code: ");
    lcd.setCursor(6,1);
    lcd.print(password[0]);
    lcd.print(password[1]);
    lcd.print(password[2]);
    lcd.print(password[3]);

    
    delay(3000);
    lcd.clear();
    currentLength = 0;
  }
  lcd.setCursor(0,0);
  lcd.print("Temps: ");
  while(tailleTemps <5){
    lcd.setCursor(tailleTemps + 0, 1);
    if(chiffre == 2){
      nombre = premierNb + deuxNb;
      Mcount = nombre.toInt();
      tailleTemps = 7;
    }
     lcd.cursor();
    char key = myKeypad.getKey();
    key == NO_KEY;
    if (key != NO_KEY)
    {
      if ((key != '*')&&(key != '#') && (key !='A') && (key != 'B') && (key != 'C') && (key != 'D'))
      { 
      lcd.print(key);
      if(chiffre == 0){
        premierNb = key;
        chiffre ++;
      }else if(chiffre == 1){
        deuxNb = key;
        chiffre ++;
      }
      tailleTemps ++;
      }
    }
  }
  if (tailleTemps == 7){
    lcd.noCursor();
    lcd.clear();
    lcd.home();
    lcd.print("Le temps: ");
    lcd.setCursor(6,1);
    lcd.print(nombre);
    lcd.print(':');
    lcd.print('0');
    lcd.print('0');
    
    delay(3000);
    lcd.clear();
    currentLength = 0;
}
}

//If key is pressed, this key is stored in 'keypressed' variable //If key is not equal to 'NO_KEY', then this key is printed out //if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process

void loop() {
timer();
  char key2 = myKeypad.getKey(); // get the key
  
  if (key2 == '*')
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Code: ");
      
      while (currentLength < 4)
        {
          
          timer();
          
          char key2 = myKeypad.getKey(); 
          if (key2 == '#')
            {
              currentLength = 0;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Code: ");
            }
          else                  
          if (key2 != NO_KEY)    
            {
              
              lcd.setCursor(currentLength + 7, 0);
              lcd.cursor();
              
              lcd.print(key2);
              entered[currentLength] = key2;
              currentLength++;
             
              delay(100);
              lcd.noCursor();
              lcd.setCursor(currentLength + 6, 0);
              lcd.print("*");
              lcd.setCursor(currentLength + 7, 0);
              lcd.cursor();
            }
        }

      if (currentLength == 4) 
        {
          if (entered[0] == password[0] && entered[1] == password[1] && entered[2] == password[2] && entered[3] == password[3])
            {
              lcd.noCursor();
              lcd.clear();
              lcd.home();
              lcd.print("Bomb desarme");
              currentLength = 0;
             
              delay(2500);
              lcd.setCursor(0,1);
              lcd.print("Remettre à zero");
              delay(1000000);
            }
      else
        {
          lcd.noCursor();
          lcd.clear();
          lcd.home();
          lcd.print("Mauvais code!");
    
          if (Hcount > 0)
            {
              Hcount = Hcount - 1;
            }
    
          if (Mcount > 0)
            {
              Mcount = Mcount - 59;
            }
          if (Scount > 0)
            {
              Scount = Scount - 59;
            }
        delay(1500);
        currentLength = 0;
  
        }
      }  
    }
}

void timer()
{
  Serial.print(Scount);
  Serial.println();
  
  if (Hcount <= 0)
  {
    if ( Mcount < 0 )
    {
      lcd.noCursor();
      lcd.clear();
      lcd.home();
      lcd.print("The Bomb Has ");
      lcd.setCursor (0,1);
      lcd.print("Exploded!");
      
      while (Mcount < 0) 
      {
        
        delay(100); 
        
        delay(100); 
       
        delay(100); 
        
        delay(100); 
     
        delay(100); 
        
        delay(100);
      }
    } 
  }

  lcd.setCursor (0,1); // sets cursor to 2nd line
  lcd.print ("Temps:");

  if (Hcount >= 10)
    {
      lcd.setCursor (7,1);
      lcd.print (Hcount);
    }
  if (Hcount < 10) 
    {
      lcd.setCursor (7,1);
      lcd.write ("0");
      lcd.setCursor (8,1);
      lcd.print (Hcount);
    }

  lcd.print (":");

  if (Mcount >= 10)
    {
      lcd.setCursor (10,1);
      lcd.print (Mcount);
    }
  if (Mcount < 10) 
    {
      lcd.setCursor (10,1);
      lcd.write ("0");
      lcd.setCursor (11,1);
      lcd.print (Mcount);
    }
    
  lcd.print (":");

  if (Scount >= 10) 
    {
      lcd.setCursor (13,1);
      lcd.print (Scount);
    }
  if (Scount < 10) 
    {
      lcd.setCursor (13,1);
      lcd.write ("0");
      lcd.setCursor (14,1);
      lcd.print (Scount);
    }

  if (Hcount <0) 
    {
      Hcount = 0; 
    }

  if (Mcount <0) 
    {
      Hcount --; 
      Mcount = 59; 
    }

  if (Scount <1) // if 60 do this operation
    {
      Mcount --; // add 1 to Mcount
      Scount = 59; // reset Scount
    }

  if (Scount > 0) // do this oper. 59 times
    {
      unsigned long currentMillis = millis();
  
      if(currentMillis - secMillis > interval) 
        {
          secMillis = currentMillis;
          Scount --; // add 1 to Scount
          delay(10); // waits for a second
          delay(10); // waits for a second
          //lcd.clear();
        }
    }
}
