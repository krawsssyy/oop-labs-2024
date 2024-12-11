#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

enum Location { INDOOR, OUTDOOR };

class SportsEvent {
	private:
		const int year;
		enum Location location;
		std::string type;
		float* scores;
		int noParticipants;
		static int totalEvents;
		static int magicLen;
	public:
		SportsEvent() : year(2024), location(INDOOR), type(""), noParticipants(1) { // default constructor
			this->scores = new float[this->noParticipants];
			memset(this->scores, 0.f, sizeof(float) * this->noParticipants);
			totalEvents++;
		}

		void setScores(float* scores, int size) { // setter for scores
			if (scores && size > magicLen) { // validate
				delete[] this->scores;
				this->scores = new float[size];
				memcpy(this->scores, scores, sizeof(float) * size);

				this->noParticipants = size; // update number of participants
			}
			else
				throw std::exception("New scores array doesn't exist or doesn't have the necessary size!");
		}

		float* getScores() { // getter for scores
			float* cpy = new float[this->noParticipants];
			memcpy(cpy, this->scores, sizeof(float) * this->noParticipants);
			return cpy;
		}

		int getNoParticipants() { return this->noParticipants; } // getter for the participants

		SportsEvent(int year, enum Location location, int noParticipants) : year(year), location(location) { // parametrized constructor
			if (noParticipants < 1) // validate number of participants and ensure it is valid
				this->noParticipants = 1;
			this->scores = new float[this->noParticipants];
			memset(this->scores, 0.f, sizeof(float) * this->noParticipants);

			totalEvents++;	
		}

		~SportsEvent() {
			delete[] this->scores;
			this->scores = nullptr;
		}

		SportsEvent(const SportsEvent& se) : year(se.year), location(se.location), noParticipants(se.noParticipants) { // copy constructor
			this->scores = new float[this->noParticipants];
			memcpy(this->scores, se.scores, sizeof(float) * this->noParticipants);

			totalEvents++;
		}

		static int getNoEvents() { return totalEvents; } // setter for the number of events

		SportsEvent& operator=(const SportsEvent& se) {
			if (this != &se) { // avoid self reference
				delete this;
				new (this) SportsEvent(se);
			}
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const SportsEvent& se);
		friend SportsEvent& operator+(int lhs, SportsEvent& rhs);

		float operator[](int idx) {
			return this->scores[idx];
		}

		int getBestParticipant() {
			float max = -1.f; // initialize max value with a value that cannot be reached
			int idx = 0;

			for(int i = 0; i < this->noParticipants; i++)
				if (this->scores[i] > max) {
					max = this->scores[i];
					idx = i;
				}
			return idx;
		}

		float calculateAverageScore() {
			float avg = 0;

			for (int i = 0; i < this->noParticipants; i++)
				avg += this->scores[i];

			return avg / this->noParticipants;
		}
};

int SportsEvent::totalEvents = 0;
int SportsEvent::magicLen = 1;

std::ostream& operator<<(std::ostream& os, const SportsEvent& se) {
	os << "Year: " << se.year << "; Location: " << (se.location == INDOOR ? "INDOOR" : "OUTDOOR") << "; Number of participants: " << se.noParticipants << "; Scores: ";
	for (int i = 0; i < se.noParticipants; i++)
		os << se.scores[i] << " ";
	os << '\n';
	return os;
}
SportsEvent& operator+(int lhs, SportsEvent& rhs) {
	for (int i = 0; i < rhs.noParticipants; i++)
		rhs.scores[i] += lhs;
	return rhs;
}
int main() {
	SportsEvent s1(); // test default constructor

	SportsEvent s2(2024, INDOOR, 5); // test parametrized constructor

	float tst[] = {9.8f, 8.7f, 10.0f};
	s2.setScores(tst, 3);
	float* res = s2.getScores();
	std::cout << "First score: " << res[0] << std::endl;

	delete[] res;
	res = nullptr; // cleanup returned pointer

	SportsEvent* s3 = new SportsEvent();
	delete s3; // test destructor
	s3 = nullptr;

	SportsEvent s4(s2); // test copy constructor

	SportsEvent s5 = s2; // test operator=

	std::cout << s5; // test operator<<
	
	s5 = 10 + s5; // test operator+

	std::cout << "Second score: " << s5[1] << std::endl; // test operator[]

	std::cout << "Best participant: " << s5.getBestParticipant() << std::endl; // test getBestParticipant function

	std::cout << "Average: " << s5.calculateAverageScore() << std::endl; // test calculate average function

	return 0;
}