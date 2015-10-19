#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

#include "cardsDeckState.h"
#include "card.h"

Card Parse(std::vector< std::string > &patterns) {
	Card card;

	card.requiredMetalAmount = stoi(patterns[0]);
	card.requiredStoneAmount = stoi(patterns[1]);

	card.damage = stoi(patterns[2]);
	card.damageEnemyTower = stoi(patterns[3]);
	card.damageYourself = stoi(patterns[4]);

	card.changeEnemyMetalAmount = stoi(patterns[5]);
	card.changeEnemyMinesNumber = stoi(patterns[6]);
	card.changeEnemyQuarriesNumber = stoi(patterns[7]);
	card.changeEnemyStoneAmount = stoi(patterns[8]);
	card.changeYourMetalAmount = stoi(patterns[9]);
	card.changeYourMinesNumber = stoi(patterns[10]);
	card.changeYourQuarriesNumber = stoi(patterns[11]);
	card.changeYourStoneAmount = stoi(patterns[12]);
	card.changeYourTower = stoi(patterns[13]);
	card.changeYourWall = stoi(patterns[14]);

	card.name = patterns[15];

	return card;
}

CardsDeckState::CardsDeckState(int cardsNumber) {
	std::fstream stream;
	stream.open("Cards\\cards.txt");

	for (int i = 0; i < cardsNumber; ++i ) {
		std::vector< std::string > patterns;
		for (int j = 0; j < 16; ++j) {
			std::string pattern;
			stream >> pattern;
			patterns.push_back(pattern);
		}
		cards.push_back(Parse(patterns));
	}

	stream.close();

	std::srand((unsigned int)std::time(0));
	std::random_shuffle ( cards.begin(), cards.end() );
}

CardsDeckState::~CardsDeckState() 
{
}

void CardsDeckState::ReturnCard(Card card) {
	cards.push_back(card);
	std::random_shuffle ( cards.begin(), cards.end() );
}

Card CardsDeckState::GetCard() {
	Card card = cards.front();
	cards.pop_front();
	return card;
}