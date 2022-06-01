#include "../tests.h"
#include "../Game.h"
#include <iostream>

int Game_Save(){
    // Arrange
    Game g;
    Player p;

    p.setName("PLAYERONE");
    //Tile t = Tile('A',1);
    //p.fillHand(t);    //This causes a double free. why?
    g.AddPlayer(p);

    //p.setName("PLAYERTWO");
    //p.fillHand(Tile('B',2));
    //g.AddPlayer(p);

    // Act
    std::ifstream pre("saves/testSave.txt");
    if (pre){
        //std::cout << "Removing file: saves/testSave.txt" << std::endl;
        remove("saves/testSave.txt");
    }

    g.saveState("testSave", "daniel");

    // Assert
    int numFailures = 0;
    std::ifstream post("saves/testSave.txt");
    numFailures += AssertAndReport(post.good(), 1, "Game_Save_CreatesFile");

    std::string name, hand;
    int score, num_players;

    post >> num_players;
    post >> name;
    post >> score;
    // will only take the first character (won't work for a full hand)
    post >> hand;
    //std::getline(post, hand);
    // std::cout << hand << std::endl;

    numFailures += AssertAndReport(num_players, 1, "Game_Save_Name");
    numFailures += AssertAndReport(name, "PLAYERONE", "Game_Save_Name");
    numFailures += AssertAndReport(score, 0, "Game_Save_Score");
    numFailures += AssertAndReport(hand, "EMPTY", "Game_Save_Hand");

    return numFailures;
}


int Game_InitaliseBag(){
    // Arrange
    Game g;
    LinkedList t = LinkedList();

    // Act
    g.InitaliseBag(t);

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(t.Count(), 98, "Game_InitaliseBag_Size");

    // Count Frequencies
    int freqs[26] = {0};
    int exp[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};

    std::string got = "";
    std::string exps = "";

    // get letter freqs
    int const count = t.Count();
    for (int i=0; i < count; i++){
        char l = t.DrawTile().getLetter();
        freqs[(int)l - 65]++;
    }

    // construct strings
    for (int i=0; i < 26; i++){
        exps += (char)(i+65);
        got += (char)(i+65);

        exps += "-";
        got += "-";

        exps += std::to_string(exp[i]);
        got += std::to_string(freqs[i]);

        if (i < 25){
            exps +=", ";
            got +=", ";
        }
    }

    numFailures += AssertAndReport(got, exps, "Game_InitaliseBag_Freqs");

    return numFailures;
}

int Game_ValidNames(){
    // Arrange
    Game g;

    // Act
    int numFailures = 0;

    if ( !g.validName("A") ) {
        numFailures += AssertAndReport("A returns true", "returned false", "Game_validName");
    }
    if ( !g.validName("ABC") ) {
        numFailures += AssertAndReport("ABC returns true", "returned false", "Game_validName");
    }
    if ( g.validName("U $") ) {
        numFailures += AssertAndReport("U $ returns false", "returned true", "Game_validName");
    }
    if ( g.validName("1") ) {
        numFailures += AssertAndReport("1 returns false", "returned true", "Game_validName");
    }
    if ( g.validName("$") ) {
        numFailures += AssertAndReport("$ returns false", "returned true", "Game_validName");
    }
    if ( g.validName("abc") ) {
        numFailures += AssertAndReport("abc returns false", "returned true", "Game_validName");
    }
    if ( g.validName("the X") ) {
        numFailures += AssertAndReport("the X returns false", "returned true", "Game_validName");
    }

    return numFailures;
}

int Game_ValidMainMenuChoice(){
    // Arrange
    Game g;

    // Act
    int numFailures = 0;

    if ( !g.validMainMenuChoice(1) ) {
        numFailures += AssertAndReport("1 returns true", "returned false", "Game_ValidMainMenuChoice");
    }
    if ( !g.validMainMenuChoice(2) ) {
        numFailures += AssertAndReport("2 returns true", "returned false", "Game_ValidMainMenuChoice");
    }
    if ( !g.validMainMenuChoice(3) ) {
        numFailures += AssertAndReport("3 returns true", "returned false", "Game_ValidMainMenuChoice");
    }
    if ( !g.validMainMenuChoice(4) ) {
        numFailures += AssertAndReport("4 returns true", "returned false", "Game_ValidMainMenuChoice");
    }
    if ( g.validMainMenuChoice(0) ) {
        numFailures += AssertAndReport("0 returns false", "returned true", "Game_ValidMainMenuChoice");
    }
    if ( g.validMainMenuChoice(10) ) {
        numFailures += AssertAndReport("10 returns false", "returned true", "Game_ValidMainMenuChoice");
    }

    return numFailures;
}

int Game_validatePlacementInput() {
    // Arrange
    Game g;

    // Act
    int numFailures = 0;

    if ( !g.validatePlaceTiles("place A at C0") ) {
        
        numFailures += AssertAndReport("place A at C0 returns true", "returned false", "Game_validatePlacementInput");
    }
    if (!g.validatePlaceTiles("place A at C000")) {
        
        numFailures += AssertAndReport("place A at C000 returns true", "returned false", "Game_validatePlacementInput");
    }

    if ( g.validatePlaceTiles("place AatC0") ) {
        
        numFailures += AssertAndReport("place AatC0 returns false", "returned true", "Game_validatePlacementInput");
    }
    
    if ( g.validatePlaceTiles("place A a C0") ) {
        
        numFailures += AssertAndReport("place A a C0 returns false", "returned true", "Game_validatePlacementInput");
    }
    
    if ( g.validatePlaceTiles("place A at 0") ) {
        
        numFailures += AssertAndReport("place A at 0 returns false", "returned true", "Game_validatePlacementInput");
    }

    if ( g.validatePlaceTiles("place AA at C0") ) {
        numFailures += AssertAndReport("place AA at C0 returns false", "returned true", "Game_validatePlacementInput");
    }
    // if you can think of other ways to break input, feel free to add

    if (numFailures == 0 ) {
        numFailures += AssertAndReport("", "", "Game_validatePlacementInput");
    }
    return numFailures;
}

int Game_RunTests(){
    int numFailures = 0;

    numFailures += Game_ValidMainMenuChoice();
    numFailures += Game_ValidNames();
    numFailures += Game_InitaliseBag();
    numFailures += Game_Save();
    numFailures += Game_validatePlacementInput();

    std::cout << std::endl;
    return numFailures;
}