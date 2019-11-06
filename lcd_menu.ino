/* 
   menuItems and submenuITems display controlled by IRremote(using different buttons).
    
   
    modified 2/6/17
  by Pooja Kose 
  
 */


String menuItems[] = {"Temperature", "Humidity", "LED","BUZZER", "EXIT"};
String menuItems1[] = {"CELSIUS" , "FAHRENHEIT" };
String menuItems2[] = {"LED ON" , "LED OFF" };
String menuItems3[] = {"BUZZER ON" , "BUZZER OFF" };

#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

int readkey;
int menuPage = 0;
int spage1 = 0;
int spage2 = 0;
int spage3 = 0;
int maxMenuPages = 3;
int maxMenuPages1 = 0;
int maxMenuPages2 =0;
int maxMenuPages3 =0;
int cursorPosition = 0;
int cursorPosition1 = 0;
int cursorPosition2 = 0;
int cursorPosition3 = 0;

byte downArrow[8] = {
  0b00100, 
  0b00100, 
  0b00100, 
  0b00100, 
  0b00100, 
  0b10101,   
  0b01110, 
  0b00100   
};

byte upArrow[8] = {
  0b00100, 
  0b01110, 
  0b10101, 
  0b00100,
  0b00100, 
  0b00100, 
  0b00100, 
  0b00100  
};

byte menuCursor[8] = {
  B01000, 
  B00100,
  B00010,
  B11111, 
  B00010, 
  B00100, 
  B01000, 
  B00000 
};

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11,6, 5, 4, 3);
int LED = 7;
int b = 13;
int s = A0;
int t , h ;
#define DHTPIN 8    

#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_OK 0xFF02FD
#define BUTTON_U 0xFF629D
#define BUTTON_D 0xFFA857
#define BUTTON_L 0xFF22DD
#define BUTTON_R 0xFFC23D


void setup() {
   
    Serial.begin(9600);
   pinMode(LED, OUTPUT);
    pinMode(b, OUTPUT);
  irrecv.enableIRIn(); 
  Serial.println("DHTxx test!");
 delay(1000);
  dht.begin();
 
  lcd.begin(16, 2);
  lcd.clear();
  
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
}

void loop() {
 
  h = dht.readHumidity();
  t = dht.readTemperature();
int s=analogRead (s);
  Serial.println(s);
  delay(200);
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
     delay(1000);
   mainMenu();
  Cursor();
  operate();
    
}

void mainMenu() {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}
void subMenu() {
  Serial.print(spage1);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems1[spage1]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems1[spage1 + 1]);
  
  Cursor1();
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 0: 
        break;
      case 1: 
        button = 0;
        switch (cursorPosition1) { 
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem6();
            break;
          
        }
        activeButton = 1;
        subMenu();
        Cursor1();
        break;
      case 2:
        button = 0;
        if (spage1 == 0) {
          cursorPosition1 = cursorPosition1 - 1;
          cursorPosition1 = constrain(cursorPosition1, 0, ((sizeof(menuItems1) / sizeof(String)) - 1));
        }
        if (spage1 % 2 == 0 and cursorPosition1 % 2 == 0) {
          spage1 = spage1 - 1;
          spage1 = constrain(spage1, 0, maxMenuPages1);
        }

        if (spage1 % 2 != 0 and cursorPosition1 % 2 != 0) {
          spage1 = spage1 - 1;
          spage1 = constrain(spage1, 0, maxMenuPages1);
        }

        cursorPosition1 = cursorPosition1 - 1;
        cursorPosition1 = constrain(cursorPosition1, 0, ((sizeof(menuItems1) / sizeof(String)) - 1));

        subMenu();
        Cursor1();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (spage1 % 2 == 0 and cursorPosition1 % 2 != 0) {
          spage1 = spage1 + 1;
          spage1 = constrain(spage1, 0, maxMenuPages1);
        }

        if (spage1 % 2 != 0 and cursorPosition1 % 2 == 0) {
          spage1 = spage1 + 1;
          spage1 = constrain(spage1, 0, maxMenuPages1);
        }

        cursorPosition1 = cursorPosition1 + 1;
        cursorPosition1 = constrain(cursorPosition1, 0, ((sizeof(menuItems1) / sizeof(String)) - 1));
        subMenu();
        Cursor1();
        activeButton = 1;
        break;
      case 4:  
        button = 0;
        activeButton = 1;
        break;

    }
  }

}

void subMenu1() {
   Serial.print(spage2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems2[spage2]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems2[spage2 + 1]);
  
  Cursor2();
  
int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 0: 
        break;
      case 1: 
        button = 0;
        switch (cursorPosition2) { 
          case 0:
            menuItem3();
            break;
          case 1:
            menuItem4();
            break;
          
        }
        activeButton = 1;
        subMenu1();
        Cursor2();
        break;
      case 2:
        button = 0;
        if (spage2 == 0) {
          cursorPosition2 = cursorPosition2 - 1;
          cursorPosition2 = constrain(cursorPosition2, 0, ((sizeof(menuItems2) / sizeof(String)) - 1));
        }
        if (spage2 % 2 == 0 and cursorPosition2 % 2 == 0) {
          spage2 = spage2 - 1;
          spage2 = constrain(spage2, 0, maxMenuPages2);
        }

        if (spage2 % 2 != 0 and cursorPosition2 % 2 != 0) {
          spage2 = spage2 - 1;
          spage2 = constrain(spage2, 0, maxMenuPages2);
        }

        cursorPosition2 = cursorPosition2 - 1;
        cursorPosition2 = constrain(cursorPosition2, 0, ((sizeof(menuItems2) / sizeof(String)) - 1));

        subMenu1();
        Cursor2();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (spage2 % 2 == 0 and cursorPosition2 % 2 != 0) {
          spage2 = spage2 + 1;
          spage2 = constrain(spage2, 0, maxMenuPages2);
        }

        if (spage2 % 2 != 0 and cursorPosition2 % 2 == 0) {
          spage2 = spage2 + 1;
          spage2 = constrain(spage2, 0, maxMenuPages2);
        }

        cursorPosition2 = cursorPosition2 + 1;
        cursorPosition2 = constrain(cursorPosition2, 0, ((sizeof(menuItems2) / sizeof(String)) - 1));
        subMenu1();
        Cursor2();
        activeButton = 1;
        break;
        case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
void subMenu2() {
   Serial.print(spage3);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems3[spage3]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems3[spage3 + 1]);
  
  Cursor3();
  
int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 0: 
        break;
      case 1: 
        button = 0;
        switch (cursorPosition3) { 
          case 0:
            menuItem7();
            break;
          case 1:
            menuItem8();
            break;
          
        }
        activeButton = 1;
        subMenu2();
        Cursor3();
        break;
      case 2:
        button = 0;
        if (spage3 == 0) {
          cursorPosition3 = cursorPosition3 - 1;
          cursorPosition3 = constrain(cursorPosition3, 0, ((sizeof(menuItems3) / sizeof(String)) - 1));
        }
        if (spage3 % 2 == 0 and cursorPosition3 % 2 == 0) {
          spage3 = spage3 - 1;
          spage3 = constrain(spage3, 0, maxMenuPages3);
        }

        if (spage3 % 2 != 0 and cursorPosition3 % 2 != 0) {
          spage3 = spage3 - 1;
          spage3 = constrain(spage3, 0, maxMenuPages3);
        }

        cursorPosition3 = cursorPosition3 - 1;
        cursorPosition3 = constrain(cursorPosition3, 0, ((sizeof(menuItems3) / sizeof(String)) - 1));

        subMenu2();
        Cursor3();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (spage3 % 2 == 0 and cursorPosition3 % 2 != 0) {
          spage3 = spage3 + 1;
          spage3 = constrain(spage3, 0, maxMenuPages3);
        }

        if (spage3 % 2 != 0 and cursorPosition2 % 2 == 0) {
          spage3 = spage3 + 1;
          spage3 = constrain(spage3, 0, maxMenuPages3);
        }

        cursorPosition3 = cursorPosition3 + 1;
        cursorPosition3 = constrain(cursorPosition3, 0, ((sizeof(menuItems3) / sizeof(String)) - 1));
        subMenu2();
        Cursor3();
        activeButton = 1;
        break;
        case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
void Cursor1() {
  for (int x = 0; x < 2; x++) {     
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (spage1 % 2 == 0) {
    if (cursorPosition1 % 2 == 0) { 
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition1 % 2 != 0) { 
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (spage1 % 2 != 0) {
    if (cursorPosition1 % 2 == 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition1 % 2 != 0) {  
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void Cursor2() {
  for (int x = 0; x < 2; x++) {     
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (spage2 % 2 == 0) {
    if (cursorPosition2 % 2 == 0) { 
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition2 % 2 != 0) { 
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (spage2 % 2 != 0) {
    if (cursorPosition2 % 2 == 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition2 % 2 != 0) {  
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void Cursor3() {
  for (int x = 0; x < 2; x++) {     
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (spage3 % 2 == 0) {
    if (cursorPosition3 % 2 == 0) { 
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition3 % 2 != 0) { 
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (spage3 % 2 != 0) {
    if (cursorPosition3 % 2 == 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition3 % 2 != 0) {  
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}


void Cursor() {
  for (int x = 0; x < 2; x++) {     
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) { 
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) { 
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}
void operate() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 0: 
        break;
      case 1: 
        button = 0;
        switch (cursorPosition) { 
          case 0:
          subMenu();
          Cursor1();
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            subMenu1();
          Cursor2();
            break;
          case 3:
           subMenu2();
          Cursor3();
            break;
            case 4:
            menuItem5();
            break;
          
        }
        activeButton = 1;
        mainMenu();
        Cursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        mainMenu();
        Cursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenu();
        Cursor();
        activeButton = 1;
        break;
    }
  }
}
int evaluateButton(int x) {
  x = results.value;
  int result = 0;
  if (irrecv.decode(&results)){
   if (results.value == BUTTON_OK) 
   {
    result = 1; 
  } else if (results.value == BUTTON_U) {
    result = 2; 
  } else if (results.value == BUTTON_D) {
    result = 3; 
  } else if (results.value == BUTTON_L) {
    result = 4; 
  }
  irrecv.resume();
  }
  return result;
}

void menuItem1() {
  
int activeButton = 0;
  lcd.clear();
  lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("Temp: ");
lcd.setCursor(5,0);
lcd.print(t);
lcd.setCursor(8,0);
lcd.print("C");

while (activeButton == 0) {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        subMenu();
        Cursor1();
        activeButton = 1;
        break;
    }
  }
}

void menuItem2() {
int activeButton = 0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity: ");
lcd.setCursor(10,0);
lcd.print(h); 
lcd.setCursor(13,0);
lcd.print("%");

 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
void menuItem3() {
int activeButton = 0;
digitalWrite(LED, HIGH);
lcd.clear();
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("LED ON");
 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem4() {
int activeButton = 0;
digitalWrite(LED, LOW);
lcd.clear();
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("LED OFF");
 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
void menuItem5() {
  int activeButton = 0;
lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("POOJA");
    lcd.setCursor(0,1);
  lcd.print("PRIYANKA");
   while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem6() {
int activeButton = 0;
lcd.clear();
   lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
    lcd.setCursor(5,0);
  lcd.print((t*1.8+32));
    lcd.setCursor(11,0);
  lcd.print("F");

 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
void menuItem7() {
int activeButton = 0;
digitalWrite(b, HIGH);
lcd.clear();
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("BUZZER ON");
 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem8() {
int activeButton = 0;
digitalWrite(b, LOW);
lcd.clear();
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("BUZZER OFF");
 while(activeButton == 0) 
 {
    int button;
    readkey = results.value;
    button = evaluateButton(readkey);
 switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
