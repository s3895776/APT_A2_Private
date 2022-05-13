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

    g.saveState("testSave");

    // Assert
    int numFailures = 0;
    std::ifstream post("saves/testSave.txt");
    numFailures += AssertAndReport(post.good(), 1, "Game_Save_CreatesFile");

    std::string name, hand;
    int score;

    post >> name;
    post >> score;
    post >> hand;

    numFailures += AssertAndReport(name, "PLAYERONE", "Game_Save_Name");
    numFailures += AssertAndReport(score, 0, "Game_Save_Score");
    numFailures += AssertAndReport(hand, "", "Game_Save_Hand");

    return numFailures;
}

int Game_Load(){
    // Arrange
    Game g;
    //g.AddPlayer();

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_Load");

    return numFailures;
}

int Game_InitaliseBag(){
    // TODO(dan): test no duplicates, shuffle correct, etc...
    // Arrange
    Game g;
    LinkedList t;

    // Act
    g.InitaliseBag(t);
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_InitaliseBag");

    return numFailures;
}

int Game_ValidNames(){
    // Arrange
    Game g;
    LinkedList t;

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_ValidNames");

    return numFailures;
}

int Game_MainMenuChoices(){
    // Arrange
    Game g;

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_MainMenuChoices");

    return numFailures;
}


int Game_RunTests(){
    int numFailures = 0;

    //numFailures += Game_MainMenuChoices();
    //numFailures += Game_ValidNames();
    //numFailures += Game_InitaliseBag();
    numFailures += Game_Save();
    //numFailures += Game_Load();

    std::cout << std::endl;
    return numFailures;
}