#include <memory>
#include <iostream>
#include <string>
#include <optional>
using namespace std;

struct FootBallPlayer {
	string name;
	int num;

};

class FootBallRoster {
public:
	// Adds a FootBallPlayer to the roster.
	void addPlayer(FootBallPlayer player) {

	}

	// deletes the first FootBallPlayer that matches name
	bool deletePlayer(string name) {

	}

	// Uses a weak_ptr to return true if there exists a favorite player, false otherwise 
	bool setFavorite(string name) {

	}

	// Returns an optional parameter if there is a favorite player
	std::optional<FootBallPlayer> getFavorite() const {

	}

	// Prints the list of FootBallPlayers on the roster
	void printPlayers() const {

	}

private:
	struct Node {
		FootBallPlayer player;

		unique_ptr<FootBallPlayer> next;

		Node(FootBallPlayer p, unique_ptr<FootBallPlayer> n = nullptr) {
			player = p;
		}
	};

	unique_ptr<Node> root;
};

// prints out the name of the favorite player or a message 
// stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster);

int main() {

	FootBallPlayer fb1{ "Matthew Stafford", 9 };
	FootBallPlayer fb2{ "Aaron Donald", 99 };
	FootBallPlayer fb3{ "Jalen Ramsey", 5 };

	FootBallRoster roster;

	roster.addPlayer(fb1);
	roster.addPlayer(fb2);
	roster.addPlayer(fb3);

	roster.printPlayers();
	roster.setFavorite("Aaron Donald");

	favoritePlayer(roster);

	roster.deletePlayer("Aaron Donald");
	favoritePlayer(roster);
}