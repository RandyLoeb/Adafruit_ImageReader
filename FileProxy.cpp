#include "FileProxy.h"

void FileProxy::close()
{
    if (_useBuffer)
    {
        _fileBuf.clear();
    }

    if (_file)
    {
        _file.close();
    }
}

void FileProxy::read(uint8_t *buf, size_t size)
{
    //Serial.print("reading with size=");
    //Serial.println(size);
    if (_useBuffer)
    {
        for (size_t i = 0; i < size; i++)
        {
            //Serial.print("i=");
            //Serial.println(i);
            if (_position < _fileBuf.size())
            {
                buf[i] = (uint8_t)_fileBuf.at(_position++);
            }
        }
    }
    else
    {
        if (_file)
        {
            _file.read(buf, size);
        }
    }
}

int FileProxy::read()
{
    if (_useBuffer)
    {
        //Serial.print("61:");
        //Serial.println(_fileBuf.at(61));
        //Serial.print("about to read():");
        //Serial.println(_position);
        if (_position < _fileBuf.size())
        {
            return _fileBuf.at(_position++);
        }
        //Serial.println("ending read()");
    }
    else
    {
        if (_file)
        {
            return _file.read();
        }
    }
}

size_t FileProxy::position()
{
    if (_useBuffer)
    {
        return _position;
    }
    else
    {
        if (_file)
        {
            return _file.position();
        }
    }
}

void FileProxy::seek(uint32_t pos)
{
    //Serial.print("Seeking to ");
    //Serial.println(pos);
    if (_useBuffer)
    {
        _position = pos;
    }
    else
    {
        if (_file)
        {
            _file.seek(pos);
        }
    }
}

void FileProxy::setFile(File f)
{

    _file = f;
    if (_useBuffer)
    {

        _fileBuf.clear();

        while (f.available())
        {
            _fileBuf.push_back(f.read());
        }
        Serial.print("_fileBuf size:");
        Serial.println(_fileBuf.size());
        f.seek(0);
    }
}