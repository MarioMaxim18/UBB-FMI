#include "items.h"
#include <iostream>

ostream& operator<<(ostream& stream, const MediaItem& song)
{
    stream << "Song: [Artist: " << song.artist << " | Title: "<<song.title<<" | Duration: "<<song.dur<<" | Link: "<<song.yt_link<<"]"<< "\n";
    return stream;
}
