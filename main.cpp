#include <iostream>
#include <memory>
#include "List.h"
#include "Player.h"
#include "Card.h"
#include "Stack.h"

int main() {
    // ==========================================
    // Part 1: Required test harness (Do not modify)[cite: 7, 8]
    // ==========================================
    std::cout << "== List<int>: addAnywhere / deleteAnywhere / reverse ==" << std::endl;
    std::unique_ptr<List<int*>> nums(makeList<int*>());
    nums->addFront(new int(10));
    nums->addFront(new int(20));
    nums->addFront(new int(30));
    nums->print();
    nums->addAnywhere(1, new int(99));
    nums->print();
    nums->deleteAnywhere(2);
    nums->print();
    nums->reverse();
    nums->print();

    std::cout << std::endl << "== List<int>: concat ==" << std::endl;
    std::unique_ptr<List<int*>> more(makeList<int*>());
    more->addFront(new int(2));
    more->addFront(new int(1));
    more->print();
    nums->concat(more.get());
    nums->print();
    more->print();

    // ==========================================
    // Part 2: Uno Scene with Card Hands (Extra Credit)[cite: 8, 9]
    // ==========================================
    std::cout << std::endl << "== Part 2: Uno Scene ==" << std::endl;

    // 1. Table forms: 3 players join the turn order[cite: 9]
    std::unique_ptr<List<Player*>> table1(makeList<Player*>());
    Player* p1 = new Player(1, "Alice");
    Player* p2 = new Player(2, "Bob");
    Player* p3 = new Player(3, "Charlie");

    // Deal starting hands (Extra Credit Stack<Card>)[cite: 9]
    p1->addCardToHand(new Card("Red", "5"));
    p1->addCardToHand(new Card("Blue", "Skip"));
    p2->addCardToHand(new Card("Yellow", "Draw Two"));
    p3->addCardToHand(new Card("Green", "7"));

    table1->addFront(p3);
    table1->addFront(p2);
    table1->addFront(p1);

    std::cout << "Initial Turn Order:" << std::endl;
    table1->print();

    // 2. New player pulls up a chair mid-order using addAnywhere[cite: 9]
    std::cout << "\nDave pulls up a chair and joins mid-order (position 1):" << std::endl;
    Player* p4 = new Player(4, "Dave");
    p4->addCardToHand(new Card("Wild", "Wild Card"));
    table1->addAnywhere(1, p4);
    table1->print();

    // 3. Reverse card played (prints before and after)[cite: 9]
    std::cout << "\nA Reverse card is played! Turn order before and after reverse:" << std::endl;
    table1->print();
    table1->reverse();
    table1->print();

    // 4. Player runs out of cards and steps away using deleteAnywhere[cite: 9]
    std::cout << "\nBob (id 2) runs out of cards and steps away from position 2:" << std::endl;
    table1->deleteAnywhere(2);
    table1->print();

    // 5. Second table merges into the first using concat[cite: 9]
    std::cout << "\nA second table joins via concat:" << std::endl;
    std::unique_ptr<List<Player*>> table2(makeList<Player*>());
    Player* p5 = new Player(5, "Eve");
    p5->addCardToHand(new Card("Blue", "9"));
    table2->addFront(p5);

    std::cout << "Table 2 before merge:" << std::endl;
    table2->print();

    table1->concat(table2.get());

    std::cout << "Table 1 after merging Table 2:" << std::endl;
    table1->print();
    std::cout << "Table 2 after merge (should print empty):" << std::endl;
    table2->print();

    return 0;
}