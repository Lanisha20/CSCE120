# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Database::Database():stateParkList({}), camperList({}){

}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	// TODO: implement function
	stateParkList.push_back(new StatePark(parkName, entranceFee, trailMiles));
	return;
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function
	camperList.push_back(new Passport(camperName, isJuniorPassport));
	return;
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)
	bool isParkName = false;
	bool isCamperName = false;
	int parkPlace = -1;
	int camperPlace = -1;
	// TODO: implement function
	for(unsigned int i = 0; i < stateParkList.size(); i++){
		if(stateParkList.at(i)->getParkName() == parkName){
			isParkName = true;
			parkPlace = i;
		}
	}
	for(unsigned int i = 0; i < camperList.size(); i++){
		if(camperList.at(i)->getCamperName() == camperName){
			isCamperName = true;
			camperPlace = i;
		}
	}
	if(isParkName && isCamperName){
		camperList.at(camperPlace)->addParkVisited(stateParkList.at(parkPlace));
	}
	return;
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
