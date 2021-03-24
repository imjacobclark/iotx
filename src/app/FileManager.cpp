#include "FileManager.h"

void FileManager::begin(){
  Serial.println("File Manager starting...");

  Serial.println("Mounting file system...");
 
  if(SPIFFS.begin()){
      Serial.println("File system mounted OK");  
  }else{
      Serial.println("Error mounting the file system");  
  }
}

String FileManager::read_file(String file_name){
    File root = SPIFFS.open(file_name,  "r");
    String fileAsString = "";

    if(!root){
        Serial.println("Error opening file");
        return "";
    }
 
    File file = root.openNextFile();
    
    while(file.available()){
      fileAsString = fileAsString + (char) file.read();
    }

    return fileAsString;
}
