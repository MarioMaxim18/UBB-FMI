#include "items.h"
#include <iostream>

ostream& operator<<(ostream& stream, const MediaItem& song)
{
    stream <<song.toString();
    return stream;
}

bool operator==(const MediaItem& item1, const MediaItem& item2) {
    return item1.artist == item2.artist && item1.title == item2.title;
}

string MediaItem::toString() const
{
    return artist + "," + title + "," + dur.toString() + "," + yt_link;
}

std::pair<ushi, ushi> VideoItem::processResolutionString(const std::string& resolution) const
{
    int posSep = resolution.find_first_of("x");
    int res1 = stoi(resolution.substr(0, posSep));
    int res2 = stoi(resolution.substr(posSep + 1, resolution.length()));
    return std::make_pair(res1, res2);
}

string VideoItem::toString() const
{
    return MediaItem::toString() + "," + std::to_string(res.first) + "x" + std::to_string(res.second);
}
