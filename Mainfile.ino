#include <BluetoothSerial.h>

#include <SPI.h>

#include <MFRC522.h>

#define CUSTOM_SETTINGS




BluetoothSerial SerialBT;

byte BTData;
String command;
 

#define SS_PIN    5  // ESP32 pin GIOP5

#define RST_PIN   27 // ESP32 pin GIOP27

 

MFRC522 rfid(SS_PIN, RST_PIN);

 

byte keyTagUID[4] = {0xDF, 0xDA, 0xFA, 0x29};

byte keyTagUID2[4] = {0xAD, 0x87, 0xFA, 0x29};

 

/* Check if Bluetooth configurations are enabled in the SDK */

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)

#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it

#endif

 

void setup()

{

 

  pinMode(2, OUTPUT);  

  pinMode(33, OUTPUT);

  pinMode(12, OUTPUT);  

  pinMode(13, OUTPUT);

  Serial.begin(9600);

 

  SerialBT.begin();

  SerialBT.println("Bluetooth Started! Ready to pair...");

 

 

  SPI.begin(); // init SPI bus

  rfid.PCD_Init(); // init MFRC522

 

}

 

void loop()

{

 

 

  if(SerialBT.available())

  {

    BTData = SerialBT.read();  

   

  }




  if(BTData == '1')

  {

 

   

   

    SerialBT.println("DOOR IS OPENING");

 

    digitalWrite(12, HIGH);

    digitalWrite(13, LOW);

    delay(5000);  

    SerialBT.println("DOOR IS CLOSING");

   

    digitalWrite(12, LOW);

    digitalWrite(13, HIGH);

    delay(5000);

    digitalWrite(13, LOW);

    digitalWrite(12, LOW);

     

  }

  if(BTData == '2')

  {

    delay(100);

    SerialBT.println("OPENING THE DOOR FOR YOU SIR");

 

    digitalWrite(12, HIGH);

    digitalWrite(13, LOW);

    delay(5000);

    digitalWrite(13, LOW);

    digitalWrite(12, LOW);

     

   

  }  

  if(BTData == '3')

  {

    delay(100);

    SerialBT.println("CLOSING THE DOOR FOR YOU SIR");

 

    digitalWrite(12, LOW);

    digitalWrite(13, HIGH);

    delay(5000);

    digitalWrite(13, LOW);

    digitalWrite(12, LOW);

  }  

 

    if(BTData == '4')

  {

    delay(150);  

    SerialBT.println("LIGHTS TURNED ON SIR");  

   

    digitalWrite(33, HIGH);  

 

  }  

    if(BTData == '5')

  {

    delay(150);  

    SerialBT.println("LIGHTS TURNED OFF SIR");  

   

    digitalWrite(33, LOW);

  }  

 

 

  if(BTData == '0')

  {

    digitalWrite(33, LOW);

    digitalWrite(2, LOW);

    digitalWrite(18, LOW);

    delay(150);

 

    SerialBT.println(" TURNED OFF EVERYTHING");

  }
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("led"))
    {

    digitalWrite(12, LOW);

    digitalWrite(13, HIGH);

    delay(5000);

    digitalWrite(13, LOW);

    digitalWrite(12, LOW);

    }
    else 
    {
      Serial.println("bad command");
    }
    Serial.print("Command: ");
    Serial.println(command);
  }

   

 

 

  if (rfid.PICC_IsNewCardPresent()) { // new tag is available

    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed

      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      SerialBT.println("Tap an RFID tag on the RFID-RC522 reader");

     

 

      if (rfid.uid.uidByte[0] == keyTagUID[0] && rfid.uid.uidByte[1] == keyTagUID[1] && rfid.uid.uidByte[2] == keyTagUID[2] && rfid.uid.uidByte[3] == keyTagUID[3] )

      if (rfid.uid.uidByte[0] == keyTagUID2[0] && rfid.uid.uidByte[1] == keyTagUID2[1] && rfid.uid.uidByte[2] == keyTagUID2[2] && rfid.uid.uidByte[3] == keyTagUID2[3] )

     {

        SerialBT.println("Access is granted");  

         

        delay(500);                

        SerialBT.println("DOOR IS OPENING");

       

        digitalWrite(13, HIGH);

        digitalWrite(12, LOW);

        delay(5000);

        SerialBT.println("DOOR IS CLOSING");

               

        digitalWrite(13, LOW);

        digitalWrite(12, HIGH);

        delay(5000);

        digitalWrite(13, LOW);

        digitalWrite(12, LOW);

       

      }

      else

      {

        SerialBT.print("Access denied");

        for (int i = 0; i < rfid.uid.size; i++) {

          SerialBT.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");

          SerialBT.print(rfid.uid.uidByte[i], HEX);

        }

        SerialBT.println();

       

      }

 

      rfid.PICC_HaltA(); // halt PICC

      rfid.PCD_StopCrypto1(); // stop encryption on PCD

    }

 

  }

 

}

 
