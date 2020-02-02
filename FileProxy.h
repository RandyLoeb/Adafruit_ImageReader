#include <Arduino.h>
#include "FS.h"
#include <vector>
class FileProxy
{
public:
    // void draw(Adafruit_EPD &epd, int16_t x, int16_t y);
    //uint8_t *getBuffer();
    //int16_t getWidth();
    //int16_t getHeight();
    void close();
    size_t position();
    void seek(uint32_t pos);
    void read(uint8_t *buf, size_t size);
    void setFile(File f);
    int read();

protected:
    size_t _position = 0;
    File _file;
    std::vector<int> _fileBuf;
    int _useBuffer = 1;
    //  friend class Adafruit_ImageReader; ///< Loading occurs here
};