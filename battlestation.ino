int numA = D0;
int numB = D1;
int numC = D2;
int numD = D3;
int numE = D4;
int numF = D5;
int numG = D6;
int numH = D7;

int butTall = A0;
int butShort = A1;

int green = A2;
int red = A3;

int lives = 9;

enum GameState {
    waiting,
    playing
};

GameState gameState;

void greenOn(){
    digitalWrite(green, HIGH);
}

void greenOff(){
    digitalWrite(green, LOW);
}

void redOn(){
    digitalWrite(red, HIGH);
}

void redOff(){
    digitalWrite(red, LOW);
}

//this will turn the number counter off
void numOff(){
    digitalWrite(numA, LOW);
    digitalWrite(numB, LOW);
    digitalWrite(numC, LOW);
    digitalWrite(numD, LOW);
    digitalWrite(numE, LOW);
    digitalWrite(numF, LOW);
    digitalWrite(numG, LOW);
    digitalWrite(numH, LOW);
}


//this is what updates the number counter, it defaults to 0
void updateNum() {
    switch (lives) {
        case 0:
        default:
        digitalWrite(numA, HIGH);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, LOW);
            break;
        case 1:
        digitalWrite(numA, LOW);
        digitalWrite(numB, LOW);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, LOW);
        digitalWrite(numG, LOW);
        digitalWrite(numH, LOW);
            break;
        case 2:
        digitalWrite(numA, HIGH);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, LOW);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, LOW);
        digitalWrite(numH, HIGH);
            break;
        case 3:
        digitalWrite(numA, LOW);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, LOW);
        digitalWrite(numH, HIGH);
            break;
        case 4:
        digitalWrite(numA, LOW);
        digitalWrite(numB, LOW);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, LOW);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, HIGH);
            break;
        case 5:
        digitalWrite(numA, LOW);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, LOW);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, HIGH);
            break;
        case 6:
        digitalWrite(numA, HIGH);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, LOW);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, HIGH);
            break;
        case 7:
        digitalWrite(numA, LOW);
        digitalWrite(numB, LOW);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, LOW);
        digitalWrite(numH, LOW);
            break;
        case 8:
        digitalWrite(numA, HIGH);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, HIGH);
            break;
        case 9:
        digitalWrite(numA, LOW);
        digitalWrite(numB, HIGH);
        digitalWrite(numC, HIGH);
        digitalWrite(numD, LOW);
        digitalWrite(numE, HIGH);
        digitalWrite(numF, HIGH);
        digitalWrite(numG, HIGH);
        digitalWrite(numH, HIGH);
            break;
    }
}

//this blinks the red button and gets called when the game is over
void blinkRed(int amount){
    for(int i = 0; i< amount; i++){
        redOn();
        delay(1000);
        redOff();
        delay(1000);
    }
}
//here is where we can blink the dot on the counter
void blinkDot(){
    for(int i = 0; i< 5; i++){
        digitalWrite(numD, HIGH);
        delay(500);
        digitalWrite(numD, LOW);
        delay(500);
    }
}
//this function makes it so that the counter ticks down
void countDown(int amount){
    numOff();
    blinkDot();
    updateNum();
    delay(1000);
    redOn();
    for(int i = 0; i < amount; i++){
        lives = lives - 1;
        updateNum();
        delay(1000);
        if(lives == 0){
            return;
        }
    }
}

void setup() {
    pinMode(butTall, INPUT_PULLDOWN);
    pinMode(butShort, INPUT_PULLDOWN);
    pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(numA, OUTPUT);
    pinMode(numB, OUTPUT);
    pinMode(numC, OUTPUT);
    pinMode(numD, OUTPUT);
    pinMode(numE, OUTPUT);
    pinMode(numF, OUTPUT);
    pinMode(numG, OUTPUT);
    pinMode(numH, OUTPUT);
    updateNum();
    gameState = waiting;
}



void loop() {       //at the beginning of every loop we check our gamestate
    switch(gameState){   //to see how we will react to button presses
        case waiting:   //the two gamestats are "waiting" or "playing"
            redOff();
            if(lives <=0){   //this part looks to see if there are less than 1 people alive
                blinkRed(5);
                lives = 9; //and then restarts the game
                updateNum();
            }else{          //here we get kicked into playing at a random interval
                greenOn();
                delay(1000*(random(5,15)));
                greenOff();
                redOn();
                gameState = playing;
            }
            break;
        case playing:
            //once we are playing we can choose to make the risky choice or the safe choice
            if (digitalRead(butTall) == HIGH) {// tall button clicked // risky button
                redOff();
                int randomNum = random(1,10);
                if(randomNum > 5){ //the risky choice could let everyone live but it could also make lots of people die
                    countDown(0);
                } else{
                    countDown(randomNum);
                }
                gameState = waiting;
            }
            if (digitalRead(butShort) == HIGH) {//short button clicked
                redOff();
                countDown(random(1,2)); //some people are always going to die if you're a coward
                gameState = waiting;
            }
            break;

    }
}
