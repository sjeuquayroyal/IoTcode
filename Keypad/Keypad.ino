#include <Keypad.h>
#include <Servo.h>
#include <string.h>
#include <LiquidCrystal.h>

const byte rows = 4;
const byte columns = 4;
int holdDelay = 700;
int n =3;
int state = 0;
char key = 0;
int pos = 0;

String default_passwd = "2580";
//variable to store the user input for password
String input_passwd = "";
//Define keys for lock and unlock or change password function
char lock_key = '*';
char unlock_key = '#';
char change_pass_key = '-'; //press * key for more than 3 second
// Create an instance for servo motor
Servo servo_A0;
//Define characters matrix
char keys[rows][columns] = 
{
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'},
};

byte rowPins[rows] = {6, 7, 8, 9};
byte columnPins[columns] = {10, 11, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

char function_key(int n)
{
 char temp = keypad.getKey();
 if ((int)keypad.getState() == PRESSED)
 {
 if (temp != 0) {key = temp;} 
 }
 if ((int)keypad.getState() == HOLD)
 {
state++;
 state = constrain(state, 1, n);
 delay(holdDelay);
 } 
 if ((int)keypad.getState() == RELEASED)
 {
 key += state;
 state = 0; 
 } 
 delay(100);
 //Serial.println(key);
 return key;
}
// Define function input_password
String input_password(int num_char)
{
 String passwd = "";
 //Serial.print("Input password: ");
 do 
 {
 char temp = keypad.getKey();
if (temp != 0) 
 {
 //Serial.print(temp);
 LCD_display(passwd.length(), 1, "*");
 passwd += temp;
 }
 delay(100);
 }
while (passwd.length() < num_char);
 //Serial.println();
 return passwd;
}
// Define function change_password
String Change_password(int num_char, String current_passwd)
{
 //Authenticate the old password:
 //Serial.print("Input old password: ");
 LCD_display(0, 0, "OLD PASSWORD:");
 String old_passwd = input_password(num_char);
 
 if (old_passwd != current_passwd)
 {
 lcd.clear();
 LCD_display(0, 0, "WRONG PASSWORD!");
 //Serial.println("Password does not match! Nothing changes");
return current_passwd; 
 }
 //New password 
 //Serial.print("Input new password: ");
 lcd.clear();
 LCD_display(0, 0, "NEW PASSWORD:");
 String new_passwd = input_password(num_char);
 //Confirm passwd
 //Serial.print("Input new password again: ");
lcd.clear();
 LCD_display(0, 0, "CONFIRM PASSWORD");
 String confirm_passwd = input_password(num_char);
if (confirm_passwd == new_passwd)
 {
//Serial.println("Password has changed!!!");
 lcd.clear();
LCD_display(0, 0, "CHANGED PASSWORD");
return confirm_passwd;
 }
 else
 {
//Serial.println("Password does not match! Nothing changes");
 lcd.clear();
LCD_display(0, 0, "NOTHING CHANGES!");
return current_passwd; 
 }
}
void Unlock()
{
 //Serial.print("Input password: ");
 lcd.clear();
 LCD_display(0, 0, "INPUT PASSWORD:");
input_passwd = input_password(4);
if (input_passwd == default_passwd)
{
 lcd.clear();
 LCD_display(0, 0, "OPENNING!!!");
 //Unlock by servo_A0
  analogWrite(2, HIGH);
 for (pos = 0; pos <= 180; pos += 1)
 {
// tell servo to go to position in variable 'pos'
 servo_A0.write(pos);
 // wait 15 ms for servo to reach the position
 delay(15); // Wait for 15 millisecond(s)
 }
 delay(1000); //open door 3s then close
 //lock by servo_A0
  
 tone(A3, 1000, 100);
 digitalWrite(A2, HIGH);
 delay(50);
  digitalWrite(A2, LOW);
 delay(50);
 
 lcd.clear();
 LCD_display(0, 0, "CLOSING!!!");
 for (pos = 180; pos >= 0; pos -= 1) 
 {
 // tell servo to go to position in variable 'pos'
 servo_A0.write(pos);
 // wait 15 ms for servo to reach the position
 delay(15); // Wait for 15 millisecond(s)
 } 
  
  tone(A3, 1000, 100);
  digitalWrite(A1, HIGH);
  delay(50);
  digitalWrite(A1, LOW);
  delay(50);
}
else 
{
 //Serial.println("Wrong password!");
 LCD_display(0, 0, "WRONG PASSWORD!");
}
//Reset input_passwd
input_passwd = "";
 key = 0;
}
// Define LCD display function
void LCD_display(int column, int line, String message)
{
 // set the cursor to column 0, line 1
 // (note: line 1 is the second row, since counting begins with 0):
 lcd.setCursor(column, line);
 // print the number of seconds since reset:
 lcd.print(message);
}
void setup()
{
 //Setting serial with baudrate 9600
 //Serial.begin(9600);
 // connect signal pin of servo to pin number 4 on Uno
 servo_A0.attach(A0); 
 servo_A0.write(pos);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 LCD_display(0, 0, "Welcome!");
}
void loop()
{
 lcd.clear();
 LCD_display(0, 0, "STATUS: LOCKED!");
 LCD_display(0, 1, "UNLOCK: PRESS #");
 while (key !=unlock_key & key != change_pass_key)
 {
 key = function_key(n);
 //lcd.setCursor(8, 1);
 // print the key
if (key == unlock_key) 
 {
 Unlock();
 }
 
 if (key == change_pass_key)
 {
default_passwd = Change_password(4, default_passwd);
 delay(2000);
 key =0;
 }
}
}
