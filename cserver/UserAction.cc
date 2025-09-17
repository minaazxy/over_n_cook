
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "GameController.h"
#include "UserAction.h"
#include <bits/stdc++.h>

using namespace wfrest;
using namespace ctl;
using namespace std;
GameController& controller = GameController::getInstance("default");
// -- DON'T MODIFY ANY CODE ABOVE THIS LINE -- //
// -- YOU ARE ALLOW TO ADD HEADER FILES UNDER THIS LINE -- //
#define pii pair<int,int>
// TODO: Choose your recipe mode
// you may want to have different strategy for different recipe mode
Recipe RecipeMode;
Order NowOrder;

queue<char> operations;

char LastMove;
// A template map to store the position of each counter
// Question: How do you extend this map to store more than one position for a counter?
// Question2: cutting / normal counter have more than one position, how will you handle it?
const map<Counter, pair<int, int>> counterPosition = {
    { BreadCounter, {0, 1} },
    { CabbageCounter, {8, 4} },
    { CheeseBlockCounter, {0, 10} },
    { TomatoCounter, {8, 7} },
    { RawPattyCounter, {0, 20} },
    { StoveCounter, {0, 19} },
    { PlatesCounter, {4, 20} },
    { TrashCounter, {6, 20} },
    { DeliveryCounter, {1, 20} },

    // There are 2 cutting counters, this is only one of it
    { CuttingCounter, {8, 14} },
    // There are so many normal counters, this is only one of it
    { NormalCounter, {8, 13} },
};
const map<Counter, char> counterDirection = {
    { BreadCounter, 'w' },
    { CabbageCounter, 's' },
    { CheeseBlockCounter, 'w' },
    { TomatoCounter, 's' },
    { RawPattyCounter, 'w' },
    { StoveCounter, 'w' },
    { PlatesCounter, 'd' },
    { TrashCounter, 'd' },
    { DeliveryCounter, 'd' },

    // There are 2 cutting counters, this is only one of it
    { CuttingCounter, 's' },
    // There are so many normal counters, this is only one of it
    { NormalCounter, 's' }
};

void DefaultInitialize();
void DefaultSendOperation();
void Move();
void AllSendOperation();
void Initializeforallfood();
void MakeSalad();
void MoveCounterToCounterinteract();
void MakeCheeseBurger();
void MakeMegaBurger();
void MakeBurger();
int cnt,rnd;

// Init the game (DO NOT MODIFY THIS FUNCTION)
void UserAction::InitGame() {
    Initialize();
    // Set the response to "ok" when finished initialization
    controller.SetResponse("ok");
}

// Just a ugly Initializing function
void UserAction::Initialize() {
    // TODO: You can do some initialization in this function.
    // Feel free to modify this function.
    // DefaultInitialize() will make you a MEGABurger!
    cnt = 0;
    rnd = 0;
    Initializeforallfood();
    cout << "Initializing the game..." << endl;
}

// Main Function of you game logic
void UserAction::SendOperation() {
    // TODO: Implement your gaming logic here
    // DefaultSendOperation() will make you a MEGABurger!
    rnd = controller.GetRound();
    AllSendOperation();
}


// -- Moving series functions Below -- //

void MovePointToPoint(pair<int, int> from, pair<int, int> to) {
    // TODO: Move from one point to another point
    char xdir = from.first < to.first ? 's':'w';
    char ydir = from.second < to.second ? 'd':'a';
    
    int xcnt = abs(from.first - to.first);
    int ycnt = abs(from.second - to.second);

    for(int i = 0; i < xcnt; i++){
        operations.push(xdir);
        //cout<<"number "<<i<<" add xdir："<<xdir<<"\n";
    }

    for(int i = 0; i < ycnt; i++){
        operations.push(ydir);
        //cout<<"number "<<i<<" add ydir："<<ydir<<"\n";
    }
}

void MovePointToCounter(pair<int, int> fromPoint, Counter toCounter) {
    pii targetPosition=counterPosition.at(toCounter);
    MovePointToPoint(fromPoint, targetPosition);
}
void MovePointToCounterinteract(pair<int, int> fromPoint, Counter toCounter) {
    MovePointToCounter(fromPoint, toCounter);
    operations.push(counterDirection.at(toCounter));
    operations.push('e');
}

void MoveCounterToCounter(Counter from, Counter to) {
    pii fromPosition = counterPosition.at(from);
    MovePointToCounter(fromPosition, to);
}
void MoveCounterToCounterinteract(Counter from, Counter to){
    pii fromPosition = counterPosition.at(from);
    MovePointToCounterinteract(fromPosition,to);
}

// -- Moving series functions Above -- //

// -- Strategy for different Recipe Mode Below -- //

Recipe SaladModeStrategy() {
    return Salad;
}

Recipe SaladCheeseburgerModeStrategy() {
    // TODO: Implement your salad cheeseburger mode strategy here
    // Below is a simple example, feel free to change it
    vector<Order> orderList = controller.GetOrderList();
    if (orderList.empty()) {
        return Salad;
    }
    return orderList[0].recipe;
}

Recipe AllRecipeModeStrategy() {
    // TODO: Implement your all recipe mode strategy here
    // Below is a simple example, feel free to change it
    vector<Order> orderList = controller.GetOrderList();
    if (orderList.empty()) {
        return Salad;
    }
    return orderList[0].recipe;
}

Recipe GetNextOrder() {
    // Return the next order based on the Recipe Mode
    if (controller.GetRecipeMode() == "Salad") {
        return SaladModeStrategy();
    }
    else if (controller.GetRecipeMode() == "SaladAndCheeseBurger") {
        return SaladCheeseburgerModeStrategy();
    }
    else {
        return AllRecipeModeStrategy();
    }
}
// -- Strategy for different Recipe Mode Above -- //
// -- Miscallaneous functions Below -- //
void CutIngredient(int times) {
    // TODO: Cut the Ingredient for times
    for(int i = 0; i < times; i++){
        operations.push('f');
    }
}
// -- Miscallaneous functions Above -- //
// -- Pipeline Funtions Below -- //

// You are welcome to change the function prototype
// Like changing the return type or adding more parameters
void MakeSalad() { 
    // TODO: Salad Making Pipeline
    // Move To Cabbage Counter
    // Grab Cabbage
    MovePointToCounterinteract(controller.GetPlayerPosition(),CabbageCounter);
    // Move To Cutting Counter
    MoveCounterToCounterinteract(CabbageCounter,CuttingCounter);
    // Cut Cabbage
    CutIngredient(5);
    // Grab Cabbage Slices
    operations.push('e');
    // Move To A Normal Counter + Put Down Cabbage Slices
    MoveCounterToCounterinteract(CuttingCounter,NormalCounter);
    // Move To Tomato Counter + Grab Tomato
    MoveCounterToCounterinteract(NormalCounter,TomatoCounter);
    // Move To A Cutting Counter + put down tomato
    MoveCounterToCounterinteract(TomatoCounter,CuttingCounter);
    // Cut Tomato
    CutIngredient(3);
    // Move To Plate Counter + Grab Plate
    MoveCounterToCounterinteract(CuttingCounter,PlatesCounter);
    // Move To A Cutting Counter + Grab Tomato Slices
    MoveCounterToCounterinteract(PlatesCounter,CuttingCounter);
    // Move To A Normal Counter + Grab Cabbage Slices
    MoveCounterToCounterinteract(CuttingCounter,NormalCounter);
    // Move To Delivery Counter
    operations.push('A');
    operations.push('A');
    MoveCounterToCounterinteract(NormalCounter,DeliveryCounter);
    // Send Order!
}

void MakeBurger() {
    //TODO: 
    // Move To Patty Counter
    MovePointToCounterinteract(controller.GetPlayerPosition(),RawPattyCounter);
    MoveCounterToCounterinteract(RawPattyCounter,StoveCounter);
    // Move To Stove Counter
    MoveCounterToCounterinteract(StoveCounter,BreadCounter);
    // Move To Bread Counter and Put 
    MoveCounterToCounterinteract(BreadCounter,NormalCounter);
    //GO bread
    MoveCounterToCounterinteract(NormalCounter,PlatesCounter);
    //Move To Plate Counter 
    MoveCounterToCounterinteract(PlatesCounter,StoveCounter);
    //Pick up bread
    MoveCounterToCounterinteract(StoveCounter,NormalCounter);
    //Pick up patty
    MoveCounterToCounterinteract(NormalCounter,DeliveryCounter);
    //Deliver!
}

void MakeCheeseBurger() {
    MovePointToCounterinteract(controller.GetPlayerPosition(),RawPattyCounter);
    MoveCounterToCounterinteract(RawPattyCounter,StoveCounter);
    MoveCounterToCounterinteract(StoveCounter,CheeseBlockCounter);
    MoveCounterToCounterinteract(CheeseBlockCounter,CuttingCounter);
    CutIngredient(3);
    MoveCounterToCounterinteract(CuttingCounter,BreadCounter);
    MoveCounterToCounterinteract(BreadCounter,NormalCounter);
    MoveCounterToCounterinteract(NormalCounter,PlatesCounter);
    MoveCounterToCounterinteract(PlatesCounter,NormalCounter);
    MoveCounterToCounterinteract(NormalCounter,CuttingCounter);
    MoveCounterToCounterinteract(CuttingCounter,StoveCounter);
    MoveCounterToCounterinteract(StoveCounter,DeliveryCounter);
}

void MakeMegaBurger() {
    MovePointToCounterinteract(controller.GetPlayerPosition(),CabbageCounter);
    MoveCounterToCounter(CabbageCounter,CuttingCounter);
    CutIngredient(5);
    operations.push('e');
    MoveCounterToCounter(CuttingCounter,NormalCounter);
    MoveCounterToCounter(NormalCounter,TomatoCounter);
    MoveCounterToCounter(TomatoCounter,CuttingCounter);
    CutIngredient(3);
    MoveCounterToCounter(CuttingCounter,PlatesCounter);
    MoveCounterToCounter(PlatesCounter,CuttingCounter);
    MoveCounterToCounter(CuttingCounter,NormalCounter);
    operations.push('e');
    MoveCounterToCounter(NormalCounter,RawPattyCounter);
    MoveCounterToCounter(RawPattyCounter,StoveCounter);
    MoveCounterToCounter(StoveCounter,CheeseBlockCounter);
    MoveCounterToCounter(CheeseBlockCounter,CuttingCounter);
    CutIngredient(3);
    MoveCounterToCounter(CuttingCounter,BreadCounter);
    MoveCounterToCounter(BreadCounter,NormalCounter);
    operations.push('e');
    MoveCounterToCounter(NormalCounter,CuttingCounter);
    MoveCounterToCounter(CuttingCounter,StoveCounter);
    MoveCounterToCounter(StoveCounter,DeliveryCounter);
}

// -- Pipeline Funtions Below -- //
// -- Default Series Function Below -- //

void Move(){
    char s= 'A';
    if (!operations.empty()) {
        s = operations.front();
        operations.pop();
        cout << "Operation: " << s << endl;
    }
    if (s == 'w'){
        //LastMove = 'w';
        controller.MoveUp();
    }
    if (s == 's'){
        //LastMove = 's';
        controller.MoveDown();
    }
    if (s == 'a'){
        //LastMove = 'a';
        controller.MoveLeft();
    }
    if (s == 'd'){
        //LastMove = 'd';
        controller.MoveRight();
    }
    if (s == 'e') controller.Interact();
    if (s == 'f') controller.InteractSpecial();
    LastMove = s;
}

void Initializeforallfood() {
    while (!operations.empty()) {
        operations.pop();
    }
}
void AllSendOperation() { 
    if(operations.empty()){
        Recipe nextRecipe = GetNextOrder();
        Initializeforallfood();
        if(nextRecipe == Salad) MakeSalad();
        if(nextRecipe == CheeseBurger) MakeCheeseBurger();
        if(nextRecipe == MegaBurger) MakeMegaBurger();
    }
    
    char s = operations.front();
    operations.pop();

    if (s == 'w'){controller.MoveUp();}
    if (s == 's'){controller.MoveDown();}
    if (s == 'a'){controller.MoveLeft();}
    if (s == 'd'){controller.MoveRight();}
    if (s == 'e') controller.Interact();
    if (s == 'f') controller.InteractSpecial();
}//bye