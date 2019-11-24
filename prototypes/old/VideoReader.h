#ifndef VIDEOREADER_H
#define VIDEOREADER_H


class VideoReader
{
public:
    virtual ~VideoReader() = default;

    virtual void handle() = 0;
};

#endif // VIDEOREADER_H
