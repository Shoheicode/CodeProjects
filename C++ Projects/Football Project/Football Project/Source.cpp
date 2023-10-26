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
		if (head == nullptr) {
			unique_ptr<Node>next(new Node(player));
			this->head = std::move(next);
		}
		else {
			unique_ptr<Node>next(new Node(player, std::move(this->head)));
			this->head = std::move(next); 
		}
	}

	// deletes the first FootBallPlayer that matches name
	bool deletePlayer(string name) {
		shared_ptr<Node> current = head;
		while (current != nullptr) {
			if (name == current->player.name) {
				shared_ptr<Node> tem = current;

				current = current->next;

				tem.reset();
				return true;
			}
			current = std::move(current->next);
		}
		return false;
	}

	// Uses a weak_ptr to return true if there exists a favorite player, false otherwise 
	bool setFavorite(string name) {

		shared_ptr<Node> current = head;

		while (current != nullptr) {

			if (current->player.name == name) {
				favPlayer = current;
				return true;
			}
			current = current->next;
		}
		
		return false;
	}
	

	// Returns an optional parameter if there is a favorite player
	std::optional<FootBallPlayer> getFavorite() const {
		if (favPlayer.lock() == nullptr) {
			return std::nullopt;
		}
		else {
			return favPlayer.lock()->player;
		}
	}

	// Prints the list of FootBallPlayers on the roster
	void printPlayers() const {
		weak_ptr<Node> current = head;
		while (current.lock() != nullptr) {
			cout << current.lock()->player.name << " " << current.lock()->player.num << endl;
			current = std::move(current.lock()->next);
		}
	}

private:
	struct Node {
		FootBallPlayer player;
		shared_ptr<Node> next;

		Node(FootBallPlayer p, shared_ptr<Node> next = nullptr) {
			player = p;
			this->next = std::move(next);
		}
	};
	shared_ptr<Node> head;
	weak_ptr<Node> favPlayer;
};

// prints out the name of the favorite player or a message 
// stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster) {
	auto temp = roster.getFavorite();

	if (temp != std::nullopt) {
		cout << "Your favorite player is: " << temp->name << endl;
	}
	else {
		cout << "You don't have a favorite player" << endl;
	}

	
}

class Student {
private:
	string m_name;
	shared_ptr <Student> m_pFriend;
public:
	Student(string name) : m_name(name) { }
	void makeFriend(shared_ptr <Student> f) { m_pFriend = f; }
	~Student() { cout << "Person is destroyed" << endl; }

};
void foo() {
	auto p(make_shared<Student>("Cindy"));
	p->makeFriend(p);
};

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

	foo();

}