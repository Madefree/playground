#include <TeltonikaTM1Q.h>
#include <NewSoftSerial.h>

#undef WATCHDOG
#define SERIAL
#define SMS

#ifdef WATCHDOG
#include "avr/io.h"
#include "avr/wdt.h"
#endif  

char smsbuffer[160];//buffer to store received SMS
char n[20];         //buffer to store SMS sender number

int i;


void setup() 
{
  // init WATCHDOG 8 sec
  #ifdef WATCHDOG
  wdt_enable(WDTO_8S);
  #endif
  
  //Serial connection.
  Serial.begin(9600);
  Serial.println("BeeGSM, manage Phone Book with SMS");
  //Start configuration.
  gsm.debug(false);
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
}

int readSer (char* inbuf, int l)
{
  int ret = 0;
  i = 0;
  while (Serial.available() > 0)
  {
    if (i < l)
    {
      inbuf[i] = Serial.read();
      i++;
      inbuf[i] = '\0';
    }
    ret = 1;
  }
  return(ret);
}

int parseMsg(char* smsbuf)
{
  char phonebook[300] = "";
  char findtext[20] = "";
  String msg = "";
  String cmd = "";
  String id = "";
  String nam = "";
  String num = "";
  int index = 0;
  char bid[3] = "";
  char name[20] = "";
  char number[20] = "";
  int ret = 0;
  
  msg = smsbuf;
  i = 0;
  for (i; i < msg.indexOf(":",i); i++)
    cmd.concat(msg.charAt(i));
  Serial.println(cmd);
  
  if (cmd.equals("ADD"))
  {
    i++;
    for (i; i < msg.indexOf(",",i); i++)
      nam.concat(msg.charAt(i));
    
    i++;
    for (i; i < msg.length(); i++)
      num.concat(msg.charAt(i));
    
    for (i=0; i < nam.length(); i++)
      name[i] = nam.charAt(i);
    
    for (i=0; i < num.length(); i++)
      number[i] = num.charAt(i);
    
    if (gsm.writePhoneBook(number,name))
    {
      Serial.print("Write ");
      Serial.print(name);
      Serial.print(" ");
      Serial.println(number);
      
      #ifdef SMS
      if (gsm.call(n, 10000))
      {
        Serial.print("\nCALL ");
        Serial.println(n);
      }
      #endif

      ret=1;
    }
  }
  else if (cmd.equals("READ"))
  {
    i++;
    for (i; i < msg.length(); i++)
      id.concat(msg.charAt(i));
    
    for (i=0; i < id.length(); i++)
      bid[i] = id.charAt(i);
    index = atoi(bid);
    
    if (gsm.readPhoneBook(index,number,name))
    {
      Serial.print("Index: ");
      Serial.println(index);
      Serial.print("Name: ");
      Serial.println(name);
      Serial.print("Number: ");
      Serial.println(number);
      ret = 1;
    }
  }
  else if (cmd.equals("READALL"))
  {
    //Read all phone book
    Serial.print("Number of items: ");
    Serial.println(gsm.readAllPhoneBook(phonebook)); //returns number of items
    Serial.println(phonebook);
    ret = 1;
  }
  else if (cmd.equals("FIND"))
  {
    i++;
    for (i; i < msg.length(); i++)
      nam.concat(msg.charAt(i));
    for (i=0; i < nam.length(); i++)
      findtext[i] = nam.charAt(i);
    
    if (gsm.findPhoneBook(findtext,index,number,name))
    {
      Serial.print("Index: ");
      Serial.println(index);
      Serial.print("Name: ");
      Serial.println(name);
      Serial.print("Number: ");
      Serial.println(number);
      ret = 1;
    }
  }
  else if (cmd.equals("CALL"))
  {
    i++;
    for (i; i < msg.length(); i++)
      num.concat(msg.charAt(i));
    for (i=0; i < num.length(); i++)
      number[i] = num.charAt(i);
      
    if (gsm.call(number, 10000))
    {
      Serial.print("\nCALL ");
      Serial.println(number);
      ret = 1;
    }
  }
  else if (cmd.equals("CALLID"))
  {
    i++;
    for (i; i < msg.length(); i++)
      id.concat(msg.charAt(i));
    
    for (i=0; i < id.length(); i++)
      bid[i] = id.charAt(i);
    index = atoi(bid);
    
    if (gsm.readPhoneBook(index,number,name))
    {
      if (gsm.call(number, 10000))
      {
        Serial.print("\nCALL ");
        Serial.println(number);
        ret = 1;
      }
    }
  }
  
  return(ret);
}

void loop()
{
  //reset WATCHDOG
  #ifdef WATCHDOG
  wdt_reset();
  #endif
  
  #ifdef SERIAL
  if (readSer(smsbuffer, 160))
  {
    if (parseMsg(smsbuffer))
      Serial.println("OK");
    else
      Serial.println("ERROR");
  }
  delay(500);
  #endif
 
  #ifdef SMS
  if (gsm.readSMS(smsbuffer, 160, n, 20))
  {
    Serial.print("Sender: ");
    Serial.println(n);
    Serial.print("Message: ");
    Serial.println(smsbuffer);
    
    //Parsing SMS
    if (parseMsg(smsbuffer))
      Serial.println("OK");
    else
      Serial.println("ERROR");
  }
  #endif
}
