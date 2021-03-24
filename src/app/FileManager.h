#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <FS.h>

class FileManager {
  public:
      void begin();
      String read_file(String file_name);
  private: 
};

extern FileManager fileManager;

#endif
