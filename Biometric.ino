#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(2, 3);
#include <Adafruit_Fingerprint.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


uint8_t id = 1;
int result = 0;

#define AD A0
#define UP A1
#define DN A2
#define DL A3
#define SN A4
#define RLY A5
#define BZ 6

void setup()
{
  pinMode(AD, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DN, INPUT_PULLUP);
  pinMode(DL, INPUT_PULLUP);
  pinMode(SN, INPUT_PULLUP);
  pinMode(BZ, OUTPUT);
  pinMode(RLY, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); lcd.print("Biometric Based!");
  lcd.setCursor(0, 1); lcd.print("Security System!");
  delay(3000);
  lcd.setCursor(0, 0); lcd.print("For Two Wheeler!");
  lcd.setCursor(0, 1); lcd.print("!!!!!!!!!!!!!!!!");
  delay(3000);
  lcd.setCursor(0, 0); lcd.print("Module Searching");
  lcd.setCursor(0, 1); lcd.print("Please Wait....!");
  delay(2000);
  finger.begin(9600);
  //finger.begin(57600);
  delay(10);

  if (finger.verifyPassword())
  {
    lcd.setCursor(0, 0); lcd.print("!!Module Found!!");
    lcd.setCursor(0, 1); lcd.print("!!Successfully!!");
    delay(2000);
  }
  else
  {
    lcd.clear();
    lcd.print("Module Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Check Connections");
    while (1);
  }
  Serial.begin(9600);
  delay(10);
}

void loop()
{
  checkKeys();

  lcd.setCursor(0, 0); lcd.print("Scan Your Finger");
  lcd.setCursor(0, 1); lcd.print("To Start Vehicle");

  if (digitalRead(UP) == LOW || digitalRead(DN) == LOW)
  {
    digitalWrite(BZ, HIGH);
    delay(500);
    digitalWrite(BZ, LOW);
    for (int i = 0; i < 1; i++)
    {
      lcd.setCursor(0, 0); lcd.print("Place Your.....!");
      lcd.setCursor(0, 1); lcd.print("Finger Properly!");
      delay(2000);
      result = getFingerprintIDez();
      if (result > 0)
      {
        lcd.setCursor(0, 0); lcd.print("Please Wait....!");
        lcd.setCursor(0, 1); lcd.print("Searching Data.!");
        delay(2000);
        chk_card1();
      }
      else
        return;
    }
  }
}

void chk_card1()
{
  if (result == 1)
  {
    digitalWrite(RLY, HIGH);
    lcd.setCursor(0, 0); lcd.print("   Authorize    ");
    lcd.setCursor(0, 1); lcd.print("      User      ");
    delay(2000);
    lcd.setCursor(0, 0); lcd.print("WELCOME");
    lcd.setCursor(0, 1); lcd.print("User 1");
    delay(2000);
    OPEN();
  }
  else
    chk_card2();
  return;
}

void chk_card2()
{
  if (result == 2)
  {
    digitalWrite(RLY, HIGH);
    lcd.setCursor(0, 0); lcd.print("   Authorize    ");
    lcd.setCursor(0, 1); lcd.print("      User      ");
    delay(2000);
    lcd.setCursor(0, 0); lcd.print("WELCOME");
    lcd.setCursor(0, 1); lcd.print("User 2");
    delay(2000);
    OPEN();
  }
  else
    chk_card3();
  return;
}

void chk_card3()
{
  if (result == 3)
  {
    digitalWrite(RLY, HIGH);
    lcd.setCursor(0, 0); lcd.print("   Authorize    ");
    lcd.setCursor(0, 1); lcd.print("      User      ");
    delay(2000);
    lcd.setCursor(0, 0); lcd.print("!WELCOME");
    lcd.setCursor(0, 1); lcd.print("User 3");
    delay(2000);
    OPEN();
  }
  else
    chk_card4();
  return;
}

void chk_card4()
{
  if (result == 4)
  {
    digitalWrite(RLY, HIGH);
    lcd.setCursor(0, 0); lcd.print("   Authorize    ");
    lcd.setCursor(0, 1); lcd.print("      User      ");
    delay(2000);
    lcd.setCursor(0, 0); lcd.print("!WELCOME");
    lcd.setCursor(0, 1); lcd.print("User 4");
    delay(2000);
    OPEN();
  }
  else
    chk_card5();
  return;
}

void chk_card5()
{
  if (result == 5)
  {
    digitalWrite(RLY, HIGH);
    lcd.setCursor(0, 0); lcd.print("   Authorize    ");
    lcd.setCursor(0, 1); lcd.print("      User      ");
    delay(2000);
    lcd.setCursor(0, 0); lcd.print("!WELCOME");
    lcd.setCursor(0, 1); lcd.print("User 5");
    delay(2000);
    OPEN();
  }
}

void OPEN()
{
  if (digitalRead(UP) == LOW || digitalRead(DN) == LOW)
  {
    digitalWrite(RLY, LOW);
    delay(2000);
    return;
  }
  OPEN();
}


void checkKeys()
{
  if (digitalRead(AD) == 0)
  {
    lcd.clear();
    lcd.print("Please Wait");
    delay(2000);
    while (digitalRead(AD) == 0);
    Enroll();
  }

  else if (digitalRead(DL) == 0)
  {
    lcd.clear();
    lcd.print("Please Wait");
    delay(2000);
    delet();
  }
}

void Enroll()
{
  int count = 0;
  lcd.clear();
  lcd.print("Enroll Finger    ");
  lcd.setCursor(0, 1);
  lcd.print("Location: ");
  while (1)
  {
    lcd.setCursor(9, 1);
    lcd.print(count);
    if (digitalRead(UP) == 0)
    {
      count++;
      if (count > 25)
        count = 0;
      delay(500);
    }

    else if (digitalRead(DN) == 0)
    {
      count--;
      if (count < 0)
        count = 25;
      delay(500);
    }
    else if (digitalRead(DL) == 0)
    {
      id = count;
      getFingerprintEnroll();
      return;
    }

    else if (digitalRead(AD) == 0)
    {
      return;
    }
  }
}

void delet()
{
  int count = 0;
  lcd.clear();
  lcd.print("Delete Finger    ");
  lcd.setCursor(0, 1);
  lcd.print("Location: ");
  while (1)
  {
    lcd.setCursor(9, 1);
    lcd.print(count);
    if (digitalRead(UP) == 0)
    {
      count++;
      if (count > 25)
        count = 0;
      delay(500);
    }
    else if (digitalRead(DN) == 0)
    {
      count--;
      if (count < 0)
        count = 25;
      delay(500);
    }
    else if (digitalRead(DL) == 0)
    {
      id = count;
      deleteFingerprint(id);
      return;
    }
    else if (digitalRead(AD) == 0)
    {
      return;
    }
  }
}

uint8_t getFingerprintEnroll()
{
  int p = -1;
  lcd.clear();
  lcd.print("Finger ID: ");
  lcd.print(id);
  lcd.setCursor(0, 1);
  lcd.print("Place Finger");
  delay(2000);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
      case FINGERPRINT_OK:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Image Taken....!");
        delay(1000);
        break;
      case FINGERPRINT_NOFINGER:
        lcd.setCursor(0, 0); lcd.print("No Finger......!");
        lcd.setCursor(0, 1); lcd.print("Detected.......!");
        delay(1000);
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
        delay(1000);
        break;
      case FINGERPRINT_IMAGEFAIL:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Image Fail.....!");
        delay(1000);
        break;
      default:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
        delay(1000);
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p)
  {
    case FINGERPRINT_OK:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Image Converted!");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Image Too Messy!");
      delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
      delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Feature Fail...!");
      delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Invalid Image..!");
      delay(1000);
      return p;
    default:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
      delay(1000);
      return p;
  }

  lcd.setCursor(0, 0); lcd.print("Please Remove..!");
  lcd.setCursor(0, 1); lcd.print("Your Finger....!");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  lcd.setCursor(0, 0); lcd.print("Place Same.....!");
  lcd.setCursor(0, 1); lcd.print("Finger Again...!");
  delay(2000);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Image Converted!");
        delay(1000);
        break;
      case FINGERPRINT_NOFINGER:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("No Finger Found!");
        delay(1000);
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
        delay(1000);
        break;
      case FINGERPRINT_IMAGEFAIL:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Image Fail.....!");
        delay(1000);
        break;
      default:
        lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
        lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
        delay(1000);
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p)
  {
    case FINGERPRINT_OK:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Image Converted!");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Image Too Messy!");
      delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
      delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Feature Fail...!");
      delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Invalid Image..!");
      delay(1000);
      return p;
    default:
      lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
      lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
      delay(1000);
      return p;
  }

  // OK converted!
  p = finger.createModel();
  if (p == FINGERPRINT_OK)
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Images Matched.!");
    delay(1000);
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
    delay(1000);
    return p;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH)
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Did Not Match..!");
    delay(1000);
    return p;
  }
  else
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
    delay(1000);
    return p;
  }
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
    lcd.setCursor(0, 0); lcd.print("Finger Stored..!");
    lcd.setCursor(0, 1); lcd.print("!!Successfully!!");
    delay(2000);
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Comm. Error....!");
    delay(1000);
    return p;
  }
  else if (p == FINGERPRINT_BADLOCATION)
  {
    lcd.setCursor(0, 0); lcd.print("Could Not Store!");
    lcd.setCursor(0, 1); lcd.print("In That Location");
    delay(1000);
    return p;
  }
  else if (p == FINGERPRINT_FLASHERR)
  {
    lcd.setCursor(0, 0); lcd.print("Error Writing..!");
    lcd.setCursor(0, 1); lcd.print("To Flash.......!");
    delay(1000);
    return p;
  }
  else
  {
    lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
    lcd.setCursor(0, 1); lcd.print("Unknown Error..!");
    delay(1000);
    return p;
  }
}

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();

  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    lcd.setCursor(0, 0); lcd.print("Finger Not Found");
    lcd.setCursor(0, 1); lcd.print("In Data - Base...!");
    delay(2000);
    fingerMismatch();
    return 0;
  }
  lcd.setCursor(0, 0); lcd.print("Fingerprint....!");
  lcd.setCursor(0, 1); lcd.print("Match ID: "); lcd.print(finger.fingerID); lcd.print("      ");
  digitalWrite(BZ, LOW);
  delay(2000);
  return finger.fingerID;
}

uint8_t deleteFingerprint(uint8_t id)
{
  uint8_t p = -1;
  lcd.clear();
  lcd.print("Please wait");
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Deleted!");
    lcd.clear();
    lcd.print("Figer Deleted");
    lcd.setCursor(0, 1);
    lcd.print("Successfully");
    delay(2000);
  }
  else
  {
    Serial.print("Something Wrong");
    lcd.clear();
    lcd.print("Something Wrong");
    lcd.setCursor(0, 1);
    lcd.print("Try Again Later");
    delay(2000);
    return p;
  }
}

void fingerMismatch()
{
  digitalWrite(BZ, HIGH);
  lcd.setCursor(0, 0); lcd.print("  Unauthorized  ");
  lcd.setCursor(0, 1); lcd.print("      User      ");
  delay(2000);
  digitalWrite(BZ, LOW);
  return;
}


