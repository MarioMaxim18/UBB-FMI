#include "duration.h"

std::ostream& operator<<(std::ostream& os, const Duration& dur) {
	//format MM:SS
	os << dur.minutes << ":" << dur.seconds;
	return os;
}

Duration::Duration(std::string dur_string) {
	int pos = dur_string.find(':');
	std::string minutes = dur_string.substr(0, pos);
	std::string seconds = dur_string.substr(pos + 1, dur_string.size() - 1);
	ushi i_minutes = std::stoi(minutes);
	ushi i_seconds = std::stoi(seconds);

	this->minutes = i_minutes;
	this->seconds = i_seconds;
}

string Duration::toString() const
{
	return std::to_string(minutes) + ":" + std::to_string(seconds);
}
